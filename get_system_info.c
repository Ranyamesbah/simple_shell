#include "header_main.h"

/**
 * clear_info_struct - Initializes info_t struct fields
 * @info: Pointer to the info_t struct
 *
 * Description: Sets all fields of the info_t struct to NULL or 0.
 */
void clear_info_struct(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info_struct - Initializes info_t struct fields
 * @info: Pointer to the info_t struct
 * @av: Argument vector
 *
 * Description: Sets the fname, arg, argc, argv and path fields of the info_t
 * struct. It also calls replace_alias and replace_vars functions.
 */
void set_info_struct(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow_delim(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = string_duplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info_struct - Frees info_t struct fields
 * @info: Pointer to the info_t struct
 * @all: Boolean value indicating if all fields should be freed
 *
 * Description: Frees the memory allocated for the argv field of the info_t
 * struct. If all is true, it also frees the memory allocated for arg, env,
 * history, alias, environ and cmd_buf fields of the info_t struct. Finally,
 * it closes the readfd file descriptor and clears the buffer.
 */
void free_info_struct(info_t *info, int all)
{
	free_string_array(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list_nodes(&(info->env));
		if (info->history)
			free_list_nodes(&(info->history));
		if (info->alias)
			free_list_nodes(&(info->alias));
		free_string_array(info->environ);
		info->environ = NULL;
		free_and_nullify_ptr((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		write_character(BUF_FLUSH);
	}
}

#include "header_main.h"

/**
 * history_cmd - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int history_cmd(info_t *info)
{
	print_list_items(info->history);
	return (0);
}

/**
 * unset_alias_cmd - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_cmd(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = find_character(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_by_index(&(info->alias),
		get_node_index(info->alias, node_with_prefix(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_cmd - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias_cmd(info_t *info, char *str)
{
	char *p;

	p = find_character(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_cmd(info, str));

	unset_alias_cmd(info, str);
	return (add_node_at_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias_cmd - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias_cmd(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = find_character(node->str, '=');
		for (a = node->str; a <= p; a++)
			write_character(*a);
		write_character('\'');
		print_string(p + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_cmd - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int alias_cmd(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias_cmd(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = find_character(info->argv[i], '=');
		if (p)
			set_alias_cmd(info, info->argv[i]);
		else
			print_alias_cmd(node_with_prefix(info->alias, info->argv[i], '='));
	}

	return (0);
}

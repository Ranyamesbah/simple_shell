#include "header_main.h"

/**
 * print_env - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_env(info_t *info)
{
	print_list_strings(info->env);
	return (0);
}

/**
 * get_env_value - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value of the variable
 */
char *get_env_value(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = str_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env_value - sets a value to an existing environment variable
 *                 or creates a new one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int set_env_value(info_t *info)
{
	if (info->argc != 3)
	{
		_print_str_stderr("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env_variable(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env_value - removes an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int unset_env_value(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_print_str_stderr("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		delete_env_variable(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates environment variables linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_at_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

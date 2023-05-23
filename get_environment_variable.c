#include "header_main.h"

/**
 * get_environ_strings - returns a copy of the current environment variables
 * stored as a string array
 *
 * @info: pointer to a struct containing potential arguments and environment
 *        variable information
 *
 * Return: a string array copy of the current environment variables
 */
char **get_environ_strings(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_array(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * delete_env_variable - removes an environment variable from the list
 *
 * @info: pointer to a struct containing potential arguments and environment
 *        variable information
 * @var: the name of the environment variable to remove
 *
 * Return: 1 if the variable was successfully removed, 0 otherwise
 */
int delete_env_variable(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_by_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * set_env_variable - initializes or modifies an environment variable
 *
 * @info: pointer to a struct containing potential arguments and environment
 *        variable information
 * @var: the name of the environment variable to set
 * @value: the value to set the environment variable to
 *
 * Return: Always 0
 */
int set_env_variable(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_len(var) + str_len(value) + 2);
	if (!buf)
		return (1);
	string_copy(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		p = str_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

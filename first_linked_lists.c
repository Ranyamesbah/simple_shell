#include "header_main.h"

/**
 * list_length - Determines the length of a linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return count;
}

/**
 * list_to_array - Returns an array of strings from the list->str.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings or NULL on failure.
 */
char **list_to_array(list_t *head)
{
	list_t *node = head;
	size_t count = list_length(head);
	size_t i;
	char **str_array;
	char *str;

	if (!head || !count)
		return NULL;

	str_array = malloc(sizeof(char *) * (count + 1));
	if (!str_array)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(str_array[j]);
			free(str_array);
			return NULL;
		}
		str = string_copy(str, node->str);
		str_array[i] = str;
	}
	str_array[i] = NULL;
	return str_array;
}

/**
 * print_list_items - Prints all elements of a list_t linked list.
 * @head: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_items(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		print_string(convert_to_string(head->num, 10, 0));
		write_character(':');
		write_character(' ');
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		count++;
	}
	return count;
}

/**
 * node_with_prefix - Returns the node whose string starts with a prefix.
 * @head: Pointer to the list head.
 * @prefix: String to match.
 * @c: The next character after prefix to match.
 *
 * Return: The matching node or NULL.
 */
list_t *node_with_prefix(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = str_starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return head;
		head = head->next;
	}
	return NULL;
}

/**
 * get_node_index - Gets the index of a node.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: Index of node or -1.
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}
	return -1;
}

#include "header_main.h"

/**
 * add_node_at_beginning - Adds a new node to the beginning of the list
 * @head: Pointer to pointer of head node
 * @str: String field of the new node
 * @num: Node index used by history
 *
 * Return: Pointer to the new head node
 */
list_t *add_node_at_beginning(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);

	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);

	custom_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;

	if (str)
	{
		new_head->str = string_duplicate(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}

	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_at_end - Adds a new node to the end of the list
 * @head: Pointer to pointer of head node
 * @str: String field of the new node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node_at_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *current_node;

	if (!head)
		return (NULL);

	current_node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	custom_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = string_duplicate(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;

		current_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}

/**
 * print_list_strings - Prints only the `str` field of a linked list
 * @h: Pointer to the head node
 *
 * Return: Number of nodes in the list
 */
size_t print_list_strings(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		print_string(h->str ? h->str : "(nil)");
		print_string("\n");
		h = h->next;
		count++;
	}

	return (count);
}

/**
 * delete_node_by_index - Deletes a node at a given index
 * @head: Pointer to pointer of head node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_by_index(list_t **head, unsigned int index)
{
	list_t *current_node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}

	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			prev_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}

		i++;
		prev_node = current_node;
		current_node = current_node->next;
	}

	return (0);
}

/**
 * free_list_nodes - Frees all nodes of a linked list
 * @head_ptr: Pointer to pointer of head node
 *
 * Return: void
 */
void free_list_nodes(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	current_node = head;
	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->str);
		free(current_node);
		current_node = next_node;
	}

	*head_ptr = NULL;
}

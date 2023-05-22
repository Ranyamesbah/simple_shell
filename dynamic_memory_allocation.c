#include "header_main.h"

/**
 * custom_memset - Fills memory with a constant byte
 * @s: Pointer to the memory area to be filled
 * @b: The byte to fill the memory with
 * @n: The number of bytes to be filled
 *
 * Return: Pointer to the memory area @s
 */
char *custom_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * free_string_array - Frees an array of strings
 * @str_arr: The array of strings to be freed
 *
 * Return: void
 */
void free_string_array(char **str_arr)
{
	char **temp_ptr = str_arr;

	if (!str_arr)
		return;

	while (*str_arr)
		free(*str_arr++);

	free(temp_ptr);
}

/**
 * custom_realloc - Reallocates a block of memory
 * @ptr: Pointer to the previously allocated memory block
 * @old_size: Size of the previous memory block in bytes
 * @new_size: Size of the new memory block in bytes
 *
 * Return: Pointer to the new memory block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));

	if (!new_size)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (new_ptr);
}

#include "header_main.h"

/**
 * free_and_nullify_ptr - Frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_nullify_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);  // Freed successfully
	}
	return (0);  // Pointer was already NULL or not valid
}

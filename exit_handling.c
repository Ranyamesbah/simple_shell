#include "header_main.h"

/**
 * copy_string - Copies a string.
 * @dest: The destination string to copy to.
 * @src: The source string to copy from.
 * @n: The number of characters to copy.
 *
 * Return: A pointer to the copied string.
 */
char *copy_string(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * concatenate_strings - Concatenates two strings.
 * @dest: The first string to concatenate.
 * @src: The second string to concatenate.
 * @n: The maximum number of bytes to use.
 *
 * Return: A pointer to the concatenated string.
 */
char *concatenate_strings(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * find_character - Locates a character in a string.
 * @s: The string to search.
 * @c: The character to find.
 *
 * Return: A pointer to the first occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char *find_character(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

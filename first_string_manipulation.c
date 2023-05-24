#include "header_main.h"

/**
 * string_copy - Copies a string from source to destination
 * @dest: Pointer to the destination string
 * @src: Pointer to the source string
 *
 * Return: Pointer to the destination string
 */
char *string_copy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return (dest);

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * string_duplicate - Duplicates a given string
 * @str: Pointer to the string to be duplicated
 *
 * Return: Pointer to the duplicated string
 */
char *string_duplicate(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * print_string - Prints a given string to stdout
 * @str: Pointer to the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		write_character(str[i]);
		i++;
	}
}

/**
 * write_character - Writes a given character to stdout
 * @c: The character to be written
 *
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

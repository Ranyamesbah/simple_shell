#include "header_main.h"

/**
 * str_len - Returns the length of a string
 * @s: The string whose length to check
 *
 * Return: Integer length of the string
 */
int str_len(char *s)
{
	int length = 0;

	if (!s)
		return (0);

	while (*s++)
		length++;

	return (length);
}

/**
 * str_cmp - Performs lexicographic comparison of two strings
 * @s1: The first string
 * @s2: The second string
 *
 * Return: Negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * str_starts_with - Checks if a string starts with a given substring
 * @haystack: String to search
 * @needle: The substring to find
 *
 * Return: Address of the next character of haystack or NULL
 */
char *str_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
			return (NULL);
	}

	return ((char *)haystack);
}

/**
 * str_cat - Concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: Pointer to the destination buffer
 */
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;

	return (ret);
}

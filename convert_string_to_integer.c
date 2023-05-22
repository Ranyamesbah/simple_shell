#include "header_main.h"

/**
 * is_interactive_mode - Determines whether the shell is running in interactive
 * mode.
 * @info: A struct containing information about the shell.
 *
 * Return: 1 if the shell is running in interactive mode, 0 otherwise.
 */
int is_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_char_delimiter - Checks if a character is a delimiter.
 * @c: The character to check.
 * @delim: A string containing the delimiter characters to check against.
 *
 * Return: 1 if 'c' is a delimiter, 0 otherwise.
 */
int is_char_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
	return (0);
}

/**
 * is_alpha_char - Checks whether a character is alphabetic.
 * @c: The character to check.
 *
 * Return: 1 if 'c' is an alphabetic character (i.e., a letter), 0 otherwise.
 */
int is_alpha_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_to_int - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in string, converted number otherwise.
 */
int str_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

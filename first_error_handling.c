#include "header_main.h"

/**
 * _str_to_int - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: the integer value of the string, or -1 if the string
 *         does not contain a valid integer or if the integer
 *         value is out of range.
 */
int _str_to_int(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message to standard error
 * @info: a pointer to the parameter and return info struct
 * @estr: the error message to print
 *
 * This function prints an error message to standard error. The
 * message includes the name of the file, the line number, the
 * name of the program, and the specified error message.
 */
void print_error(info_t *info, char *estr)
{
	_print_str_stderr(info->fname);
	_print_str_stderr(": ");
	print_d(info->line_count, STDERR_FILENO);
	_print_str_stderr(": ");
	_print_str_stderr(info->argv[0]);
	_print_str_stderr(": ");
	_print_str_stderr(estr);
}

/**
 * print_d - prints an integer to the specified file descriptor
 * @input: the integer to print
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters printed
 *
 * This function prints an integer to the specified file descriptor.
 * If the integer is negative, a leading minus sign is printed. The
 * function always returns the number of characters printed.
 */
int print_d(int input, int fd)
{
	int (*__write_character)(char) = write_character;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__write_character = _putchar_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__write_character('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__write_character('0' + current / i);
			count++;
		}
		current %= i;
	}
	__write_character('0' + current);
	count++;

	return (count);
}

/**
 * convert_to_string - converts a long integer to a string representation
 * @num: the number to be converted
 * @base: the base to convert to
 * @flags: argument flags
 *
 * Return: pointer to the resulting string
 */
char *convert_to_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @buf: pointer to the string to be modified
 *
 * Return: None
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

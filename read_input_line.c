#include "header_main.h"

/**
 * input_buffer - reads and buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of length variable
 *
 * Return: bytes read
 */
ssize_t input_buffer(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			add_history(info, *buf, info->histcount++);
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line of input minus the newline character
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	write_character(BUF_FLUSH);
	r = input_buffer(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size of buffer
 *
 * Return: number of bytes read, or -1 on failure
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size)
{
	ssize_t bytes_read = 0;

	if (*size)
		return (0);

	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*size = bytes_read;

	return (bytes_read);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: number of characters read, or -1 on failure
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, chars_read = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		chars_read = *length;

	if (i == len)
		i = len = 0;

	bytes_read = read_buffer(info, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = find_character(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = custom_realloc(p, chars_read, chars_read ? chars_read + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (chars_read)
		concatenate_strings(new_p, buffer + i, k - i);
	else
		copy_string(new_p, buffer + i, k - i + 1);

	chars_read += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = chars_read;

	*ptr = p;
	return (chars_read);
}

/**
 * sigint_handler - handles SIGINT signal (Ctrl+C)
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	print_string("\n");
	print_string("$ ");
	write_character(BUF_FLUSH);
}

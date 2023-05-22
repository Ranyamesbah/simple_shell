#include "header_main.h"

/**
 * get_history_filepath - gets the history file path
 * @info: parameter struct
 * Return: allocated string containing history file path
 */
char *get_history_filepath(info_t *info)
{
	char *home_dir, *file_path;

	home_dir = get_env_value(info, "HOME=");
	if (!home_dir)
		return NULL;

	file_path = malloc(sizeof(char) * (str_len(home_dir) + str_len(HIST_FILE) + 2));
	if (!file_path)
		return NULL;

	string_copy(file_path, home_dir);
	str_cat(file_path, "/");
	str_cat(file_path, HIST_FILE);

	return file_path;
}

/**
 * write_history_file - writes history to a file
 * @info: the parameter struct
 * Return: 1 on success, -1 on failure
 */
int write_history_file(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_filepath(info);
	list_t *node;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		_print_str_fd(node->str, fd);
		_putchar_fd('\n', fd);
	}

	_putchar_fd(BUF_FLUSH, fd);
	close(fd);

	return 1;
}

/**
 * read_history_file - reads history from a file
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history_file(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_filepath(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return 0;

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return 0;

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return 0;

	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;

	if (rdlen <= 0)
		return free(buf), 0;

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			add_history(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
		add_history(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		delete_node_by_index(&(info->history), 0);

	update_history(info);
	return info->histcount;
}

/**
 * add_history - adds an entry to the history linked list
 * @info: structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */
int add_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_at_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return 0;
}

/**
 * update_history - renumbers the history linked list after changes
 * @info: structure containing potential arguments
 * Return: the new histcount
 */
int update_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->histcount = i;
}


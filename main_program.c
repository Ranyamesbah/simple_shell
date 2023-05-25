#include "header_main.h"

/**
 * main - Entry point for the program.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Return: 0 on success, 1 on error.
 */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r"(fd)
	    : "r"(fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_print_str_stderr(argv[0]);
				_print_str_stderr(": 0: Failed to open ");
				_print_str_stderr(argv[1]);
				_putchar_stderr('\n');
				_putchar_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history_file(info);
	shell_loop(info, argv);
	return (EXIT_SUCCESS);
}

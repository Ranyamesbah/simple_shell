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
	ShellInfo shellInfo = SHELL_INFO_INIT;
	int fileDescriptor = 2;

	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r"(fileDescriptor)
	    : "r"(fileDescriptor));

	if (argc == 2)
	{
		fileDescriptor = open(argv[1], O_RDONLY);
		if (fileDescriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printStringStderr(argv[0]);
				printStringStderr(": 0: Failed to open ");
				printStringStderr(argv[1]);
				writeCharacterStderr('\n');
				flushBufferStderr();
				exit(127);
			}
			return EXIT_FAILURE;
		}
		shellInfo.readfd = fileDescriptor;
	}

	populateEnvList(&shellInfo);
	readHistoryFile(&shellInfo);
	shellLoop(&shellInfo, argv);

	return EXIT_SUCCESS;
}

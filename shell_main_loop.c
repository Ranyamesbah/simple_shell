#include "header_main.h"

/**
 * shellLoop - main shell loop
 * @shellInfo: pointer to struct containing information about the shell session
 * @arguments: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shellLoop(ShellInfo *shellInfo, char **arguments)
{
	ssize_t readStatus = 0;
	int builtinResult = 0;

	while (readStatus != -1 && builtinResult != -2)
	{
		clearShellInfo(shellInfo);
		if (isInteractiveMode(shellInfo))
			printString("$ ");
		flushBuffer();
		readStatus = getInput(shellInfo);
		if (readStatus != -1)
		{
			setShellInfo(shellInfo, arguments);
			builtinResult = findBuiltin(shellInfo);
			if (builtinResult == -1)
				findCommand(shellInfo);
		}
		else if (isInteractiveMode(shellInfo))
			writeCharacter('\n');
		freeShellInfo(shellInfo, 0);
	}
	writeHistoryFile(shellInfo);
	freeShellInfo(shellInfo, 1);
	if (!isInteractiveMode(shellInfo) && shellInfo->status)
		exit(shellInfo->status);
	if (builtinResult == -2)
	{
		if (shellInfo->errorCode == -1)
			exit(shellInfo->status);
		exit(shellInfo->errorCode);
	}
	return builtinResult;
}

/**
 * findBuiltin - finds a builtin command
 * @shellInfo: pointer to struct containing information about the shell session
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int findBuiltin(ShellInfo *shellInfo)
{
	int i, builtinResult = -1;
	BuiltinTable builtinTable[] = {
		{"exit", exitCommand},
		{"env", printEnv},
		{"help", helpCommand},
		{"history", historyCommand},
		{"setenv", setEnvValue},
		{"unsetenv", unsetEnvValue},
		{"cd", cdCommand},
		{"alias", aliasCommand},
		{NULL, NULL}
	};

	for (i = 0; builtinTable[i].name; i++)
	{
		if (strCmp(shellInfo->arguments[0], builtinTable[i].name) == 0)
		{
			shellInfo->lineCount++;
			builtinResult = builtinTable[i].function(shellInfo);
			break;
		}
	}
	return builtinResult;
}

/**
 * findCommand - finds a command in the PATH directories.
 * @shellInfo: pointer to the ShellInfo struct.
 *
 * Return: void.
 */
void findCommand(ShellInfo *shellInfo)
{
	char *path = NULL;
	int i, count = 0;

	shellInfo->path = shellInfo->arguments[0];
	if (shellInfo->lineCountFlag == 1)
	{
		shellInfo->lineCount++;
		shellInfo->lineCountFlag = 0;
	}

	for (i = 0; shellInfo->arg[i]; i++)
	{
		if (!isCharDelimiter(shellInfo->arg[i], " \t\n"))
			count++;
	}

	if (!count)
		return;

	path = findCommandPath(shellInfo, getEnvValue(shellInfo, "PATH="), shellInfo->arguments[0]);
	if (path)
	{
		shellInfo->path = path;
		executeCommand(shellInfo);
	}
	else
	{
		if ((isInteractiveMode(shellInfo) || getEnvValue(shellInfo, "PATH=")
			|| shellInfo->arguments[0][0] == '/') && isCommand(shellInfo, shellInfo->arguments[0]))
			executeCommand(shellInfo);
		else if (*(shellInfo->arg) != '\n')
		{
			shellInfo->status = 127;
			printError(shellInfo, "not found\n");
		}
	}
}

/**
 * executeCommand - forks and executes a new process to run the command.
 * @shellInfo: pointer to the ShellInfo struct.
 *
 * Return: void.
 */
void executeCommand(ShellInfo *shellInfo)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{
		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(shellInfo->path, shellInfo->arguments, getEnvironmentStrings(shellInfo)) == -1)
		{
			freeShellInfo(shellInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(shellInfo->status));
		if (WIFEXITED(shellInfo->status))
		{
			shellInfo->status = WEXITSTATUS(shellInfo->status);
			if (shellInfo->status == 126)
				printError(shellInfo, "Permission denied\n");
		}
	}
}

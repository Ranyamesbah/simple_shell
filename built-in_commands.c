#include "header_main.h"

/**
 * exit_cmd - exits the shell
 * @info: pointer to a structure containing potential arguments
 * Return: exits with a given exit status (0) if info->argv[0] != "exit"
 */
int exit_cmd(info_t *info)
{
	int exit_status;

	if (info->argv[1])
	{
		exit_status = str_to_int(info->argv[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			print_str_stderr(info->argv[1]);
			putchar_stderr('\n');
			return 1;
		}
		info->err_num = str_to_int(info->argv[1]);
		return -2;
	}
	info->err_num = -1;
	return -2;
}

/**
 * cd_cmd - changes the current directory of the process
 * @info: pointer to a structure containing potential arguments
 * Return: Always 0
 */
int cd_cmd(info_t *info)
{
	char *current_dir, *dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		print_string("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		dir = get_env_value(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env_value(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env_value(info, "OLDPWD="))
		{
			print_string(current_dir);
			putchar('\n');
			return 1;
		}
		print_string(get_env_value(info, "OLDPWD="));
		putchar('\n');
		chdir_ret = chdir((dir = get_env_value(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		print_str_stderr(info->argv[1]);
		putchar_stderr('\n');
	}
	else
	{
		set_env_variable(info, "OLDPWD", get_env_value(info, "PWD="));
		set_env_variable(info, "PWD", getcwd(buffer, 1024));
	}

	return 0;
}

/**
 * help_cmd - prints help information for the shell
 * @info: pointer to a structure containing potential arguments
 * Return: Always 0
 */
int help_cmd(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_string("help call works. Function not yet implemented \n");

	if (0)
		print_string(*arg_array);

	return 0;
}
 

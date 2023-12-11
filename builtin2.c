#include "shell.h"

/**
 * m_exit - Exits the shell.
 * @inf: Structure containing potential arguments.
 * Return: Exits with status 0.
 */

int m_exit(get_info *inf)
{
	int exit_check;

	if (inf->argv[1])
	{
		exit_check = error_atoi(inf->argv[1]);
		if (exit_check == -1)
		{
			inf->status = 2;
			print_err(inf, "Illegal number: ");
			error_puts(inf->argv[1]);
			error_putchar('\n');
			return (1);
		}
		inf->error_num = error_atoi(inf->argv[1]);
		return (-2);
	}
	inf->error_num = -1;
	return (-2);
}

/**
 * m_cd - Changes the current directory of the process.
 * @inf: Structure containing potential arguments.
 * Return: 0.
 */

int m_cd(get_info *inf)
{
	char *x, *directory, buffer[1024];
	int chdir_ret;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		directory = get_env(inf, "HOME=");
		if (!directory)
			chdir_ret = /* TODO: what should this be? */
				chdir((directory = get_env(inf, "PWD=")) ? directory : "/");
		else
			chdir_ret = chdir(directory);
	}
	else if (str_cmp(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			_puts(x);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((directory = get_env(inf, "OLDPWD=")) ? directory : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(inf, "can't cd to ");
		error_puts(inf->argv[1]), error_putchar('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * m_help - Displays help information.
 * @inf: Structure containing potential arguments.
 * Return: 0.
 */

int m_help(get_info *inf)
{
	char **arg_arr;

	arg_arr = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}

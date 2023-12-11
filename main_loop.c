#include "shell.h"

/**
 * shell_loop - Main shell loop.
 * @inf: The parameter and return inf struct.
 * @av: The argument vector from main.
 * Return: 0 on success, 1 on error, or error code.
 */

int shell_loop(get_info *inf, char **av)
{
	ssize_t x = 0;
	int ret = 0;

	while (x != -1 && ret != -2)
	{
		c_inf(inf);
		if (int_active(inf))
			_puts("$ ");
		error_putchar(FLUSH);
		x = g_input(inf);
		if (x != -1)
		{
			set_inf(inf, av);
			ret = get_builtin(inf);
			if (ret == -1)
				get_cmd(inf);
		}
		else if (int_active(inf))
			_putchar('\n');
		f_inf(inf, 0);
	}
	w_history(inf);
	f_inf(inf, 1);
	if (!int_active(inf) && inf->status)
		exit(inf->status);
	if (ret == -2)
	{
		if (inf->error_num == -1)
			exit(inf->status);
		exit(inf->error_num);
	}
	return (ret);
}

/**
 * get_builtin - Finds a built-in command.
 * @inf: The parameter and return inf struct.
 * Return: 0, -1, 1, or -2.
 */

int get_builtin(get_info *inf)
{
	int x, ret = -1;
	built_in bl[] = {
		{"exit", m_exit},
		{"env", m_env},
		{"help", m_help},
		{"history", m_history},
		{"setenv", m_set_env},
		{"unsetenv", m_unset_env},
		{"cd", m_cd},
		{"alias", m_alias},
		{NULL, NULL}
	};

	for (x = 0; bl[x].type; x++)
		if (str_cmp(inf->argv[0], bl[x].type) == 0)
		{
			inf->count_line++;
			ret = bl[x].fun(inf);
			break;
		}
	return (ret);
}

/**
 * get_cmd - Finds a command in PATH.
 * @inf: The parameter and return inf struct.
 * Return: Void.
 */

void get_cmd(get_info *inf)
{
	char *path = NULL;
	int x, z;

	inf->path = inf->argv[0];
	if (inf->flag_count_line == 1)
	{
		inf->count_line++;
		inf->flag_count_line = 0;
	}
	for (x = 0, z = 0; inf->arg[x]; x++)
		if (!is_delimeter(inf->arg[x], " \t\n"))
			z++;
	if (!z)
		return;

	path = get_path(inf, get_env(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		_fork(inf);
	}
	else
	{
		if ((int_active(inf) || get_env(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_command(inf, inf->argv[0]))
			_fork(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_err(inf, "not found\n");
		}
	}
}

/**
 * _fork - Forks an exec thread to run cmd.
 * @inf: The parameter and return inf struct.
 * Return: Void.
 */

void _fork(get_info *inf)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(inf->path, inf->argv, g_env(inf)) == -1)
		{
			f_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_err(inf, "Permission denied\n");
		}
	}
}

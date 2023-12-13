#include "shell.h"

/**
 * is_command - Determines if a file is an executable command.
 * @inf: The inf struct.
 * @p: Path to the file.
 *
 * Return:  0 || 1
 */

int is_command(get_info *inf, char *p)
{
	struct stat st;

	(void)inf;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_char - Duplicates characters.
 * @p_str: The PATH string.
 * @idx1: Starting index.
 * @idx2: Stopping index.
 *
 * Return: Pointer to new buffer.
 */

char *duplicate_char(char *p_str, int idx1, int idx2)
{
	static char buffer[1024];
	int x = 0, z = 0;

	for (z = 0, x = idx1; x < idx2; x++)
		if (p_str[x] != ':')
			buffer[z++] = p_str[x];
	buffer[z] = 0;
	return (buffer);
}

/**
 * get_path - Finds this cmd in the PATH string.
 * @inf: The inf struct.
 * @p_str: The PATH string.
 * @cmd: The cmd to find.
 *
 * Return: Full path of cmd || NULL.
 */

char *get_path(get_info *inf, char *p_str, char *cmd)
{
	int x = 0, curr_pos = 0;
	char *p;

	if (!p_str)
		return (NULL);
	if ((str_len(cmd) > 2) && starts_w(cmd, "./"))
	{
		if (is_command(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p_str[x] || p_str[x] == ':')
		{
			p = duplicate_char(p_str, curr_pos, x);
			if (!*p)
				str_cat(p, cmd);
			else
			{
				str_cat(p, "/");
				str_cat(p, cmd);
			}
			if (is_command(inf, p))
				return (p);
			if (!p_str[x])
				break;
			curr_pos = x;
		}
		x++;
	}
	return (NULL);
}

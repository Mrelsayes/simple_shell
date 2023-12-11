#include "shell.h"

/**
 * g_history - Gets the history file.
 * @inf: Parameter struct.
 * Return: Allocated string containing the history file.
 */

char *g_history(get_info *inf)
{
	char *buffer, *d;

	d = get_env(inf, "HOME=");
	if (!d)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_len(d) + str_len(FILE_HISTORY) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	str_cpy(buffer, d);
	str_cat(buffer, "/");
	str_cat(buffer, FILE_HISTORY);
	return (buffer);
}

/**
 * w_history - Creates a file or appends to an existing file.
 * @inf: The parameter struct.
 * Return: 1 on success, else -1.
 */

int w_history(get_info *inf)
{
	ssize_t fd;
	char *fname = g_history(inf);
	str_list *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r_history - Reads history from a file.
 * @inf: The parameter struct.
 * Return: count_history on success, 0 otherwise.
 */

int r_history(get_info *inf)
{
	int x, last = 0, lcount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *fname = g_history(inf);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buffer[x] == '\n')
		{
			buffer[x] = 0;
			history_list(inf, buffer + last, lcount++);
			last = x + 1;
		}
	if (last != x)
		history_list(inf, buffer + last, lcount++);
	free(buffer);
	inf->count_history = lcount;
	while (inf->count_history-- >= MAX_HISTORY)
		rm_start_node(&(inf->history), 0);
	save_history(inf);
	return (inf->count_history);
}

/**
 * history_list - Adds an entry to a history linked list.
 * @inf: Structure containing potential arguments.
 * @buffer: Buffer.
 * @lcount: The history line count, count_history.
 * Return: Always 0.
 */

int history_list(get_info *inf, char *buffer, int lcount)
{
	str_list *node = NULL;

	if (inf->history)
		node = inf->history;
	node_end(&node, buffer, lcount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * save_history - Renumbers the history linked list after changes.
 * @inf: Structure containing potential arguments.
 * Return: The new count_history.
 */

int save_history(get_info *inf)
{
	str_list *node = inf->history;
	int x = 0;

	while (node)
	{
		node->number = x++;
		node = node->next;
	}
	return (inf->count_history = x);
}

#include "shell.h"

/**
 * input_buf - Buffers chained commands.
 * @inf: Parameter struct.
 * @buffer: Address of the buffer.
 * @len: Address of the len variable.
 * Return: Bytes read.
 */

ssize_t input_buf(get_info *inf, char **buffer, size_t *len)
{
	ssize_t x = 0;
	size_t _len = 0;

	if (!*len)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sig_h);
#if USE_GETLINE
		x = getline(buffer, &_len, stdin);
#else
		x = g_line(inf, buffer, &_len);
#endif
		if (x > 0)
		{
			if ((*buffer)[x - 1] == '\n')
			{
				(*buffer)[x - 1] = '\0';
				x--;
			}
			inf->flag_count_line = 1;
			comment_rm(*buffer);
			history_list(inf, *buffer, inf->count_history++);
			{
				*len = x;
				inf->cmd_buffer = buffer;
			}
		}
	}
	return (x);
}

/**
 * g_input - Gets a line minus the newline.
 * @inf: Parameter struct.
 * Return: Bytes read.
 */

ssize_t g_input(get_info *inf)
{
	static char *buffer;
	static size_t i, j, len;
	ssize_t x = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(FLUSH);
	x = input_buf(inf, &buffer, &len);
	if (x == -1) /* EOF */
		return (-1);
	if (len)
	{
		j = i;
		p = buffer + i;

		chain_checker(inf, buffer, &j, i, len);
		while (j < len)
		{
			if (ischain(inf, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->type_cmd_buffer = NORM_COMMAND;
		}

		*buf_p = p;
		return (str_len(p));
	}

	*buf_p = buffer;
	return (x);
}

/**
 * read_buf - Reads a buffer.
 * @inf: Parameter struct.
 * @buffer: Buffer.
 * @i: Size.
 * Return: x.
 */

ssize_t read_buf(get_info *inf, char *buffer, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(inf->r_fd, buffer, R_BUFF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}

/**
 * g_line - Gets the next line of input from STDIN.
 * @inf: Parameter struct.
 * @ptr: Address of a pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 * Return: s.
 */

int g_line(get_info *inf, char **ptr, size_t *length)
{
	static char buffer[R_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t x = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	x = read_buf(inf, buffer, &len);
	if (x == -1 || (x == 0 && len == 0))
		return (-1);

	c = str_chr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = re_alloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		strn_cat(new_p, buffer + i, k - i);
	else
		strn_cpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sig_h - Blocks Ctrl-C.
 * @sig_num: The signal number.
 * Return: Void.
 */

void sig_h(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(FLUSH);
}

#include "shell.h"

/**
 * error_atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: 0 || -1
 */

int error_atoi(char *str)
{
	int x = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (x = 0;  str[x] != '\0'; x++)
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			result *= 10;
			result += (str[x] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - Prints an error message.
 * @inf: The parameter and return inf struct.
 * @str: String containing the specified error type.
 *
 * Return: 0 || -1
 */

void print_err(get_info *inf, char *str)
{
	error_puts(inf->file_name);
	error_puts(": ");
	print_dec(inf->count_line, STDERR_FILENO);
	error_puts(": ");
	error_puts(inf->argv[0]);
	error_puts(": ");
	error_puts(str);
}

/**
 * print_dec - Prints a decimal integer num base 10.
 * @in: The in.
 * @fd: The file descriptor to write to.
 *
 * Return: The num of characters.
 */

int print_dec(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int x, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		count++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (x = 1000000000; x > 1; x /= 10)
	{
		if (_abs_ / x)
		{
			__putchar('0' + current / x);
			count++;
		}
		current %= x;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * number_converter - Converter function, a clone of atoi.
 * @num: Number.
 * @base: Base.
 * @flag: Argument flag.
 *
 * Return: String.
 */

char *number_convertor(long int num, int base, int flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flag & UNSIGNED_CONV) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flag & LOWERCASE_CONV ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * comment_rm - Replaces the first instance of '#' with '\0'.
 * @buffer: Address of the string to modify.
 *
 * Return: 0.
 */

void comment_rm(char *buffer)
{
	int x;

	for (x = 0; buffer[x] != '\0'; x++)
		if (buffer[x] == '#' && (!x || buffer[x - 1] == ' '))
		{
			buffer[x] = '\0';
			break;
		}
}

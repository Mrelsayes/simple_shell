#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define NORM_COMMAND	0
#define OR_COMMAND		1
#define AND_COMMAND		2
#define COMMAND_CHAIN	3
#define GETLINE 0
#define R_BUFF_SIZE 1024
#define W_BUFF_SIZE 1024
#define FLUSH -1
#define STRTOK 0
#define LOWERCASE_CONV	1
#define UNSIGNED_CONV	2
#define FILE_HISTORY	".simple_shell_history"
#define MAX_HISTORY	4096
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


extern char **environ;


/**
 * struct string_list - singl linked list
 * @number: Field representing a number.
 * @str: Field representing a string.
 * @next: Pointer to the next node in the list.
 */

typedef struct string_list
{
	int number;
	char *str;
	struct string_list *next;
} str_list;

/**
 * struct get_info - Contains pseudo-arguments to pass into a function.
 * @arg: String generated from getline containing arguments.
 * @argv: Array of strings generated from arg.
 * @path: Path string for the current command.
 * @argc: Argument count.
 * @count_line: Error count.
 * @error_num: Error code for exit()s.
 * @flag_count_line: Whether to count this line of input.
 * @file_name: Program filename.
 * @env: Local copy of environ.
 * @environ: Modified copy of environ.
 * @history: History node.
 * @alias: Alias node.
 * @changed_environ: Whether environ was changed.
 * @status: Return status of the last executed command.
 * @cmd_buffer: Address of a pointer to cmd_buffer, if chaining.
 * @type_cmd_buffer: Type of cmd buffer.
 * @r_fd: File descriptor for reading line input.
 * @count_history: History line number count.
 */

typedef struct get_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int count_line;
	int error_num;
	int flag_count_line;
	char *file_name;
	str_list *env;
	str_list *history;
	str_list *alias;
	char **environ;
	int changed_environ;
	int status;

	char **cmd_buffer;
	int type_cmd_buffer;
	int r_fd;
	int count_history;
} get_info;


/**
 * struct built_in - Holds a built-in string and its associated function.
 * @type: Flag indicating the built-in command.
 * @fun: Pointer to the associated function.
 */

typedef struct built_in
{
	char *type;
	int (*fun)(get_info *);
} built_in;


char *starts_w(const char *, const char *);
int _putchar(char);
int put_fd(char c, int fd);
int error_putchar(char);
char *str_cat(char *, char *);
void _fork(get_info *);
int shell_loop(get_info *, char **);
void get_cmd(get_info *);
int str_cmp(char *, char *);
void error_puts(char *);
int is_command(get_info *, char *);
void _puts(char *);
char *str_cpy(char *, char *);
char *get_path(get_info *, char *, char *);
int get_builtin(get_info *);
char *duplicate_char(char *, int, int);
char *str_dup(const char *);
int str_len(char *);
char *str_cpy(char *, char *);
int puts_fd(char *str, int fd);
int error_atoi(char *);
void *re_alloc(void *, unsigned int, unsigned int);
void comment_rm(char *);
char **str_tow(char *, char *);
int buffer_free(void **);
int _atoi(char *);
char **str_tow2(char *, char);
int is_delimeter(char, char *);
int _isalpha(int);
int int_active(get_info *);
char *mem_set(char *, char, unsigned int);
void str_free(char **);
char *str_chr(char *, char);
void print_err(get_info *, char *);
char *number_convertor(long int, int, int);
int print_dec(int, int);
char *strn_cat(char *, char *, int);
char *strn_cpy(char *, char *, int);
int m_exit(get_info *);
int m_cd(get_info *);
int m_help(get_info *);
int m_history(get_info *);
int m_alias(get_info *);
ssize_t g_input(get_info *);
int g_line(get_info *, char **, size_t *);
void sig_h(int);
void c_inf(get_info *);
void set_inf(get_info *, char **);
void f_inf(get_info *, int);
char *get_env(get_info *, const char *);
int m_env(get_info *);
int m_set_env(get_info *);
int m_unset_env(get_info *);
int p_env_llist(get_info *);
int string_changer(char **, char *);
char **g_env(get_info *);
int r_history(get_info *info);
int save_history(get_info *info);
int set_env(get_info *, char *, char *);
int alias_changer(get_info *);
size_t print_string_list(const str_list *);
int unset_env(get_info *, char *);
str_list *add_start_node(str_list **, const char *, int);
ssize_t get_start_node(str_list *, str_list *);
int ischain(get_info *, char *, size_t *);
int w_history(get_info *info);
str_list *node_start(str_list *, char *, char);
int var_changer(get_info *);
int history_list(get_info *info, char *buf, int linecount);
size_t listlen(const str_list *);
void freel(str_list **);
char *g_history(get_info *info);
void chain_checker(get_info *, char *, size_t *, size_t, size_t);
int rm_start_node(str_list **, unsigned int);
str_list *node_end(str_list **, const char *, int);
size_t print_lists(const str_list *);
char **liststr(str_list *);

#endif

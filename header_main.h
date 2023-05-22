#ifndef _SHELL_H_
#define _SHELL_H_

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

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* filename: shell_main_loop.c */
int shell_loop(info_t *, char **);
int find_builtin(info_t *);
void find_command(info_t *);
void execute_command(info_t *);

/* filename: command_line_parser.c */
int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

/* filename: error_handling.c */
void _print_str_stderr(char *);
int _putchar_stderr(char);
int _putchar_fd(char c, int fd);
int _print_str_fd(char *str, int fd);

/* filename: string_manipulation.c */
int str_len(char *);
int str_cmp(char *, char *);
char *str_starts_with(const char *, const char *);
char *str_cat(char *, char *);

/* filename: first_string_manipulation.c */
char *string_copy(char *, char *);
char *string_duplicate(const char *);
void print_string(char *);
int write_character(char);

/* filename: exit_handling.c */
char *copy_string(char *, char *, int);
char *concatenate_strings(char *, char *, int);
char *find_character(char *, char);

/* filename: command_line_tokenizer.c */
char **strtow_delim(char *, char *);
char **strtow(char *, char);

/* filename: dynamic_memory_allocation.c */
char *custom_memset(char *, char, unsigned int);
void free_string_array(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* filename: memory_management.c */
int free_and_nullify_ptr(void **);

/* filename: convert_string_to_integer.c */
int is_interactive_mode(info_t *);
int is_char_delimiter(char, char *);
int is_alpha_char(int);
int str_to_int(char *);

/* filename: first_error_handling.c */
int _str_to_int(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_to_string(long int, int, int);
void remove_comments(char *);

/* filename: built-in_commands.c */
int exit_cmd(info_t *);
int cd_cmd(info_t *);
int help_cmd(info_t *);

/* filename: first_built-in_command.c */
int history_cmd(info_t *);
int alias_cmd(info_t *);

/* filename: read_input_line.c */
ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sigint_handler(int);

/* filename: get_system_info.c */
void clear_info_struct(info_t *);
void set_info_struct(info_t *, char **);
void free_info_struct(info_t *, int);

/* filename: environment_variables.c */
char *get_env_value(info_t *, const char *);
int print_env(info_t *);
int set_env_value(info_t *);
int unset_env_value(info_t *);
int populate_env_list(info_t *);

/* filename: get_environment_variable.c */
char **get_environ_strings(info_t *);
int delete_env_variable(info_t *, char *);
int set_env_variable(info_t *, char *, char *);

/* filename: command_history.c */
char *get_history_filepath(info_t *info);
int write_history_file(info_t *info);
int read_history_file(info_t *info);
int add_history(info_t *info, char *buf, int linecount);
int update_history(info_t *info);

/* filename: linked_lists.c */
list_t *add_node_at_beginning(list_t **, const char *, int);
list_t *add_node_at_end(list_t **, const char *, int);
size_t print_list_strings(const list_t *);
int delete_node_by_index(list_t **, unsigned int);
void free_list_nodes(list_t **);

/* filename: first_linked_lists.c */
size_t list_length(const list_t *);
char **list_to_array(list_t *);
size_t print_list_items(const list_t *);
list_t *node_with_prefix(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* filename: variable_handling.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
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
} x_list;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecounter_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfil_desc: the fil_desc from which to read line input
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
	int linecounter_flag;
	char *fname;
	x_list *env;
	x_list *history;
	x_list *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfil_desc;
	int histcount;
} x_info;

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
	int (*func)(x_info *);
} builtin_table;


/* toem_shloop.c */
int hsh(x_info *, char **);
int find_builtin(x_info *);
void find_cmd(x_info *);
void fork_cmd(x_info *);

/* toem_parser.c */
int is_cmd(x_info *, char *);
char *dup_chars(char *, int, int);
char *find_path(x_info *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfil_desc(char c, int fil_desc);
int _putsfil_desc(char *str, int fil_desc);

/* toem_string.c */
int _my_strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_my_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_my_strncat(char *, char *, int);
char *my_stringchar(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_my_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toemstr_2_int.c */
int open_session(x_info *);
int delim_check(char, char *);
int my_isalpha(int);
int str_2_int(char *);

/* toem_errors1.c */
int _errs2int(char *);
void prints_errors(x_info *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int my_exit(x_info *);
int my_cdir(x_info *);
int my_helper(x_info *);

/* toem_builtin1.c */
int my_previous(x_info *);
int _my_sh_alias(x_info *);

/*toem_getline.c */
ssize_t get_input(x_info *);
int _getline(x_info *, char **, size_t *);
void sigint_handler(int);

/* toem_getinfo.c */
void clear_info(x_info *);
void set_info(x_info *, char **);
void free_info(x_info *, int);

/* toem_environ.c */
char *_getenv(x_info *, const char *);
int _my_sh_env(x_info *);
int _mysetenv(x_info *);
int _myunsetenv(x_info *);
int populate_env_list(x_info *);

/* toem_getenv.c */
char **get_environ(x_info *);
int _unsetenv(x_info *, char *);
int _setenv(x_info *, char *, char *);

/* toem_history.c */
char *get_history_file(x_info *command);
int write_history(x_info *command);
int read_history(x_info *command);
int build_history_list(x_info *command, char *buf, int linecounter);
int renum_hist(x_info *command);

/* toem_lists.c */
x_list *add_node(x_list **, const char *, int);
x_list *add_node_end(x_list **, const char *, int);
size_t print_list_str(const x_list *);
int delete_node_key(x_list **, unsigned int);
void free_list(x_list **);

/* toem_lists1.c */
size_t list_len(const x_list *);
char **list_to_strings(x_list *);
size_t print_list(const x_list *);
x_list *node_prefix(x_list *, char *, char);
ssize_t get_node_key(x_list *, x_list *);

/* toem_vars.c */
int ch_delim(x_info *, char *, size_t *);
void check_chain(x_info *, char *, size_t *, size_t, size_t);
int replace_alias(x_info *);
int replaces_vals(x_info *);
int replace_string(char **, char *);

#endif

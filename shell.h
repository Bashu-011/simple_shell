#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3


/* Global environment for the shell code */
extern char **environment;
/* Name for the program*/
char *name;
/* Checker for history */
int history;

/**
 * struct y_list - struct of type defining a linked list.
 * @directory: directoryectory path.
 * @new: A pointer to another struct y_list.
 */
typedef struct y_list
{
	char *directory;
	struct y_list *new;
} x_list;

/**
 * struct builtinzz - new struct of type defining builtins commands
 * @name: name of the command.
 * @func_pointer: A function pointer to the builtin command's function.
 */
typedef struct builtinzz
{
	char *name;
	int (*func_pointer)(char **argv, char **duo_pointer);
} x_builtin;

/**
 * struct y_alias - new struct stating aliases.
 * @name: name of the alias.
 * @val: value of the alias.
 * @new: pointer to new struct y_alias.
 */
typedef struct y_alias
{
	char *name;
	char *val;
	struct y_alias *new;
} x_alias;

/* Linked lists for global aliase */
x_alias *aliases;

/* Helpers */
xsize _getline(char **line_pointer, x_size *n, FILE *input);
void *_allocator(void *pointer, unsigned int size_ptr, unsigned int mem_ptr);
char **string_token(char *line, char *delimiter);
char *command_in_path(char *command);
x_list *path_directory(char *x_paths);
int execution(char **args, char **duo_pointer);
void frees_list(x_list *top);
char *int_to_str(int numbs);

/* Error Handling in the program */
int give_error(char **args, int the_err);
char *global_error(char **args);
char *error_alias(char **args);
char *error_exit(char **args);
char *error_cd(char **args);
char *error_syntax(char **args);
char *permission_denied(char **args);
char *commands_not_found(char **args);

/* Handling inputs */
void line_handler(char **read_line, xsize read);
void replace_var(char **args, int *return_executed);
char *input_args(char *line, int *return_executed);
int calling_args(char **args, char **duo_pointer, int *return_executed);
int executes_commands(char **args, char **duo_pointer, int *return_executed);
int execution_of_args(int *return_executed);
int inspects_args(char **args);
void free_mem_args(char **args, char **duo_pointer);
char **alias_replace(char **args);

/* Builtins functions */
int (*builtin(char *input))(char **args, char **duo_pointer);
int sh_exit(char **args, char **duo_pointer);
int sh_env(char **args, char __attribute__((__unused__)) **duo_pointer);
int sh_setenv(char **args, char __attribute__((__unused__)) **duo_pointer);
int sh_unsetenv(char **args, char __attribute__((__unused__)) **duo_pointer);
int sh_cd(char **args, char __attribute__((__unused__)) **duo_pointer);
int sh_alias(char **args, char __attribute__((__unused__)) **duo_pointer);
int sh_help(char **args, char __attribute__((__unused__)) **duo_pointer);


/* Handling Strings */
int my_stringlen(const char *x);
char *my_strconcat(char *endpoint, const char *start);
char *my_str_concat(char *endpoint, const char *start, x_size n);
char *my_stringcopy(char *endpoint, const char *start);
char *my_stringxter(char *x, char y);
int my_prefix(char *x, char *allow);
int compare_string(char *x1, char *x2);
int compare_string2(const char *x1, const char *x2, x_size n);


/* Builtin Helpers */
char **create_copy(void);
void free_shell_env(void);
char **get_shel_env (const char *var);


/* Handling Linked lists */
x_alias *adds_alias(x_alias **top, char *name, char *val);
void linked_lists_free(x_alias *top);
x_list *node_end(x_list **top, char *directory);
void frees_list(x_list *top);

void h_all(void);
void h_alias(void);
void h_cd(void);
void h_exit(void);
void main_help(void);
void help_environment(void);
void h_setenv(void);
void h_unsetenv(void);
void h_history(void);

int run_file_commands(char *path_of_file, int *return_executed);
#endif /*_MY_SHELL_H_ */
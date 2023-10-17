#include "shell.h"

/**
* hsh - the main shell loop
* @command: the parameter & return command struct
* @av: the argument vector from main()
*
* Return: 0 on success, 1 on error, or error code
*/
int hsh(x_info *command, char **av)
{
ssize_t r = 0;
int builtin_ret = 0;

while (r != -1 && builtin_ret != -2)
{
clear_info(command);
if (open_session(command))
_puts("$ ");
_eputchar(BUF_FLUSH);
r = get_input(command);
if (r != -1)
{
set_info(command, av);
builtin_ret = find_builtin(command);
if (builtin_ret == -1)
find_cmd(command);
}
else if (open_session(command))
_putchar('\n');
free_info(command, 0);
}
write_history(command);
free_info(command, 1);
if (!open_session(command) && command->status)
exit(command->status);
if (builtin_ret == -2)
{
if (command->err_num == -1)
exit(command->status);
exit(command->err_num);
}
return (builtin_ret);
}

/**
* find_builtin - finds a builtin command
* @command: the parameter & return command struct
*
* Return: -1 if builtin not found,
*			0 if builtin executed successfully,
*			1 if builtin found but not successful,
*			-2 if builtin signals exit()
*/
int find_builtin(x_info *command)
{
int i, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", my_exit},
{"env", _my_sh_env},
{"help", my_helper},
{"history", my_previous},
{"setenv", _mysetenv},
{"unsetenv", _myunsetenv},
{"cd", my_cdir},
{"alias", _my_sh_alias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
if (_strcmp(command->argv[0], builtintbl[i].type) == 0)
{
command->line_count++;
built_in_ret = builtintbl[i].func(command);
break;
}
return (built_in_ret);
}

/**
* find_cmd - finds a command in PATH
* @command: the parameter & return command struct
*
* Return: void
*/
void find_cmd(x_info *command)
{
char *path = NULL;
int i, k;

command->path = command->argv[0];
if (command->linecounter_flag == 1)
{
command->line_count++;
command->linecounter_flag = 0;
}
for (i = 0, k = 0; command->arg[i]; i++)
if (!delim_check(command->arg[i], " \t\n"))
k++;
if (!k)
return;

path = find_path(command, _getenv(command, "PATH="), command->argv[0]);
if (path)
{
command->path = path;
fork_cmd(command);
}
else
{
if ((open_session(command) || _getenv(command, "PATH=")
|| command->argv[0][0] == '/') && is_cmd(command, command->argv[0]))
fork_cmd(command);
else if (*(command->arg) != '\n')
{
command->status = 127;
prints_errors(command, "not found\n");
}
}
}

/**
* fork_cmd - forks a an exec thread to run cmd
* @command: the parameter & return command struct
*
* Return: void
*/
void fork_cmd(x_info *command)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
/* TODO: PUT ERROR FUNCTION */
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(command->path, command->argv, get_environ(command)) == -1)
{
free_info(command, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(command->status));
if (WIFEXITED(command->status))
{
command->status = WEXITSTATUS(command->status);
if (command->status == 126)
prints_errors(command, "Permission denied\n");
}
}
}


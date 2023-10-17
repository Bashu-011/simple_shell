#include "shell.h"

void handles_signals(int sig);
int execution(char **args, char **front);
int main(int argc, char *argv[])

/**
* handles_signals - prints out a prompt
* @sig: the sign or signal
*/
void handles_signals(int sig)
{
char *new_prompt = "\n$ ";

(void)sig;
signal(SIGINT, handles_signals);
write(STDIN_FILENO, new_prompt, 3);
}

/**
* execution - Executes a command in the child process.
* @args: an array of arguments
* @front: pointer to the beginning of args.
*
* Return: in case of error - a matching error code.
*         else - exit value of the last executiond command.
*/
int execution(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];

if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = get_location(command);
}

if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (create_error(args, 126));
else
ret = (create_error(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
execve(command, args, environ);
if (errno == EACCES)
ret = (create_error(args, 126));
free_env();
free_args(args, front);
free_alias_list(aliases);
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}

/**
* main - executes a simple UNIX interpreter.
* @argc: number of arguments given to the program.
* @argv: array of pointers to the arguments.
*
* Return: value of the previous executiond command.
*/
int main(int argc, char *argv[])
{
int ret = 0, retn;
int *exe_ret = &retn;
char *prompt = "$ ", *new_line = "\n";

name = argv[0];
history = 1;
aliases = NULL;
signal(SIGINT, handles_signals);

*exe_ret = 0;
environ = _copyenv();
if (!environ)
exit(-100);

if (argc != 1)
{
ret = proc_file_commands(argv[1], exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handle_args(exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

while (1)
{
write(STDOUT_FILENO, prompt, 2);
ret = handle_args(exe_ret);
if (ret == END_OF_FILE || ret == EXIT)
{
if (ret == END_OF_FILE)
write(STDOUT_FILENO, new_line, 1);
free_env();
free_alias_list(aliases);
exit(*exe_ret);
}
}

free_env();
free_alias_list(aliases);
return (*exe_ret);
}

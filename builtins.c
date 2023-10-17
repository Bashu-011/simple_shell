#include "shell.h"
int (*builtin(char *command))(char **args, char **front);
int shell_exit(char **args, char **front);
int shell_cd(char **args, char __attribute__((__unused__)) **front);
int shell_help(char **args, char __attribute__((__unused__)) **front);

/**
* builtin - Matches a command with a corresponding shell inbuilt fn
* @command: The command to match to the inbuilt fn
*
* Return: A function pointer to the matching inbuilt.
*/
int (*builtin(char *command))(char **args, char **front)
{
x_builts funcs[] = {
{ "exit", shell_exit },
{ "env", shell_env },
{ "setenv", shell_setenv },
{ "unsetenv", shell_unsetenv },
{ "cd", shell_cd },
{ "alias", shell_alias },
{ "help", shell_help },
{ NULL, NULL }
};
int i;

for (i = 0; funcs[i].name; i++)
{
if (_strcmp(funcs[i].name, command) == 0)
break;
}
return (funcs[i].f);
}

/**
* shell_exit - terminates the normal process function
* @args: array of arguments containing the exit value.
* @front: pointer to the pointer of the beginning of args.
*
* Return: no arguments -3
*         If the given exit value is not valid - 2.
*         else exits with the given status value.
*
* Description: if -3 is returned, the program exits back in the main function.
*/
int shell_exit(char **args, char **front)
{
int i, len_of_int = 10;
unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

if (args[0])
{
if (args[0][0] == '+')
{
i = 1;
len_of_int++;
}
for (args[0][i]; i++)
{
if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
num = (num * 10) + (args[0][i] - '0');
else
return (create_error(--args, 2));
}
}
else
{
return (-3);
}
if (num > max - 1)
return (create_error(--args, 2));
args -= 1;
free_args(args, front);
free_env();
free_alias_list(aliases);
exit(num);
}

/**
* shell_cd - Changes the cd of the shell process.
* @args: array of arguments.
* @front: a pointer to the pointer of the beginning of args.
*
* Return: If string is not a directory - 2.
*         If an error occurs -1.
*         else - 0.
*/
int shell_cd(char **args, char __attribute__((__unused__)) **front)
{
char **directory_info, *new_line = "\n";
char *last_pwd = NULL, *pwd = NULL;
struct stat dir;

last_pwd = getcwd(last_pwd, 0);
if (!last_pwd)
return (-1);

if (args[0])
{
if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') ||
args[0][1] == '\0')
{
if (_getenv("LAST_PWD") != NULL)
(chdir(*_getenv("LAST_PWD") + 7));
}
else
{
free(last_pwd);
return (create_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
&& ((dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(last_pwd);
return (create_error(args, 2));
}
}
}
else
{
if (_getenv("HOME") != NULL)
chdir(*(_getenv("HOME")) + 5);
}

pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);

directory_info = malloc(sizeof(char *) * 2);
if (!directory_info)
return (-1);

directory_info[0] = "LAST_PWD";
directory_info[1] = last_pwd;
if (shell_setenv(directory_info, directory_info) == -1)
return (-1);

directory_info[0] = "PWD";
directory_info[1] = pwd;
if (shell_setenv(directory_info, directory_info) == -1)
return (-1);
if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}
free(last_pwd);
free(pwd);
free(directory_info);
return (0);
}

/**
* shell_help - shows info on shell builtin commands.
* @args: An array of arguments.
* @front: A pointer to the pointer of beginning of args.
*
* Return: If error occurs -1.
*         else - 0.
*/
int shell_help(char **args, char __attribute__((__unused__)) **front)
{
if (!args[0])
help_all();
else if (_strcmp(args[0], "alias") == 0)
help_alias();
else if (_strcmp(args[0], "cd") == 0)
help_cd();
else if (_strcmp(args[0], "exit") == 0)
help_exit();
else if (_strcmp(args[0], "env") == 0)
help_env();
else if (_strcmp(args[0], "setenv") == 0)
help_setenv();
else if (_strcmp(args[0], "unsetenv") == 0)
help_unsetenv();
else if (_strcmp(args[0], "help") == 0)
help_help();
else
write(STDERR_FILENO, name, _strlen(name));

return (0);
}

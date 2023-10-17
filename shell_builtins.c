#include "shell.h"

/**
* my_exit - exits the shell
* @command: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: exits with a given exit status
*         (0) if command.argv[0] != "exit"
*/
int my_exit(x_info *command)
{
int exitcheck;

if (command->argv[1])  /* an exit arguement */
{
exitcheck = _errs2int(command->argv[1]);
if (exitcheck == -1)
{
command->status = 2;
prints_errors(command, "Illegal number: ");
_eputs(command->argv[1]);
_eputchar('\n');
return (1);
}
command->err_num = _errs2int(command->argv[1]);
return (-2);
}
command->err_num = -1;
return (-2);
}

/**
* my_cdir - changes the current directory
* @command: Structure containing potential arguments. Used to maintain
*          function prototype.
*  Return: Always 0
*/
int my_cdir(x_info *command)
{
char *s, *dir, buffer[1024];
int chdir_ret;

s = getcwd(buffer, 1024);
if (!s)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!command->argv[1])
{
dir = _getenv(command, "HOME=");
if (!dir)
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(command, "PWD=")) ? dir : "/");
else
chdir_ret = chdir(dir);
}
else if (_strcmp(command->argv[1], "-") == 0)
{
if (!_getenv(command, "OLDPWD="))
{
_puts(s);
_putchar('\n');
return (1);
}
_puts(_getenv(command, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((dir = _getenv(command, "OLDPWD=")) ? dir : "/");
}
else
chdir_ret = chdir(command->argv[1]);
if (chdir_ret == -1)
{
prints_errors(command, "can't change directory to ");
_eputs(command->argv[1]), _eputchar('\n');
}
else
{
_setenv(command, "OLDPWD", _getenv(command, "PWD="));
_setenv(command, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
* my_helper - displays the current directory of the process
* @command: Structure containing potential arguments. Used to maintain
*          constant function prototype.
*  Return: Always 0
*/
int my_helper(x_info *command)
{
char **arg_array;

arg_array = command->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array); /* temp att_unused workaround */
return (0);
}

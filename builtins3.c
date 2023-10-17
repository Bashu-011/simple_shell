#include "shell.h"

int shell_env(char **args, char __attribute__((__unused__)) **front);
int shell_setenv(char **args, char __attribute__((__unused__)) **front);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
* shell_env - Prints the current environmentments.
* @args: An array of arguments passed to the shell.
* @front: A double pointer to the beginning of args.
*
* Return: If an error happens  -1.
*	   else - 0.
*
* Description: Prints one variable on each line in the
* specified format 'variable'='value'.
*/
int shell_env(char **args, char __attribute__((__unused__)) **front)
{
int x;
char new_char = '\n';

if (!environment)
return (-1);

for (x = 0; environment[x]; x++)
{
write(STDOUT_FILENO, environment[x], _strlen(environment[x]));
write(STDOUT_FILENO, &new_char, 1);
}

(void)args;
return (0);
}

/**
* shell_setenv - Changes the environmentmental variable to the PATH.
* @args: array of arguments passed to the shell.
* @front: double pointer to the beginning of args.
* Description: args[1] name of the new or existing PATH variable.
*              args[2] value to set the new or changed variable to.
*
* Return: If error occurs -1.
*         else - 0.
*/
int shell_setenv(char **args, char __attribute__((__unused__)) **front)
{
char **environment_val = NULL, **new_environment, *new_value;
x_size size;
int x;

if (!args[0] || !args[1])
return (create_error(args, -1));

new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
if (!new_value)
return (create_error(args, -1));
_strcpy(new_value, args[0]);
_strcat(new_value, "=");
_strcat(new_value, args[1]);

environment_val = _getenv(args[0]);
if (environment_val)
{
free(*environment_val);
*environment_val = new_value;
return (0);
}
for (size = 0; environment[size]; size++)
;

new_environment = malloc(sizeof(char *) * (size + 2));
if (!new_environment)
{
free(new_value);
return (create_error(args, -1));
}

for (x = 0; environment[x]; x++)
new_environment[x] = environment[x];

free(environment);
environment = new_environment;
environment[x] = new_value;
environment[x + 1] = NULL;

return (0);
}

/**
* shell_unsetenv - removes any environmentmental variable from the PATH.
* @args: An array of arguments passed to the shell.
* @front: a pointer to the pointer of the beginning of args.
* Description: args[1] is the PATH variable to be removed.
*
* Return: If an error occurs -1.
*         else - 0.
*/
int shell_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
char **environment_val, **new_environment;
x_size size;
int x, x2;

if (!args[0])
return (create_error(args, -1));
environment_val = _getenv(args[0]);
if (!environment_val)
return (0);

for (size = 0; environment[size]; size++)
;

new_environment = malloc(sizeof(char *) * size);
if (!new_environment)
return (create_error(args, -1));

for (x = 0, x2 = 0; environment[x]; x++)
{
if (*environment_val == environment[x])
{
free(*environment_val);
continue;
}
new_environment[x2] = environment[x];
x2++;
}
free(environment);
environment = new_environment;
environment[size - 1] = NULL;

return (0);
}
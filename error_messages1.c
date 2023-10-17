#include "shell.h"

char *error_environment(char **args);
char *error_alias(char **args);
char *error_cd(char **args);
char *error_exit(char **args);
char *error_syntax(char **args);
/**
* error_environment - gives an error message for shell_env errors.
* @args: An array of arguments given to the command.
*
* Return: The error message.
*/
char *error_environment(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

args--;
len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 45;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(history_str);
return (NULL);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, history_str);
_strcat(error, ": ");
_strcat(error, args[0]);
_strcat(error, ": Unable to add or remove from environment\n");

free(history_str);
return (error);
}

/**
* error_alias - gives an error message for the shell_alias errors.
* @args: An array of arguments given to the command.
*
* Return: The error message
*/
char *error_alias(char **args)
{
char *error;
int len;

len = _strlen(name) + _strlen(args[0]) + 13;
error = malloc(sizeof(char) * (len + 1));
if (!error)
return (NULL);

_strcpy(error, "alias: ");
_strcat(error, args[0]);
_strcat(error, " not found\n");

return (error);
}

/**
* error_exit - gives an error message for the shell_exit errors.
* @args: An array of arguments given to the command.
*
* Return: The error message
*/
char *error_exit(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 27;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(history_str);
return (NULL);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, history_str);
_strcat(error, ": exit: Illegal number: ");
_strcat(error, args[0]);
_strcat(error, "\n");

free(history_str);
return (error);
}

/**
* error_cd - gives an error message for shell_cd errors.
* @args: An array of arguments given to the command.
*
* Return: The error message
*/
char *error_cd(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

if (args[0][0] == '-')
args[0][2] = '\0';
len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(history_str);
return (NULL);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, history_str);
if (args[0][0] == '-')
_strcat(error, ": cd: Illegal option ");
else
_strcat(error, ": cd: can't cd to ");
_strcat(error, args[0]);
_strcat(error, "\n");

free(history_str);
return (error);
}

/**
* error_syntax - gives an error message for syntax errors.
* @args: An array of arguments parsed to the command.
*
* Return: The error message
*/
char *error_syntax(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 33;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(history_str);
return (NULL);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, history_str);
_strcat(error, ": Syntax error: \"");
_strcat(error, args[0]);
_strcat(error, "\" unexpected\n");

free(history_str);
return (error);
}
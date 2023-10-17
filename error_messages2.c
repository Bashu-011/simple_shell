#include "shell.h"

char *error1(char **args);
char *error2(char **args);

/**
* error1 - gives an error message for permission denied
* @args: An array of arguments given to the command.
*
* Return: The error message
*/
char *error1(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

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
_strcat(error, ": ");
_strcat(error, args[0]);
_strcat(error, ": Permission denied!\n");

free(history_str);
return (error);
}

/**
* error2 - gives an error message for commands not found
* @args: An array of arguments given to the command.
*
* Return: The error message
*/
char *error2(char **args)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (NULL);

len = _strlen(name) + _strlen(history_str) + _strlen(args[0]) + 16;
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
_strcat(error, ": command not found\n");

free(history_str);
return (error);
}

#include "shell.h"

char *input_args(char *line, int *exe_ret);
int calls_args(char **args, char **front, int *exe_ret);
int executes_commands(char **args, char **front, int *exe_ret);
int execution_of_args(int *exe_ret);
int inspects_args(char **args);

/**
* input_args - recieves commands from the standard input.
* @line: A buffer for storing the command.
* @exe_ret: return value of the last executed command.
*
* Return: If an error occurs - NULL.
*         else - pointer to the stored command.
*/
char *input_args(char *line, int *exe_ret)
{
x_size n = 0;
xsize read;
char *prompt = "$ ";

if (line)
free(line);

read = _getline(&line, &n, STDIN_FILENO);
if (read == -1)
return (NULL);
if (read == 1)
{
hist++;
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, prompt, 2);
return (input_args(line, exe_ret));
}

line[read - 1] = '\0';
variable_replacement(&line, exe_ret);
handle_line(&line, read);

return (line);
}

/**
* calls_args - divides operators from commands and calls them.
* @args: array of arguments.
* @front: pointer to the beginning of args.
* @exe_ret: return value of the previous executed command.
*
* Return: value of the previous executed command.
*/
int calls_args(char **args, char **front, int *exe_ret)
{
int ret, index;

if (!args[0])
return (*exe_ret);
for (index = 0; args[index]; index++)
{
if (_strncmp(args[index], "||", 2) == 0)
{
free(args[index]);
args[index] = NULL;
args = replace_aliases(args);
ret = executes_commands(args, front, exe_ret);
if (*exe_ret != 0)
{
args = &args[++index];
index = 0;
}
else
{
for (index++; args[index]; index++)
free(args[index]);
return (ret);
}
}
else if (_strncmp(args[index], "&&", 2) == 0)
{
free(args[index]);
args[index] = NULL;
args = replace_aliases(args);
ret = executes_commands(args, front, exe_ret);
if (*exe_ret == 0)
{
args = &args[++index];
index = 0;
}
else
{
for (index++; args[index]; index++)
free(args[index]);
return (ret);
}
}
}
args = replace_aliases(args);
ret = executes_commands(args, front, exe_ret);
return (ret);
}

/**
* executes_commands - initiates the execution of the command.
* @args: array of arguments.
* @front: pointer to the beginning of args.
* @exe_ret: value of the previous executed command.
*
* Return: value of the last executed command.
*/
int executes_commands(char **args, char **front, int *exe_ret)
{
int ret, i;
int (*builtin)(char **args, char **front);

builtin = get_builtin(args[0]);

if (builtin)
{
ret = builtin(args + 1, front);
if (ret != EXIT)
*exe_ret = ret;
}
else
{
*exe_ret = execute(args, front);
ret = *exe_ret;
}

hist++;

for (i = 0; args[i]; i++)
free(args[i]);

return (ret);
}

/**
* execution_of_args - runs the execution of a command.
* @exe_ret: returns the last executed comman
*
* Return: If END_OF_FILE (-2).
*         If the input isn't recognised -1
*         else - exit value of the last executed command.
*/
int execution_of_args(int *exe_ret)
{
int ret = 0, index;
char **args, *line = NULL, **front;

line = input_args(line, exe_ret);
if (!line)
return (END_OF_FILE);

args = _strtok(line, " ");
free(line);
if (!args)
return (ret);
if (inspects_args(args) != 0)
{
*exe_ret = 2;
free_args(args, args);
return (*exe_ret);
}
front = args;

for (index = 0; args[index]; index++)
{
if (_strncmp(args[index], ";", 1) == 0)
{
free(args[index]);
args[index] = NULL;
ret = calls_args(args, front, exe_ret);
args = &args[++index];
index = 0;
}
}
if (args)
ret = calls_args(args, front, exe_ret);

free(front);
return (ret);
}

/**
* inspects_args - Checks if there are any leading symbols
* @args: pointer to commands and arguments
* Return: If ';', '&&', or '||' is placed at an invalid position - 2.
*	   else - 0.
*/
int inspects_args(char **args)
{
x_size i;
char *cur, *nex;

for (i = 0; args[i]; i++)
{
cur = args[i];
if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
{
if (i == 0 || cur[1] == ';')
return (create_error(&args[i], 2));
nex = args[i + 1];
if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
return (create_error(&args[i + 1], 2));
}
}
return (0);
}

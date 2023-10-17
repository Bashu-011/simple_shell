#include "shell.h"

void frees_args(char **args, char **front);
char *current_pid(void);
char *currentenv_val(char *beginning, int len);
void replace_var(char **args, int *exe_ret);

/**
* frees_args - sets free memory taken by args.
* @args: null-terminated double pointer containing arguments.
* @front: double pointer to the start of args.
*/
void frees_args(char **args, char **front)
{
x_size i;

for (i = 0; args[i] || args[i + 1]; i++)
free(args[i]);

free(front);
}

/**
* current_pid - obtains the current process ID.
* Description: Opens the stat file, a space-delimited file containing
*              information about the current.
*               The function reads the PID into
*              a buffer and replace the space at the end with a \0 byte.
*
* Return: current process ID or NULL incase of failure.
*/
char *current_pid(void)
{
x_size i = 0;
char *buffer;
xsize file;

file = open("/proc/self/stat", O_RDONLY);
if (file == -1)
{
perror("Cant read the file");
return (NULL);
}
buffer = malloc(120);
if (!buffer)
{
close(file);
return (NULL);
}
read(file, buffer, 120);
while (buffer[i] != ' ')
i++;
buffer[i] = '\0';

close(file);
return (buffer);
}

/**
* currentenv_val - get the value similar to an environmental variable.
* @beginning: environmental variable to be searched for.
* @len: length of the environmental variable to search for.
*
* Return: If the variable is not found - an empty string.
*         else - the value of the environmental variable.
*
* Description: Variables stored in the format VARIABLE=VALUE.
*/
char *currentenv_val(char *beginning, int len)
{
char **var_address;
char *replacement = NULL, *temp, *var;

var = malloc(len + 1);
if (!var)
return (NULL);
var[0] = '\0';
_strncat(var, beginning, len);

var_address = _getenv(var);
free(var);
if (var_address)
{
temp = *var_address;
while (*temp != '=')
temp++;
temp++;
replacement = malloc(_strlen(temp) + 1);
if (replacement)
_strcpy(replacement, temp);
}

return (replacement);
}

/**
* replace_var - manages variable replacement.
* @line: double pointer holding the commands and arguments.
* @exe_ret: pointer to the return value of the last command.
*
* Description: Replaces with the current PID, with the return value
*              of the last executed program,
*              and all the envrionmental variables
*              starting with $ with their corresponding value.
*/
void replace_var(char **line, int *exe_ret)
{
int j, k = 0, len;
char *replacement = NULL, *last_line = NULL, *new_line;

last_line = *line;
for (j = 0; last_line[j]; j++)
{
if (last_line[j] == '$' && last_line[j + 1] &&
last_line[j + 1] != ' ')
{
if (last_line[j + 1] == '$')
{
replacement = current_pid();
k = j + 2;
}
else if (last_line[j + 1] == '?')
{
replacement = _itoa(*exe_ret);
k = j + 2;
}
else if (last_line[j + 1])
{
for (k = j + 1; last_line[k] &&
last_line[k] != '$' &&
last_line[k] != ' '; k++)
;
len = k - (j + 1);
replacement = currentenv_val(&last_line[j + 1], len);
}
new_line = malloc(j + _strlen(replacement)
+ _strlen(&last_line[k]) + 1);
if (!line)
return;
new_line[0] = '\0';
_strncat(new_line, last_line, j);
if (replacement)
{
_strcat(new_line, replacement);
free(replacement);
replacement = NULL;
}
_strcat(new_line, &last_line[k]);
free(last_line);
*line = new_line;
last_line = new_line;
j = -1;
}
}
}
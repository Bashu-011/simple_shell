#include "shell.h"

int null_files(char *file_path);
int run_files_commands(char *file_path, int *exe_ret);

/**
* null_files - handles files that dont exist/lack proper permission
* @file_path: Path to the file.
*
* Return: 127.
*/

int null_files(char *file_path)
{
char *error, *history_str;
int len;

history_str = _itoa(history);
if (!history_str)
return (127);

len = _strlen(name) + _strlen(history_str) + _strlen(file_path) + 16;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(history_str);
return (127);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, history_str);
_strcat(error, ": Can't open ");
_strcat(error, file_path);
_strcat(error, "\n");

free(history_str);
write(STDERR_FILENO, error, len);
free(error);
return (127);
}

/**
* run_files_commands - tries to run commands within a file
* @file_path: Path to file.
* @exe_ret: Return value of previous executed command.
*
* Return: file can't open - 127.
*	   malloc fails - -1.
*	   else return value of previous command ran.
*/
int run_files_commands(char *file_path, int *exe_ret)
{
xsize file, f_reads, i;
unsigned int line_size = 0;
unsigned int last_size = 120;
char *line, **args, **front;
char buffer[120];
int ret;

history = 0;
file = open(file_path, O_RDONLY);
if (file == -1)
{
*exe_ret = null_files(file_path);
return (*exe_ret);
}
line = malloc(sizeof(char) * last_size);
if (!line)
return (-1);
do {
f_reads = read(file, buffer, 119);
if (f_reads == 0 && line_size == 0)
return (*exe_ret);
buffer[f_reads] = '\0';
line_size += f_reads;
line = _realloc(line, last_size, line_size);
_strcat(line, buffer);
last_size = line_size;
} while (f_reads);
for (i = 0; line[i] == '\n'; i++)
line[i] = ' ';
for (; i < line_size; i++)
{
if (line[i] == '\n')
{
line[i] = ';';
for (i += 1; i < line_size && line[i] == '\n'; i++)
line[i] = ' ';
}
}
variable_replacement(&line, exe_ret);
handle_line(&line, line_size);
args = _strtok(line, " ");
free(line);
if (!args)
return (0);
if (check_args(args) != 0)
{
*exe_ret = 2;
free_args(args, args);
return (*exe_ret);
}
front = args;

for (i = 0; args[i]; i++)
{
if (_strncmp(args[i], ";", 1) == 0)
{
free(args[i]);
args[i] = NULL;
ret = call_args(args, front, exe_ret);
args = &args[++i];
i = 0;
}
}

ret = call_args(args, front, exe_ret);

free(front);
return (ret);
}

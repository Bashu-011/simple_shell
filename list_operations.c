#include "shell.h"

/**
* is_cmd - determines if a file is an executable command
* @command: the command struct
* @path: path to the file
*
* Return: 1 if true, 0 otherwise
*/
int is_cmd(x_info *command, char *path)
{
struct stat st;

(void)command;
if (!path || stat(path, &st))
return (0);

if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* dup_chars - doubles the characters
* @pathstr: the PATH string
* @start: start key
* @stop: end key
*
* Return: pointer to new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
static char buf[1024];
int i = 0, k = 0;

for (k = 0, i = start; i < stop; i++)
if (pathstr[i] != ':')
buf[k++] = pathstr[i];
buf[k] = 0;
return (buf);
}

/**
* find_path - finds this cmd in the PATH string
* @command: the command struct
* @pathstr: the PATH string
* @cmd: the cmd to find
*
* Return: full path of cmd if found or NULL
*/
char *find_path(x_info *command, char *pathstr, char *cmd)
{
int i = 0, curr_pos = 0;
char *path;

if (!pathstr)
return (NULL);
if ((_my_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(command, cmd))
return (cmd);
}
while (1)
{
if (!pathstr[i] || pathstr[i] == ':')
{
path = dup_chars(pathstr, curr_pos, i);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(command, path))
return (path);
if (!pathstr[i])
break;
curr_pos = i;
}
i++;
}
return (NULL);
}

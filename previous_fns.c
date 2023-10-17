#include "shell.h"

/**
* get_history_file - gets the history file
* @command: parameter struct
*
* Return: allocated string containg history file
*/

char *get_history_file(x_info *command)
{
char *buf, *dir;

dir = _getenv(command, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_my_strlen(dir) + _my_strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_my_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
* write_history - creates a file, or appends to an existing file
* @command: the parameter struct
*
* Return: 1 on success else -1
*/
int write_history(x_info *command)
{
xx_size fil_desc;
char *filename = get_history_file(command);
x_list *node = NULL;

if (!filename)
return (-1);

fil_desc = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fil_desc == -1)
return (-1);
for (node = command->history; node; node = node->next)
{
_putsfil_desc(node->str, fil_desc);
_putfil_desc('\n', fil_desc);
}
_putfil_desc(BUF_FLUSH, fil_desc);
close(fil_desc);
return (1);
}

/**
* read_history - reads from previous version of file
* @command: the parameter struct
*
* Return: hist count on success, 0 otherwise
*/
int read_history(x_info *command)
{
int i, last = 0, linecounter = 0;
xx_size fil_desc, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(command);

if (!filename)
return (0);

fil_desc = open(filename, O_RDONLY);
free(filename);
if (fil_desc == -1)
return (0);
if (!fstat(fil_desc, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fil_desc, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fil_desc);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(command, buf + last, linecounter++);
last = i + 1;
}
if (last != i)
build_history_list(command, buf + last, linecounter++);
free(buf);
command->histcount = linecounter;
while (command->histcount-- >= HIST_MAX)
delete_node_key(&(command->history), 0);
renum_hist(command);
return (command->histcount);
}

/**
* build_history_list - adds entry to a history linked list
* @command: Structure containing potential arguments. Used to maintain
* @buf: buffer
* @linecounter: the history linecount, histcount
*
* Return: Always 0
*/
int build_history_list(x_info *command, char *buf, int linecounter)
{
x_list *node = NULL;

if (command->history)
node = command->history;
add_node_end(&node, buf, linecounter);

if (!command->history)
command->history = node;
return (0);
}

/**
* renum_hist - renumbers the history linked list after changes
* @command: Structure containing potential arguments. Used to maintain
*
* Return: the new histcount
*/
int renum_hist(x_info *command)
{
x_list *node = command->history;
int i = 0;

while (node)
{
node->num = i++;
node = node->next;
}
return (command->histcount = i);
}

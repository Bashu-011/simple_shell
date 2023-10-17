#include "shell.h"

/**
* clear_info - initializes x_info struct
* @command: struct address
*/
void clear_info(x_info *command)
{
command->arg = NULL;
command->argv = NULL;
command->path = NULL;
command->argc = 0;
}

/**
* set_info - initializes x_info struct
* @command: struct address
* @av: argument vector
*/
void set_info(x_info *command, char **av)
{
int i = 0;

command->fname = av[0];
if (command->arg)
{
command->argv = strtow(command->arg, " \t");
if (!command->argv)
{

command->argv = malloc(sizeof(char *) * 2);
if (command->argv)
{
command->argv[0] = _strdup(command->arg);
command->argv[1] = NULL;
}
}
for (i = 0; command->argv && command->argv[i]; i++)
;
command->argc = i;

replace_alias(command);
replaces_vals(command);
}
}

/**
* free_info - frees x_info struct fields
* @command: struct address
* @all: true if freeing all fields
*/
void free_info(x_info *command, int all)
{
ffree(command->argv);
command->argv = NULL;
command->path = NULL;
if (all)
{
if (!command->cmd_buf)
free(command->arg);
if (command->env)
free_list(&(command->env));
if (command->history)
free_list(&(command->history));
if (command->alias)
free_list(&(command->alias));
ffree(command->environ);
command->environ = NULL;
bfree((void **)command->cmd_buf);
if (command->readfil_desc > 2)
close(command->readfil_desc);
_putchar(BUF_FLUSH);
}
}

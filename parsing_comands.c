#include "shell.h"

/**
* ch_delim - tests if current char is a chain delimeter
* @command: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
*
* Return: 1 if chain delimeter, 0 otherwise
*/
int ch_delim(x_info *command, char *buf, size_t *p)
{
size_t j = *p;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
command->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
command->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';')
{
buf[j] = 0;
command->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*p = j;
return (1);
}

/**
* check_chain - checks we should continue chaining based on last status
* @command: the parameter struct
* @buf: the char buffer
* @p: address of current position in buf
* @i: starting position in buf
* @len: length of buf
*
* Return: Void
*/
void check_chain(x_info *command, char *buf, size_t *p, size_t i, size_t len)
{
size_t j = *p;

if (command->cmd_buf_type == CMD_AND)
{
if (command->status)
{
buf[i] = 0;
j = len;
}
}
if (command->cmd_buf_type == CMD_OR)
{
if (!command->status)
{
buf[i] = 0;
j = len;
}
}

*p = j;
}

/**
* replace_alias - replaces an aliases in the tokenized string
* @command: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_alias(x_info *command)
{
int i;
x_list *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_prefix(command->alias, command->argv[0], '=');
if (!node)
return (0);
free(command->argv[0]);
p = my_stringchar(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
command->argv[0] = p;
}
return (1);
}

/**
* replaces_vals - replaces values in the tokenized string
* @command: the parameter struct
*
* Return: 1 if replaced, 0 otherwise
*/
int replaces_vals(x_info *command)
{
int i = 0;
x_list *node;

for (i = 0; command->argv[i]; i++)
{
if (command->argv[i][0] != '$' || !command->argv[i][1])
continue;

if (!_strcmp(command->argv[i], "$?"))
{
replace_string(&(command->argv[i]),
_strdup(convert_number(command->status, 10, 0)));
continue;
}
if (!_strcmp(command->argv[i], "$$"))
{
replace_string(&(command->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_prefix(command->env, &command->argv[i][1], '=');
if (node)
{
replace_string(&(command->argv[i]),
_strdup(my_stringchar(node->str, '=') + 1));
continue;
}
replace_string(&command->argv[i], _strdup(""));

}
return (0);
}

/**
* replace_string - replaces string
* @old: address of old string
* @new: new string
*
* Return: 1 if replaced, 0 otherwise
*/
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}

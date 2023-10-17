#include "shell.h"

/**
* get_environ - returns the string array copy of our environ
* @command: a structure containing potential arguments. Used to maintain
*           function prototype.
* Return: Always 0
*/
char **get_environ(x_info *command)
{
if (!command->environ || command->env_changed)
{
command->environ = list_to_strings(command->env);
command->env_changed = 0;
}

return (command->environ);
}

/**
* _unsetenv - Remove an environment variable
* @command: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: 1 on delete, else 0
* @var: the string env var property
*/
int _unsetenv(x_info *command, char *var)
{
x_list *node = command->env;
x_size i = 0;
char *p;

if (!node || !var)
return (0);

while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
command->env_changed = delete_node_key(&(command->env), i);
i = 0;
node = command->env;
continue;
}
node = node->next;
i++;
}
return (command->env_changed);
}

/**
* _setenv - Initialize a new environment variable,
*             or modify an existing one
* @command: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
*  Return: Always 0
*/
int _setenv(x_info *command, char *var, char *value)
{
char *buf = NULL;
x_list *node;
char *p;

if (!var || !value)
return (0);

buf = malloc(_my_strlen(var) + _my_strlen(value) + 2);
if (!buf)
return (1);
_my_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = command->env;
while (node)
{
p = starts_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
command->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(command->env), buf, 0);
free(buf);
command->env_changed = 1;
return (0);
}

#include "shell.h"

/**
* _my_sh_env - prints the current working environment
* @command: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int _my_sh_env(x_info *command)
{
print_list_str(command->env);
return (0);
}

/**
* _getenv - gets the value of the environment variable
* @command: Structure containing potential arguments. Used to maintain
* @name: environment variable name
*
* Return: the value
*/
char *_getenv(x_info *command, const char *name)
{
x_list *node = command->env;
char *p;

while (node)
{
p = starts_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
}
return (NULL);
}

/**
* _mysetenv - Initialize a new environment variable,
*             or modify an existing one
* @command: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _mysetenv(x_info *command)
{
if (command->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(command, command->argv[1], command->argv[2]))
return (0);
return (1);
}

/**
* _myunsetenv - Remove an environment variable
* @command: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int _myunsetenv(x_info *command)
{
int i;

if (command->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (i = 1; i <= command->argc; i++)
_unsetenv(command, command->argv[i]);

return (0);
}

/**
* populate_env_list - populates env linked list
* @command: Structure containing potential arguments. Used to maintain
*          constant function prototype.
* Return: Always 0
*/
int populate_env_list(x_info *command)
{
x_list *node = NULL;
size_t i;

for (i = 0; environ[i]; i++)
add_node_end(&node, environ[i], 0);
command->env = node;
return (0);
}

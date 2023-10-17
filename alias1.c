#include "shell.h"

/**
* my_previous - displays the previous list, command by line, preceded
*              with line numbers, starting at 0.
* @command: Structure containing potential arguments. Used to maintain
*        constant function prototype.
*  Return: Always 0
*/
int my_previous(x_info *command)
{
print_list(command->history);
return (0);
}

/**
* unsets_aliases - unsets alias from a string
* @command: the parameter struct
* @str: string alias
*
* Return: Always 0 on success, 1 on error
*/
int unsets_aliases(x_info *command, char *str)
{
char *p, c;
int ret;

p = my_stringchar(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_key(&(command->alias),
get_node_key(command->alias, node_prefix(command->alias, str, -1)));
*p = c;
return (ret);
}

/**
* sets_alias - sets alias to a string
* @command: parameter struct
* @str: string alias
*
* Return: Always 0 on success, else 1
*/
int sets_alias(x_info *command, char *str)
{
char *p;

p = my_stringchar(str, '=');
if (!p)
return (1);
if (!*++p)
return (unsets_aliases(command, str));

unsets_aliases(command, str);
return (add_node_end(&(command->alias), str, 0) == NULL);
}

/**
* prints_alias - prints an alias as string
* @node: the alias node
*
* Return: Always 0 on success
* else 1 on error
*/
int prints_alias(x_list *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = my_stringchar(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
* _my_sh_alias - copies the alias builtin (man alias)
* @command: Structure containing potential arguments
*  Used to maintain constant function prototype.
*  Return: Always 0
*/
int _my_sh_alias(x_info *command)
{
int i = 0;
char *p = NULL;
x_list *node = NULL;

if (command->argc == 1)
{
node = command->alias;
while (node)
{
prints_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; command->argv[i]; i++)
{
p = my_stringchar(command->argv[i], '=');
if (p)
sets_alias(command, command->argv[i]);
else
prints_alias(node_prefix(command->alias, command->argv[i], '='));
}

return (0);
}

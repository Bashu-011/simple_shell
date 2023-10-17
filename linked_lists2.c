#include "shell.h"

/**
* list_len - determines length of linked list
* @h: pointer to first node
*
* Return: size of list
*/
x_size list_len(const x_list *h)
{
x_size i = 0;

while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
* list_to_strings - returns an array of strings of the list->str
* @head: pointer to first node
*
* Return: array of strings
*/
char **list_to_strings(x_list *head)
{
x_list *node = head;
x_size i = list_len(head), j;
char **strs;
char *str;

if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));
if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(_my_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}

str = _my_strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}


/**
* print_list - prints all elements of a x_list linked list
* @h: pointer to first node
*
* Return: size of list
*/
x_size print_list(const x_list *h)
{
x_size i = 0;

while (h)
{
_puts(convert_number(h->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* node_prefix - returns node whose string starts with prefix
* @node: pointer to list head
* @prefix: string to match
* @c: the next character after prefix to match
*
* Return: match node or null
*/
x_list *node_prefix(x_list *node, char *prefix, char c)
{
char *p = NULL;

while (node)
{
p = starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}

/**
* get_node_key - gets the key of a node
* @head: pointer to list head
* @node: pointer to the node
*
* Return: key of node or -1
*/
xx_size get_node_key(x_list *head, x_list *node)
{
x_size i = 0;

while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
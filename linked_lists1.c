#include "shell.h"

/**
* add_node - add node to the start of the list
* @head: address of pointer to the head node
* @str: str field of node
* @num: key used by history
*
* Return: size of list
*/
x_list *add_node(x_list **head, const char *str, int num)
{
x_list *new_head;

if (!head)
return (NULL);
new_head = malloc(sizeof(x_list));
if (!new_head)
return (NULL);
_my_memset((void *)new_head, 0, sizeof(x_list));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node key used by history
*
* Return: size of list
*/
x_list *add_node_end(x_list **head, const char *str, int num)
{
x_list *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(x_list));
if (!new_node)
return (NULL);
_my_memset((void *)new_node, 0, sizeof(x_list));
new_node->num = num;
if (str)
{
new_node->str = _strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
* print_list_str - prints only the str element of a x_list linked list
* @h: pointer to first node
*
* Return: size of list
*/
x_size print_list_str(const x_list *h)
{
x_size i = 0;

while (h)
{
_puts(h->str ? h->str : "(nil)");
_puts("\n");
h = h->next;
i++;
}
return (i);
}

/**
* delete_node_key - deletes node at an key
* @head: address of pointer to first node
* @key: key of node to delete
*
* Return: 1 on success, 0 on failure
*/
int delete_node_key(x_list **head, unsigned int key)
{
x_list *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);

if (!key)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
{
if (i == key)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}

/**
* free_list - frees all nodes of a list
* @head_ptr: address of pointer to head node
*
* Return: void
*/
void free_list(x_list **head_ptr)
{
x_list *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}

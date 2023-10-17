#include "shell.h"

x_alias *adds_alias(x_alias **head, char *name, char *value);
void linkedlists_free(x_alias *head);
x_list *node_end(x_list **head, char *dir);
void frees_list(x_list *head);

/**
* adds_alias - Adds to the end of a x_alias linked list
* @head: pointer to the head of the x_list
* @name: name of the new alias to be added
* @value: value of the new alias to be added
* Return: for an error - NULL
*         else - pointer to the new node
*/
x_alias *adds_alias(x_alias **head, char *name, char *value)
{
x_alias *new_node = malloc(sizeof(x_alias));
x_alias *last;

if (!new_node)
return (NULL);

new_node->next = NULL;
new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
if (!new_node->name)
{
free(new_node);
return (NULL);
}
new_node->value = value;
_strcpy(new_node->name, name);

if (*head)
{
last = *head;
while (last->next != NULL)
last = last->next;
last->next = new_node;
}
else
*head = new_node;

return (new_node);
}
/**
* linkedlists_free - Frees  x_alias linked list
* @head: head of the x_alias list
*/
void linkedlists_free(x_alias *head)
{
x_alias *next;

while (head)
{
next = head->next;
free(head->name);
free(head->value);
free(head);
head = next;
}
}
/**
* node_end - adds node to the end of the x_list linked list
* @head: pointer to the head of the x_list
* @dir: directory path for the new node to contain
* Return: for an error - NULL
* else - a pointer to the new node
*/
x_list *node_end(x_list **head, char *dir)
{
x_list *new_node = malloc(sizeof(x_list));
x_list *last;

if (!new_node)
return (NULL);

new_node->dir = dir;
new_node->next = NULL;

if (*head)
{
last = *head;
while (last->next != NULL)
last = last->next;
last->next = new_node;
}
else
*head = new_node;

return (new_node);
}
/**
* frees_list - frees x_list linked list
* @head: top of the x_list
*/
void frees_list(x_list *head)
{
x_list *next;

while (head)
{
next = head->next;
free(head->dir);
free(head);
head = next;
}
}
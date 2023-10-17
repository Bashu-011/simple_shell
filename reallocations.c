#include "shell.h"

/**
**_my_memset - fills memory with a constant byte
*@s: the pointer to the memory area
*@b: the byte to fill *s with
*@n: the amount of bytes to be filled
*Return: (s) a pointer to the memory area s
*/
char *_my_memset(char *s, char b, unsigned int n)
{
unsigned int i;

for (i = 0; i < n; i++)
s[i] = b;
return (s);
}

/**
* ffree - frees a string of strings
* @pp: string of strings
*/
void ffree(char **pp)
{
char **a = pp;

if (!pp)
return;
while (*pp)
free(*pp++);
free(a);
}

/**
* _realloc - reallocates a block of memory
* @ptr: pointer to previous allocated block
* @last_size: byte size of previous block
* @new_size: byte size of new block
*
* Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int last_size, unsigned int new_size)
{
char *p;

if (!ptr)
return (malloc(new_size));
if (!new_size)
return (free(ptr), NULL);
if (new_size == last_size)
return (ptr);

p = malloc(new_size);
if (!p)
return (NULL);

last_size = last_size < new_size ? last_size : new_size;
while (last_size--)
p[last_size] = ((char *)ptr)[last_size];
free(ptr);
return (p);
}

#include "shell.h"

/**
**_strncpy - copies a string
*@dest: the destination string to be copied to
*@src: the source string
*@n: the amount of characters to be copied
*Return: the concatenated string
*/
char *_strncpy(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
while (src[i] != '\0' && i < n - 1)
{
dest[i] = src[i];
i++;
}
if (i < n)
{
j = i;
while (j < n)
{
dest[j] = '\0';
j++;
}
}
return (s);
}

/**
**_my_strncat - concatenates two strings
*@dest: first string
*@src: second string
*@n: amount of bytes to be maximally used
*Return: concatenated string
*/
char *_my_strncat(char *dest, char *src, int n)
{
int i, j;
char *s = dest;

i = 0;
j = 0;
while (dest[i] != '\0')
i++;
while (src[j] != '\0' && j < n)
{
dest[i] = src[j];
i++;
j++;
}
if (j < n)
dest[i] = '\0';
return (s);
}

/**
**my_stringchar - locates a character in a string
*@s: the string to parse
*@c: the character to look for
*Return: (s) a pointer to the memory area s
*/
char *my_stringchar(char *s, char c)
{
do {
if (*s == c)
return (s);
} while (*s++ != '\0');

return (NULL);
}
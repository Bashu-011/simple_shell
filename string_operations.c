#include "shell.h"

/**
* _my_strlen - returns the length of a string
* @s: the string whose length to check
*
* Return: integer length of string
*/
int _my_strlen(char *s)
{
int i = 0;

if (!s)
return (0);

while (*s++)
i++;
return (i);
}

/**
* _strcmp - performs lexicogarphic comparison of two strangs.
* @x1: the first strang
* @x2: the second strang
*
* Return: negative if x1 < x2, positive if x1 > x2, zero if x1 == x2
*/
int _strcmp(char *x1, char *x2)
{
while (*x1 && *x2)
{
if (*x1 != *x2)
return (*x1 - *x2);
x1++;
x2++;
}
if (*x1 == *x2)
return (0);
else
return (*x1 < *x2 ? -1 : 1);
}

/**
* starts_with - checks if needle starts with haystack
* @haystack: string to search
* @needle: the substring to find
*
* Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
while (*needle)
if (*needle++ != *haystack++)
return (NULL);
return ((char *)haystack);
}

/**
* _strcat - concatenates two strings
* @dest: the destination
* @src: the source
*
* Return: pointer to destination buffer
*/
char *_strcat(char *dest, char *src)
{
char *ret = dest;

while (*dest)
dest++;
while (*src)
*dest++ = *src++;
*dest = *src;
return (ret);
}

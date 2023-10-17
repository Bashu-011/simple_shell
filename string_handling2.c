#include "shell.h"

char *my_strchr(char *x, char y);
int my_strspn(char *x, char *allow);
int my_strcmp(char *x1, char *x2);
int my_strncmp(const char *x1, const char *x2, x_size n);

/**
* my_strchr - finds an xter in string input
* @x: string to search
* @y: character to finf
*
* Return: if xter(y) found - a pointer to the first instance
*        else - NULL.
*/
char *my_strchr(char *x, char y)
{
int index;

for (index = 0; x[index]; index++)
{
if (x[index] == y)
return (x + index);
}

return (NULL);
}

/**
* my_strspn - gets length of previous substring
* @x: string input to search
* @allow: prefix to measure
*
* Return: number of bits in x which
*         include only of bits from allowed.
*/
int my_strspn(char *x, char *allow)
{
int bits = 0;
int index;

while (*x)
{
for (index = 0; allow[index]; index++)
{
if (*x == allow[index])
{
bits++;
break;
}
}
x++;
}
return (bits);
}

/**
* my_strcmp - checks two strings.
* @x1: first string to be checked
* @x2: second string to be checked
*
* Return: +ve byte difference if x1 > x2
*         0 if x1 = x2
*         -ve byte difference if x1 < x2
*/
int my_strcmp(char *x1, char *x2)
{
while (*x1 && *x2 && *x1 == *x2)
{
x1++;
x2++;
}

if (*x1 != *x2)
return (*x1 - *x2);

return (0);
}

/**
* my_strncmp - still checks 2 strings
* @x1: Pointer to the 1st string.
* @x2: Pointer to the 2nd string
* @n: first n bytes of the strings to check
*
* Return: <0 if x1 is shorter than x2.
*         0 if x1 and x2 match.
*         >0 if x1 is longer than x2.
*/
int my_strncmp(const char *x1, const char *x2, x_size n)
{
x_size a;

for (a = 0; x1[a] && x2[a] && a < n; a++)
{
if (x1[a] > x2[a])
return (x1[a] - x2[a]);
else if (x1[a] < x2[a])
return (x1[a] - x2[a]);
}
if (a == n)
return (0);
else
return (-15);
}

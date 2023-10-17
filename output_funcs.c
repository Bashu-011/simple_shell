#include "shell.h"

/**
*_eputs - prints the input string
* @str: string to be printed
*
* Return: None
*/
void _eputs(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
* _eputchar - writes the character to std error
* @c: The character to be written
*
* Return: 1 for success.
* For error, -1 is returned, and set appropriately.
*/
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
* _putfil_desc - writes the character to the given fil_desc
* @c: character to print
* @fil_desc: file descriptor to be written to
*
* Return: On success 1.
* For error, -1 is returned
*/
int _putfil_desc(char c, int fil_desc)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fil_desc, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
*_putsfil_desc - print an input string
* @str: the string to be printed
* @fil_desc: the file descriptor to write to
*
* Return: the number of chars put
*/
int _putsfil_desc(char *str, int fil_desc)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _putfil_desc(*str++, fil_desc);
}
return (i);
}

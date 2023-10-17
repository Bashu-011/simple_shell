#include "shell.h"

/**
* open_session - returns true if shell is open
* @command: struct address
*
* Return: 1 if the session is interactive, else 0
*/
int open_session(x_info *command)
{
return (isatty(STDIN_FILENO) && command->readfil_desc <= 2);
}

/**
* delim_check - checks if a character is a delimeter
* @c: the charachter to check
* @delim: delimeter string
* Return: 1 if true, else 0
*/
int delim_check(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}

/**
*my_isalpha - checks for the letter a-z
*@c: The character to input
*Return: 1 if c is alphabetic, else 0
*/

int my_isalpha(int c)
{
if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
return (1);
else
return (0);
}

/**
*str_2_int - changes a string to an integer
*@s: string to be converted
*Return: 0 if there are no numbers
*else converted string
*/

int str_2_int(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;

for (i = 0;  s[i] != '\0' && flag != 2; i++)
{
if (s[i] == '-')
sign *= -1;

if (s[i] >= '0' && s[i] <= '9')
{
flag = 1;
result *= 10;
result += (s[i] - '0');
}
else if (flag == 1)
flag = 2;
}

if (sign == -1)
output = -result;
else
output = result;

return (output);
}

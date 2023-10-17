#include "shell.h"

int len_of_nums(int num);
char *_itoa(int num);
int give_error(char **args, int err);

/**
* len_of_nums - counts the length of a number.
* @num: The number to be counted
*
* Return: The number length.
*/
int len_of_nums(int num)
{
unsigned int numx;
int len = 1;

if (num < 0)
{
len++;
numx = num * -1;
}
else
{
numx = num;
}
while (numx > 9)
{
len++;
numx /= 10;
}

return (len);
}

/**
* _itoa - changes the integer to a string.
* @num: The integer to be changed
*
* Return: The converted string
*/
char *_itoa(int num)
{
char *buffer;
int len = len_of_nums(num);
unsigned int numx;

buffer = malloc(sizeof(char) * (len + 1));
if (!buffer)
return (NULL);

buffer[len] = '\0';

if (num < 0)
{
numx = num * -1;
buffer[0] = '-';
}
else
{
numx = num;
}

len--;
do {
buffer[len] = (numx % 10) + '0';
numx /= 10;
len--;
} while (numx > 0);

return (buffer);
}


/**
* give_error - prints out a custom error message
* @args: An array of arguments given
* @err: The error
*
* Return: The error
*/
int give_error(char **args, int err)
{
char *error;

switch (err)
{
case -1:
error = error_env(args);
break;
case 1:
error = error_1(args);
break;
case 2:
if (*(args[0]) == 'e')
error = error_2_exit(++args);
else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
error = error_2_syntax(args);
else
error = error_2_cd(args);
break;
case 126:
error = error_126(args);
break;
case 127:
error = error_127(args);
break;
}
write(STDERR_FILENO, error, _strlen(error));

if (error)
free(error);
return (err);

}

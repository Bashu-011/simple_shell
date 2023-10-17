#include "shell.h"

int len_of_token(char *str, char *dlimiter);
int token_counter(char *str, char *dlimiter);
char **_strtok(char *line, char *dlimiter);

/**
* len_of_token - identifies dlimiter and marks the end
* @str: the string in question
* @dlimiter: delimiteriter character.
*
* Return: delimiteriter marking length of stringg
*/
int len_of_token(char *str, char *dlimiter)
{
int index = 0, len = 0;

while (*(str + index) && *(str + index) != *dlimiter)
{
len++;
index++;
}

return (len);
}

/**
* token_counter - Counts the number of delimitered
* contained in a string
* @str: The string to be counted
* @dlimiter: The dlimiteriter character.
*
* Return: The number of words contained within the
* string
*/
int token_counter(char *str, char *dlimiter)
{
int index, tokens = 0, len = 0;

for (index = 0; *(str + index); index++)
len++;

for (index = 0; index < len; index++)
{
if (*(str + index) != *dlimiter)
{
tokens++;
index += len_of_token(str + index, dlimiter);
}
}

return (tokens);
}

/**
* _strtok - tokenizes a string.
* @line: The string in question
* @dlimiter: delimiteriter to tokenize the string
*
* Return: pointer to an array containing the tokenized words.
*/
char **_strtok(char *line, char *dlimiter)
{
char **ptr;
int index = 0, tokens, x, letters, y;

tokens = token_counter(line, dlimiter);
if (tokens == 0)
return (NULL);

ptr = malloc(sizeof(char *) * (tokens + 2));
if (!ptr)
return (NULL);

for (x = 0; x < tokens; x++)
{
while (line[index] == *dlimiter)
index++;

letters = len_of_token(line + index, dlimiter);

ptr[x] = malloc(sizeof(char) * (letters + 1));
if (!ptr[x])
{
for (index -= 1; index >= 0; index--)
free(ptr[index]);
free(ptr);
return (NULL);
}

for (y = 0; y < letters; y++)
{
ptr[x][y] = line[index];
index++;
}

ptr[x][y] = '\0';
}
ptr[x] = NULL;
ptr[y + 1] = NULL;

return (ptr);
}

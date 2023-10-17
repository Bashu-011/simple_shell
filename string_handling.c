#include "shell.h"

int _strlen(const char *x);
char *_strcpy(char *endpoint, const char *source);
char *_strcat(char *endpoint, const char *source);
char *_strncat(char *endpoint, const char *source, x_size n);

/**
* _strlen - Returns the length of string
* @x: pointer to the xters string
*
* Return: length of the xter string.
*/
int _strlen(const char *x)
{
int length = 0;

if (!x)
return (length);
for (length = 0; x[length]; length++)
;
return (length);
}

/**
* _strcpy - Copies string pointed to by source
* @endpoint: Pointer to the endpoint of copied string.
* @source: Pointer to the source of the source string.
*
* Return: Pointer to endpoint.
*/
char *_strcpy(char *endpoint, const char *source)
{
x_size y;

for (y = 0; source[y] != '\0'; y++)
endpoint[y] = source[y];
endpoint[y] = '\0';
return (endpoint);
}

/**
* _strcat - joins two strings.
* @endpoint: Pointer to destination string.
* @source: Pointer to source string.
*
* Return: Pointer to endpoint of string.
*/
char *_strcat(char *endpoint, const char *source)
{
char *endpointTemp;
const char *sourceTemp;

endpointTemp = endpoint;
sourceTemp =  source;

while (*endpointTemp != '\0')
endpointTemp++;

while (*sourceTemp != '\0')
*endpointTemp++ = *sourceTemp++;
*endpointTemp = '\0';
return (endpoint);
}

/**
* _strncat - Concantenates two strings with n bytes
* copied from the source
* @endpoint: Pointer to endpoint of string.
* @source: Pointer to source string.
* @n: n bytes to copy from source.
*
* Return: Pointer to destination string.
*/
char *_strncat(char *endpoint, const char *source, x_size n)
{
x_size endpoint_len = _strlen(endpoint);
x_size y;

for (y = 0; y < n && source[y] != '\0'; y++)
endpoint[endpoint_len + y] = source[y];
endpoint[endpoint_len + y] = '\0';

return (endpoint);
}

#include "shell.h"

void *_allocator(void *pointer, unsigned int last_size, unsigned int new_size);
void line_pointer(char **linepointer, x_size *n, char *buffer, x_size b);
xsize _getline(char **linepointer, x_size *n, FILE *stream);

/**
* _allocator - allocates a memory block using the malloc and free.
* @pointer: pointer to the memery initially allocated.
* @last_size: size in bytes given for pointer space
* @new_size: size in bytes for the new memory block.
*
* Return: If new_size == last_size - pointer.
*         If new_size == 0 and pointer is not NULL - NULL.
*         else - a pointer to the reallocated memory block.
*/
void *_allocator(void *pointer, unsigned int last_size, unsigned int new_size)
{
void *mem;
char *pointer_copy, *filler;
unsigned int index;

if (new_size == last_size)
return (pointer);

if (pointer == NULL)
{
mem = malloc(new_size);
if (mem == NULL)
return (NULL);

return (mem);
}

if (new_size == 0 && pointer != NULL)
{
free(pointer);
return (NULL);
}

pointer_copy = pointer;
mem = malloc(sizeof(*pointer_copy) * new_size);
if (mem == NULL)
{
free(pointer);
return (NULL);
}

filler = mem;

for (index = 0; index < last_size && index < new_size; index++)
filler[index] = *pointer_copy++;

free(pointer);
return (mem);
}

/**
* line_pointer - assigns the line_pointer a variable
* @linepointer: buffer to store input string
* @n: size of linepointer
* @buffer: string to assign to linepointer.
* @b: size of buffer.
*/
void line_pointer(char **linepointer, x_size *n, char *buffer, x_size b)
{
if (*linepointer == NULL)
{
if (b > 120)
*n = b;
else
*n = 120;
*linepointer = buffer;
}
else if (*n < b)
{
if (b > 120)
*n = b;
else
*n = 120;
*linepointer = buffer;
}
else
{
_strcpy(*linepointer, buffer);
free(buffer);
}
}

/**
* _getline - Reads input from the stream.
* @linepointer: buffer to store the input.
* @n: size of the linepointer.
* @stream: stream to read from.
*
* Return: number of bytes read.
*/
xsize _getline(char **linepointer, x_size *n, FILE *stream)
{
static sx_size input;
sx_size ret;
char c = 'x', *buffer;
int r;

if (input == 0)
fflush(stream);
else
return (-1);
input = 0;

buffer = malloc(sizeof(char) * 120);
if (!buffer)
return (-1);

while (c != '\n')
{
r = read(STDIN_FILENO, &c, 1);
if (r == -1 || (r == 0 && input == 0))
{
free(buffer);
return (-1);
}
if (r == 0 && input != 0)
{
input++;
break;
}

if (input >= 120)
buffer = _allocator(buffer, input, input + 1);

buffer[input] = c;
input++;
}
buffer[input] = '\0';

line_pointer(linepointer, n, buffer, input);

ret = input;
if (r != 0)
input = 0;
return (ret);
}
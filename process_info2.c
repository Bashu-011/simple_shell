#include "shell.h"

void line_handler(char **line, xsize read);
xsize gets_length(char *line);
void check_logicals(char *line, xsize *new_len);

/**
* line_handler - divides the line gotten from standard input
* @line: pointer to the line in standard input.
* @read: length of line.
*
* Description: Spaces are insert to separate ";", "||", and "&&".
*              Replaces "#" with '\0'.
*/
void line_handler(char **line, xsize read)
{
char *last_line, *new_line;
char previous, current, next;
x_size i, j;
xsize new_len;

new_len = gets_length(*line);
if (new_len == read - 1)
return;
new_line = malloc(new_len + 1);
if (!new_line)
return;
j = 0;
last_line = *line;
for (i = 0; last_line[i]; i++)
{
current = last_line[i];
next = last_line[i + 1];
if (i != 0)
{
previous = last_line[i - 1];
if (current == ';')
{
if (next == ';' && previous != ' ' && previous != ';')
{
new_line[j++] = ' ';
new_line[j++] = ';';
continue;
}
else if (previous == ';' && next != ' ')
{
new_line[j++] = ';';
new_line[j++] = ' ';
continue;
}
if (previous != ' ')
new_line[j++] = ' ';
new_line[j++] = ';';
if (next != ' ')
new_line[j++] = ' ';
continue;
}
else if (current == '&')
{
if (next == '&' && previous != ' ')
new_line[j++] = ' ';
else if (previous == '&' && next != ' ')
{
new_line[j++] = '&';
new_line[j++] = ' ';
continue;
}
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
new_line[j++]  = ' ';
else if (previous == '|' && next != ' ')
{
new_line[j++] = '|';
new_line[j++] = ' ';
continue;
}
}
}
else if (current == ';')
{
if (i != 0 && last_line[i - 1] != ' ')
new_line[j++] = ' ';
new_line[j++] = ';';
if (next != ' ' && next != ';')
new_line[j++] = ' ';
continue;
}
new_line[j++] = last_line[i];
}
new_line[j] = '\0';

free(*line);
*line = new_line;
}

/**
* gets_length - gets the new length of the divided line
*               by ";", "||", "&&&", or "#".
* @line: line to check.
*
* Return: new length of the line.
*
* Description: reduces lines containing '#' comments with '\0'.
*/

xsize gets_length(char *line)
{
x_size i;
xsize new_len = 0;
char current, next;

for (i = 0; line[i]; i++)
{
current = line[i];
next = line[i + 1];
if (current == '#')
{
if (i == 0 || line[i - 1] == ' ')
{
line[i] = '\0';
break;
}
}
else if (i != 0)
{
if (current == ';')
{
if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
{
new_len += 2;
continue;
}
else if (line[i - 1] == ';' && next != ' ')
{
new_len += 2;
continue;
}
if (line[i - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
else
check_logicals(&line[i], &new_len);
}
else if (current == ';')
{
if (i != 0 && line[i - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
}
/**
* check_logicals - checks the lines for any
*                  logical operators "||" or "&&".
* @line: pointer to the xter to check in the line.
* @new_len: Pointer to new_len in gets_length function.
*/
void check_logicals(char *line, xsize *new_len)
{
char previous, current, next;

previous = *(line - 1);
current = *line;
next = *(line + 1);

if (current == '&')
{
if (next == '&' && previous != ' ')
(*new_len)++;
else if (previous == '&' && next != ' ')
(*new_len)++;
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
(*new_len)++;
else if (previous == '|' && next != ' ')
(*new_len)++;
}
}

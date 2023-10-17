#include "shell.h"

/**
* input_buf - buffers chained command
* @command: a parameter struct
* @buf: the address of a buffer
* @len: address of a len variable
*
* Return: bytes read
*/
ssize_t input_buf(x_info *command, char **buf, size_t *len)
{
ssize_t r = 0;
size_t len_p = 0;

if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)command->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigint_handler);
#if USE_GETLINE
r = getline(buf, &len_p, stdin);
#else
r = _getline(command, buf, &len_p);
#endif
if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0';
r--;
}
command->linecounter_flag = 1;
remove_comments(*buf);
build_history_list(command, *buf, command->histcount++);
{
*len = r;
command->cmd_buf = buf;
}
}
}
return (r);
}

/**
* get_input - gets a line input
* without the newline
* @command: a parameter struct
*
* Return: bytes read
*/
ssize_t get_input(x_info *command)
{
static char *buf;
static size_t i, j, len;
ssize_t r = 0;
char **buf_p = &(command->arg), *p;

_putchar(BUF_FLUSH);
r = input_buf(command, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len)
{
j = i;
p = buf + i;

check_chain(command, buf, &j, i, len);
while (j < len)
{
if (ch_delim(command, buf, &j))
break;
j++;
}

i = j + 1;
if (i >= len)
{
i = len = 0;
command->cmd_buf_type = CMD_NORM;
}

*buf_p = p;
return (_my_strlen(p));
}

*buf_p = buf;
return (r);
}

/**
* read_buf - reads a buffer
* @command: parameter struct
* @buf: buffer
* @i: size
*
* Return: r
*/
ssize_t read_buf(x_info *command, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(command->readfil_desc, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
* _getline - gets the next line of input from STDIN
* @command: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
*
* Return: s
*/
int _getline(x_info *command, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;

r = read_buf(command, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = my_stringchar(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p)
return (p ? free(p), -1 : -1);

if (s)
_my_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);

s += k - i;
i = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
* sigint_handler - checks on the copy fn
* @sig_num: signal number
*
* Return: void
*/
void sigint_handler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

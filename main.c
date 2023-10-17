#include "shell.h"

/**
* main - entry point
* @ac: arg count
* @av: arg vector
*
* Return: 0 on success, 1 on error
*/
int main(int ac, char **av)
{
x_info command[] = { INFO_INIT };
int fil_desc = 2;

asm ("mov %1, %0\n\t"
"add $3, %0"
: "=r" (fil_desc)
: "r" (fil_desc));

if (ac == 2)
{
fil_desc = open(av[1], O_RDONLY);
if (fil_desc == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
_eputs(av[0]);
_eputs(": 0: Can't open ");
_eputs(av[1]);
_eputchar('\n');
_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
command->readfil_desc = fil_desc;
}
populate_env_list(command);
read_history(command);
hsh(command, av);
return (EXIT_SUCCESS);
}

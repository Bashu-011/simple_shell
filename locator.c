#include "shell.h"

char *fills_path_directory(char *path);
list_1 *gets_path_directory(char *path);
char *gets_location(char *command);

/**
* gets_location - Locates the commands in the PATH.
* @command: The specified command to be located.
*
* Return: Null, if command can't be located or for an error
*         else path of the command.
*/
char *gets_location(char *command)
{
char **path, *temp;
list_1 *dirs, *head;
struct stat st;

path = _getenv("PATH");
if (!path || !(*path))
return (NULL);

dirs = gets_path_directory(*path + 5);
head = dirs;

while (dirs)
{
temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
if (!temp)
return (NULL);

_strcpy(temp, dirs->dir);
_strcat(temp, "/");
_strcat(temp, command);

if (stat(temp, &st) == 0)
{
end_node(head);
return (temp);
}

dirs = dirs->next;
free(temp);
}

end_node(head);

return (NULL);
}

/**
* fills_path_directory - Copies the path, replaces leading and trailing
*		   colons (:) with the current wd.
* @path: The colon seperating the list of directories.
*
* Return: Copy of path with any leading or trailing colons replaced
*	   with the current wd.
*/
char *fills_path_directory(char *path)
{
int i, length = 0;
char *copy_path, *pwd;

pwd = *(_getenv("PWD")) + 4;
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
length += _strlen(pwd) + 1;
else
length++;
}
else
length++;
}
copy_path = malloc(sizeof(char) * (length + 1));
if (!copy_path)
return (NULL);
copy_path[0] = '\0';
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (i == 0)
{
_strcat(copy_path, pwd);
_strcat(copy_path, ":");
}
else if (path[i + 1] == ':' || path[i + 1] == '\0')
{
_strcat(copy_path, ":");
_strcat(copy_path, pwd);
}
else
_strncat(copy_path, &path[i], 1);
}
else
{
_strncat(copy_path, &path[i], 1);
}
}
return (copy_path);
}

/**
* gets_path_directory - Tokenizes a colon-separated list of
*              wd into the list_1 linked list.
* @path: The list of directories.
*
* Return: A pointer to the initialized linked list.
*/
list_1 *gets_path_directory(char *path)
{
int index;
char **dirs, *copy_path;
list_1 *head = NULL;

copy_path = fills_path_directory(path);
if (!copy_path)
return (NULL);
dirs = _strtok(copy_path, ":");
free(copy_path);
if (!dirs)
return (NULL);

for (index = 0; dirs[index]; index++)
{
if (end_node(&head, dirs[index]) == NULL)
{
free_list_1(head);
free(dirs);
return (NULL);
}
}

free(dirs);

return (head);
}

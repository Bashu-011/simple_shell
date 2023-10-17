#include "shell.h"

char **_copiedenv(void);
void free_env(void);
char **_setenv(const char *var);

/**
* _copiedenv - Creates a copy of the environment.
*
* Return: If errors occur - NULL.
*         - a pointer to pointer to the new copy.
*/
char **_copiedenv(void)
{
char **new_env;
x_size size;
int index;

for (size = 0; env[size]; size++)
;

new_env = malloc(sizeof(char *) * (size + 1));
if (!new_env)
return (NULL);

for (index = 0; env[index]; index++)
{
new_env[index] = malloc(_strlen(env[index]) + 1);

if (!new_env[index])
{
for (index--; index >= 0; index--)
free(new_env[index]);
free(new_env);
return (NULL);
}
_strcpy(new_env[index], env[index]);
}
new_env[index] = NULL;

return (new_env);
}

/**
* free_env - Frees the copy of the environment.
*/
void free_env(void)
{
int index;

for (index = 0; env[index]; index++)
free(env[index]);
free(env);
}

/**
* _setenv - sets an environmental variable from the PATH.
* @var: name of the environmental variable to set.
*
* Return: If environmental valriable does not exist - NULL.
*         else - a pointer to the envmental variable.
*/
char **_setenv(const char *var)
{
int index, len;

len = _strlen(var);
for (index = 0; env[index]; index++)
{
if (_strncmp(var, env[index], len) == 0)
return (&env[index]);
}

return (NULL);
}

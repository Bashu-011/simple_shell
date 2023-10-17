#include "shell.h"

void h_environment(void);
void h_setenv(void);
void h_unsetenv(void);
void h_history(void);

/**
* h_environment - shows info on the shell inbuilt command env.
*/
void h_environment(void)
{
char *message = "env: env\n\tPrint the current environment.\n";

write(STDOUT_FILENO, message, _strlen(message));
}

/**
* h_setenv -shows info on the shell inbuilt command setenv.
*/
void h_setenv(void)
{
char *message = "setenv: setenv [VARIABLE] [VALUE]\n\tStarts a new";

write(STDOUT_FILENO, message, _strlen(message));
message = "environment value, or changes an existing one.\n\n";
write(STDOUT_FILENO, message, _strlen(message));
message = "\tUpon failure, prints  message to the stderr.\n";
write(STDOUT_FILENO, message, _strlen(message));
}

/**
* h_unsetenv - shows information on the inbuilt shell command unsentenv
*/
void h_unsetenv(void)
{
char *message = "unsetenv: unsetenv [VARIABLE]\n\tRemoves the ";

write(STDOUT_FILENO, message, _strlen(message));
message = "environmental variable.\n\n\tWhen a failure happens, prints a ";
write(STDOUT_FILENO, message, _strlen(message));
message = "message to stderr.\n";
write(STDOUT_FILENO, message, _strlen(message));
}

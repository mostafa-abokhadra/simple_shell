#include "1_shell.h"
#include "2_shell.h"

/**
  * main - entry point
  * @argc: args count
  * @argv: args
  *
  * Description: shell entry
  * Return: 0
  */
int main(int argc __attribute__((unused)), char *argv[])
{
		int out = 0;
		char *command_line = NULL;
		char **tokenized = NULL;
		char **path_dir = NULL;

		path_dir = _sub();
		while (1)
		{
			command_line = read_command();
			if (!command_line || strcmp(command_line, "exit") == 0)
			{
				if (!command_line)
				{
					if (isatty(STDIN_FILENO))
						printf("\n");
				}
				else
					free(command_line), command_line = NULL;
				_free2d(path_dir);
				exit(out);
			}
			if (strcmp(command_line, "env") == 0)
				out_env(command_line);
			else
			{
				tokenized = set_command(command_line);
				if (!tokenized)
					continue;
				out = fork_exec(tokenized, argv, path_dir);
			}
		}
		_free2d(path_dir);
		return (0);
}



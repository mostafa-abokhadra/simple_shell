#ifndef SHELL2
#define SHELL2

/**
  * _betty - getting first command
  * @name: full command
  * @c: arg1
  * @i: arg2
  *
  * Description: additional func to pass betty
  * Return: nothing
  */
void _betty(char *name, int *c, int *i)
{
	if (!name)
		return;
	for (*i = 0; name[*i]; (*i)++)
	{
		if (name[*i] == '/')
			*c = *i;
	}
}

/**
  * check_exist - check file
  * @name: name of file
  * @path_dir: directories to search on
  *
  * Description: existence of a file check
  * Return: state of existence
  */
char *check_exist(char *name, char **path_dir)
{
		char *ptr = NULL, *single_path = NULL;
		int i, c = 0;

		if (!name || !path_dir)
			return (NULL);
		 _betty(name, &c, &i);
		 ptr = malloc(sizeof(char) * (i - c + 1));
		if (!ptr)
		{
			free(ptr), ptr = NULL;
			return (NULL);
		}
		for (i = 0; name[c]; i++)
			ptr[i] = name[c++];
		ptr[i] = '\0';
		for (i = 0; path_dir[i]; i++)
		{
			single_path = malloc(sizeof(char) * ((strlen(path_dir[i])
							+ strlen(ptr) + 3)));
			if (!single_path)
			{
				free(ptr), ptr = NULL;
				return (NULL);
			}
			strcpy(single_path, path_dir[i]);
			strcat(single_path, "/");
			strcat(single_path, ptr);
			if (access(single_path, F_OK) == 0)
			{
				free(ptr), ptr = NULL;
				return (single_path);
			}
			else
			{
				free(single_path), single_path = NULL;
				continue;
			}
		}
		free(ptr), ptr = NULL;
		return (NULL);
}

/**
  * fork_exec - forking
  * @tokenized: tokenizing
  * @argv: args
  * @path_dir: directories
  *
  * Description: executing
  * Return: status
  */
int fork_exec(char *tokenized[], char *argv[], char **path_dir)
{
		pid_t pid = getpid();
		int status;
		char *full_path = NULL;
		static int error;

		if (tokenized[0][0] == '.')
		{
			if (access(tokenized[0], F_OK) == 0)
				full_path = strdup(tokenized[0]);
		}
		else
			full_path = check_exist(tokenized[0], path_dir);
		if (full_path)
		{
			free(tokenized[0]), tokenized[0] = NULL;
			tokenized[0] = strdup(full_path);
			free(full_path), pid = fork();
		}
		else
		{
			free(full_path);
			printf("%s: %d: %s: not found\n", argv[0], ++error, tokenized[0]);
			_free2d(tokenized);
			return (127);
		}
		if (pid == 0)
		{
			if (execve(tokenized[0], tokenized, environ))
			{
				perror(argv[0]);
				_free2d(tokenized);
				_free2d(path_dir), exit(127);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			_free2d(tokenized);
		}
		return (WEXITSTATUS(status));
}

/**
  * set_command -setting command
  * @command_line: the command
  *
  * Description: command line set
  * Return: the commnd line
  */
char **set_command(char *command_line)
{
		int argc = 0, i;
		char **tokenized = NULL;
		char *token = NULL, *copy_command = NULL;

		if (!command_line)
			return (NULL);
		copy_command = strdup(command_line);
		token = strtok(copy_command, " \n\t");
		if (!token)
		{
			free(copy_command), copy_command = NULL;
			free(command_line), command_line = NULL;
			return (NULL);
		}
		for (; token; argc++, token = strtok(NULL, " \n\t"))
		{}
		free(copy_command), copy_command = NULL;
		tokenized = malloc(sizeof(char *) * (argc + 1));
		if (!tokenized)
		{
			free(command_line), command_line = NULL;
			return (NULL);
		}
		token = strtok(command_line, " \n\t");
		for (i = 0; token; i++, token = strtok(NULL, " \n\t"))
			tokenized[i] = strdup(token);
		tokenized[i] = NULL;
		free(command_line), command_line = NULL;
		return (tokenized);
}

/**
  * read_command - reading input
  *
  * Description: getting input
  *
  * Return: the input
  */
char *read_command()
{
		char *command_line = NULL;
		int read;
		size_t size = 0;

		if (isatty(STDIN_FILENO))
			printf("$ ");
		read = getline(&command_line, &size, stdin);
		if (read == -1)
		{
			free(command_line);
			return (NULL);
		}
		if (command_line[read - 1] == '\n' && read != 1)
			command_line[read - 1] = '\0', read--;
		return (command_line);
}

#endif


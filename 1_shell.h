#ifndef SHELL1
#define SHELL1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

/**
  * out_env - print env
  * @str: to be freed
  *
  * Description: printing built in env
  * Return: nothing
  */
void out_env(char *str)
{
		int i;

		for (i = 0 ; environ[i] ; i++)
		{
			printf("%s\n", environ[i]);
		}
		free(str), str = NULL;
}

/**
  * _free2d - freeing 2d array
  * @arr: the 2d array
  *
  * Description: freeing memmory
  * Return: nothing
  */
void _free2d(char **arr)
{
		int i;

		if (arr == NULL)
			return;
		for (i = 0; arr[i]; i++)
			free(arr[i]), arr[i] = NULL;
		free(arr), arr = NULL;
}

/**
  * _remove - removing path key word
  * @str: path var
  *
  * Description: remove not important word
  * Return: path without path key word
  */
char *_remove(char *str)
{
		char *PATH = NULL;
		int i;

		if (!str)
			return (NULL);
		for (i = 0; i < 5; i++)
			str++;
		PATH = strdup(str);
		if (!PATH)
			return (NULL);
		return (PATH);
}

/**
  * _sub - getting path
  *
  * Description: get path from env
  *
  * Return: path
  */
char **_sub()
{
		char *PATH = NULL, *sub = NULL, *token = NULL, *copy = NULL;
		char **path_dir = NULL;
		size_t path_no = 0;
		int i = 0;

		for (; environ[i] ; i++)
		{
			sub = strndup(environ[i], 4);
			if (strcmp(sub, "PATH") == 0)
			{
				PATH = _remove(environ[i]);
				break;
			}
			free(sub), sub = NULL;
		}
		free(sub), sub = NULL;
		if (!PATH)
			return (NULL);
		copy = strdup(PATH);
		token = strtok(copy, ":");
		if (!copy)
		{
			free(PATH), PATH = NULL;
			return (NULL);
		}
		for (path_no = 0; token ; path_no++, token = strtok(NULL, ":"))
		{}
		free(copy), copy = NULL;
		path_dir = malloc(sizeof(char *) * (path_no + 1));
		if (!path_dir)
		{
			free(PATH), PATH = NULL;
			return (NULL);
		}
		token = strtok(PATH, ":");
		for (i = 0; token; i++, token = strtok(NULL, ":"))
			path_dir[i] = strdup(token);
		path_dir[i] = NULL;
		free(PATH), PATH = NULL;
		return (path_dir);
}
#endif


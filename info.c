#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @in: struct address
 */
void clear_info(info_t *in)
{
	in->arg = NULL;
	in->argv = NULL;
	in->path = NULL;
	in->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @in: struct address
 * @av: argument vector
 */
void set_info(info_t *in, char **av)
{
	int i = 0;

	in->fname = av[0];
	if (in->arg)
	{
		in->argv = strtow(in->arg, " \t");
		if (!in->argv)
		{

			in->argv = malloc(sizeof(char *) * 2);
			if (in->argv)
			{
				in->argv[0] = _strdup(in->arg);
				in->argv[1] = NULL;
			}
		}
		for (i = 0; in->argv && in->argv[i]; i++)
			;
		in->argc = i;

		replace_alias(in);
		replace_vars(in);
	}
}

/**
 * free_info - frees info_t struct fields
 * @in: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *in, int all)
{
	ffree(in->argv);
	in->argv = NULL;
	in->path = NULL;
	if (all)
	{
		if (!in->cmd_buf)
			free(in->arg);
		if (in->env)
			free_list(&(in->env));
		if (in->history)
			free_list(&(in->history));
		if (in->alias)
			free_list(&(in->alias));
		ffree(in->environ);
			in->environ = NULL;
		bfree((void **)in->cmd_buf);
		if (in->readfd > 2)
			close(in->readfd);
		_putchar(BUF_FLUSH);
	}
}

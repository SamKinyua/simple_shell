#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @x: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
*/

char **strtow(char *str, char *x)
{
	int y, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!x)
		x = " ";
	for (y = 0; str[y] != '\0'; y++)
		if (!is_delim(str[y], x) && (is_delim(str[y + 1], x) || !str[y + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[y], x))
			y++;
		k = 0;
		while (!is_delim(str[y + k], x) && str[y + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[y++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @x: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
*/
char **strtow2(char *str, char x)
{
	int y, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (y = 0; str[y] != '\0'; y++)
		if ((str[y] != x && str[y + 1] == x) ||
		    (str[y] != x && !str[y + 1]) || str[y + 1] == x)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (y = 0, j = 0; j < numwords; j++)
	{
		while (str[y] == x && str[y] != x)
			y++;
		k = 0;
		while (str[y + k] != x && str[y + k] && str[y + k] != x)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[y++];
		s[j][m] = 0;
	}
	s[j] = NULL;

	return (s);
}

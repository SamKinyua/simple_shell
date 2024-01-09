#include "shell.h"

/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @suc: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
*/
char *_strncpy(char *dest, char *suc, int n)
{
	int y, j;
	char *s = dest;

	y = 0;
	while (suc[y] != '\0' && y < n - 1)
	{
		dest[y] = suc[y];
		y++;
	}
	if (y < n)
	{
		j = y;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two string
 * @dest: the first string
 * @suc: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
*/
char *_strncat(char *dest, char *suc, int n)
{
	int y, j;
	char *s = dest;

	y = 0;
	j = 0;
	while (dest[y] != '\0')
		y++;
	while (suc[j] != '\0' && j < n)
	{
		dest[y] = suc[j];
		y++;
		j++;
	}
	if (j < n)
		dest[y] = '\0';
	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be parsed
 * @ch: the character to look for
 * Return: (s) a pointer to the memory area s
*/
char *_strchr(char *s, char ch)
{
	do {
		if (*s == ch)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}

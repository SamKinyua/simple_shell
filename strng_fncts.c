#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @t: the string whose length to check
 * Return: integer length of string
*/
int _strlen(char *t)
{
	int i = 0;

	if (!t)
		return (0);

	while (*t++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @z1: the first strang
 * @z2: the second strang
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int _strcmp(char *z1, char *z2)
{
	while (*z1 && *z2)
	{
		if (*z1 != *z2)
			return (*z1 - *z2);
		z1++;
		z2++;
	}
	if (*z1 == *z2)
		return (0);
	else
		return (*z1 < *z2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 * Return: address of next char of haystack or NULL
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @suc: the source buffer
 * Return: pointer to destination buffer
*/
char *_strcat(char *dest, char *suc)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*suc)
		*dest++ = *suc++;
	*dest = *suc;
	return (ret);
}

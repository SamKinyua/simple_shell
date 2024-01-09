#include "shell.h"

/**
 * *_memset - fills memory with a constant byte
 * @t: the pointer to the memory area
 * @v: the byte to fill *s with
 * @m: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
*/
char *_memset(char *t, char v, unsigned int m)
{
	unsigned int i;

	for (i = 0; i < m; i++)
		t[i] = v;
	return (t);
}

/**
 * ffree - frees a string of strings
 * @cc: string of strings
*/
void ffree(char **cc)
{
	char **a = cc;

	if (!cc)
		return;
	while (*cc)
		free(*cc++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *b;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	b = malloc(new_size);
	if (!b)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		b[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (b);
}

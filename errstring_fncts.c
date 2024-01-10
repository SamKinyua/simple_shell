#include "shell.h"

/**
 * _eputs - prints input string
 * @str: string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
    int r = 0;

    if (!str)
        return;
    while (str[r] != '\0')
    {
        _eputchar(str[r]);
        r++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: Character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    static int r;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
    {
        write(2, buf, r);
        r = 0;
    }
    if (c != BUF_FLUSH)
        buf[r++] = c;
    return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: Character to print
 * @fd: The file descriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    static int r;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || r >= WRITE_BUF_SIZE)
    {
        write(fd, buf, r);
        r = 0;
    }
    if (c != BUF_FLUSH)
        buf[r++] = c;
    return (1);
}

/**
 * _putsfd - Prints an input string
 * @str: String to be printed
 * @fd: the file descriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
    int r = 0;

    if (!str)
        return (0);
    while (*str)
    {
        r += _putfd(*str++, fd);
    }
    return (r);
}


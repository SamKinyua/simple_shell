#include "shell.h"

/**
 * get_history_file - Gets the history file
 * @in: Parameter struct
 * Return: Allocated string containing history file
 */
char *get_history_file(info_t *in)
{
    char *buf, *dir;

    dir = _getenv(in, "HOME=");
    if (!dir)
        return (NULL);

    buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
    if (!buf)
        return (NULL);

    buf[0] = 0;
    _strcpy(buf, dir);
    _strcat(buf, "/");
    _strcat(buf, HIST_FILE);

    return (buf);
}

/**
 * write_history - Creates a file, or appends to an existing file
 * @in: The parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *in)
{
    ssize_t f;
    char *filename = get_history_file(in);
    list_t *node = NULL;

    if (!filename)
        return (-1);

    f = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (f == -1)
        return (-1);

    for (node = in->history; node; node = node->next)
    {
        _putsfd(node->str, f);
        _putfd('\n', f);
    }
    _putfd(BUF_FLUSH, f);
    close(f);

    return (1);
}

/**
 * read_history - Reads history from file
 * @in: The parameter struct
 * Return: Histcount on success, 0 otherwise
 */
int read_history(info_t *in)
{
    int r, last = 0, linecount = 0;
    ssize_t f, rdlen, fsize = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_file(in);

    if (!filename)
        return (0);

    f = open(filename, O_RDONLY);
    free(filename);

    if (f == -1)
        return (0);

    if (!fstat(f, &st))
        fsize = st.st_size;

    if (fsize < 2)
        return (0);

    buf = malloc(sizeof(char) * (fsize + 1));

    if (!buf)
        return (0);

    rdlen = read(f, buf, fsize);
    buf[fsize] = 0;

    if (rdlen <= 0)
        return (free(buf), 0);

    close(f);

    for (r = 0; r < fsize; r++)
        if (buf[r] == '\n')
        {
            buf[r] = 0;
            build_history_list(in, buf + last, linecount++);
            last = r + 1;
        }

    if (last != r)
        build_history_list(in, buf + last, linecount++);

    free(buf);
    in->histcount = linecount;

    while (in->histcount-- >= HIST_MAX)
        delete_node_at_index(&(in->history), 0);

    renumber_history(in);

    return (in->histcount);
}

/**
 * build_history_list - Adds entry to a history linked list
 * @in: Structure containing potential arguments. Used to maintain
 * @buf: Buffer
 * @linecount: The history linecount, histcount
 * Return: Always 0
 */
int build_history_list(info_t *in, char *buf, int linecount)
{
    list_t *node = NULL;

    if (in->history)
        node = in->history;

    add_node_end(&node, buf, linecount);

    if (!in->history)
        in->history = node;

    return (0);
}

/**
 * renumber_history - Renumbers the history linked list after changes
 * @in: Structure containing potential arguments. Used to maintain
 * Return: The new histcount
 */
int renumber_history(info_t *in)
{
    list_t *node = in->history;
    int r = 0;

    while (node)
    {
        node->num = r++;
        node = node->next;
    }

    return (in->histcount = r);
}


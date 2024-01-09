#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @in: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buf(info_t *in, char **buf, size_t *len)
{
ssize_t c = 0;
size_t len_p = 0;

if (!*len) /* if there is nothing left in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
c = getline(buf, &len_p, stdin);
#else
c = _getline(in, buf, &len_p);
#endif
if (c > 0)
{
if ((*buf)[c - 1] == '\n')
{
(*buf)[c - 1] = '\0'; /* remove trailing newline */
c--;
}
in->linecount_flag = 1;
remove_comments(*buf);
build_history_list(in, *buf, in->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = c;
in->cmd_buf = buf;
}
}
}
return (c);
}

/**
 * get_input - gets a line minus the newline
 * @in: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *in)
{
static char *buf; /* the ';' command chain buffer */
static size_t z, a, len;
ssize_t c = 0;
char **buf_p = &(in->arg), *p;

_putchar(BUF_FLUSH);
c = input_buf(in, &buf, &len);
if (c == -1) /* EOF */
return (-1);
if (len)	/* we have commands left in the chain buffer */
{
a = z; /* init new iterator to current buf position */
p = buf + z; /* get pointer for return */

check_chain(in, buf, &a, z, len);
while (a < len) /* iterate to semicolon or end */
{
if (is_chain(in, buf, &a))
break;
a++;
}

z = a + 1; /* increment past nulled ';'' */
if (z >= len) /* reached end of buffer? */
{
z = len = 0; /* reset position and length */
in->cmd_buf_type = CMD_NORM;
}

*buf_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}

*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
return (c); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @in: parameter struct
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t read_buf(info_t *in, char *buf, size_t *i)
{
ssize_t r = 0;

if (*i)
return (0);
r = read(in->readfd, buf, READ_BUF_SIZE);
if (r >= 0)
*i = r;
return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @in: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *in, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t z, len;
size_t k;
ssize_t r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;

p = *ptr;
if (p && length)
s = *length;
if (z == len)
z = len = 0;

r = read_buf(in, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);

c = _strchr(buf + z, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);

if (s)
_strncat(new_p, buf + z, k - z);
else
_strncpy(new_p, buf + z, k - z + 1);

s += k - z;
z = k;
p = new_p;

if (length)
*length = s;
*ptr = p;
return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}

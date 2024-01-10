#include "shell.h"

/**
 * get_environ - Returns the string array copy of the environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
   
char **get_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */

int _unsetenv(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t r = 0;
    char *a;

    if (!node || !var)
        return (0);

    while (node)
    {
        a = starts_with(node->str, var);
        if (a && *a == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), r);
            r = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        r++;
    }
    return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */

int _setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *a;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);

    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        a = starts_with(node->str, var);
        if (a && *a == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);

    free(buf);
    info->env_changed = 1;
    return (0);
}


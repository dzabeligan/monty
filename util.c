#include "util.h"

/**
 * find - find character in string
 *
 * @str: String to search from
 * @c: Character to search for
 * Return: 1 if character is found, else return 0
 */
int find(const char *str, const char c)
{
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

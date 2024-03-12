#include "s21_string.h"

int s21_strlen(char *data)
{
    int res = 0;
    while (data[res] != '\0')
    {
        res += 1;
    }
    return res;
}

int s21_strcmp(char *a, char *b)
{
    int res = 0;
    while (*a == *b && *a != '\0')
    {
        a++;
        b++;
    }
    if (*a == '\0' && *b == '\0')
    {
        res = 0;
    }
    else if (*a > *b)
    {
        res = 1;
    }
    else
        res = -1;
    return res;
}
char *s21_strcpy(char *dst, const char *src)
{
    char *res = dst;
    while (*src != '\0')
    {
        *dst = *src;
        dst++;
        src++;
    }
    *(dst++) = '\0';
    return res;
}

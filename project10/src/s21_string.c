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
char *s21_strcat(char *dst, char *src)
{
    int len_1 = s21_strlen(dst);
    int len_2 = len_1 + s21_strlen(src);
    for (int i = 0; src[i] != '\0'; i++)
    {
        dst[len_1 + i] = src[i];
    }
    dst[len_2] = '\0';
    return dst;
}
char *s21_strchr(char *src, int c)
{
    int count = 0;
    while (src[count] && src[count] != c)
    {
        count += 1;
    }
    return src[count] == c ? src + count : NULL;
}
char *s21_strstr(char *str, char *substr)
{
    int len_2 = s21_strlen(substr);
    int j = 0;
    char *res = NULL;
    if (s21_strlen(str) > 1 && s21_strlen(substr) > 1)
    {
        for (int i = 0; i < s21_strlen(str); i++)
        {
            if (str[i] == substr[j])
            {
                j++;
                if (j == len_2)
                {
                    res = (str + i - j + 1);
                }
            }
        }
    }
    return res;
}
char * s21_strtok(char * str, char * substr) {
    
}
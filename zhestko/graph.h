#pragma once

typedef struct stack_int
{
    int *array;
    int n;
} stack_int;

typedef struct stack_char
{
    char *numbers;
    int n;
} stack_char;
char *infix_to_postfix(char *array, int len);
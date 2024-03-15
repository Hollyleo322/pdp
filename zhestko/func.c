#include "graph.h"
#include <stdlib.h>
#include <string.h>
char *infix_to_postfix(char *array, int len)
{
    char *numbers = "1234567890";
    char *operands = "+-*/()iotgql";
    stack_char *mm = malloc(sizeof(stack_char));
    mm.array_char = malloc(sizeof(char) * len);
    char *res = malloc(sizeof(char) * len);
    int count_array = 0;
    char tmp;
    for (int i = 0; i < len; i++)
    {
        if (strchr(numbers, array[i]))
        {
            res[count_array] = array[i];
            count_array += 1;
        }
        else
        {
            if (array[i] = '(')
            {
                push(array[i], mm);
            }
            else if (array[i] = ')')
            {
                while (tmp = pop(mm) != '(')
                {
                    res[count_array] = tmp;
                    count_array += 1;
                }
            }
        }
    }
}

void push(char a, stack_char *s)
{
    s->numbers[s->n] = a;
    s->n += 1;
    printf("push = %d\n", s->numbers[s->n - 1]);
}
char pop(stack_char *stack_value)
{
    char res = stack_value->numbers[stack_value->n - 1];
    stack_value->n -= 1;
    printf("pop = %d\n", res);
    return res;
}
int priority(char *a)
{
    int res;
    if (a == 'i' || a == 'o' || a == 't' || a == "g" || a == 'q' || a == 'l')
    {
        res = 3;
    }
    else if (a == '*' || a == '/')
    {
        res = 2;
    }
    else if (a == '(')
    {
        res = 0;
    }
    else
        res = 1;
    return res;
}
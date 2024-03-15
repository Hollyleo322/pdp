#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"

#define N 1000

int main()
{
    char infix[N];
    fgets(infix, N, stdin);
    int len = 0;
    for (int i = 0; infix[i] != '\n'; i++)
    {
        len += 1;
    }
    if (len != 0)
    {
        char *postfix = infix_to_postfix(infix, len);
    }
    else
        printf("n/a");
}
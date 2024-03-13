#pragma once
typedef struct {
    int *a;
    int n;
    int size;
} stack;

stack *init(int size);
void push(stack *res, int input);
int pop(stack *s);
void destroy(stack *res);

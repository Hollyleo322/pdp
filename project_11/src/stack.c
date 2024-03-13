#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int *a;
    int n;
    int size;
} stack;
stack *init(int size) {
    stack *res;
    res = malloc(sizeof(stack));
    res->a = malloc(size * sizeof(int));
    res->size = size;
    res->n = 0;
    return res;
}
void push(stack *res, int input) {
    if (res->n == res->size) {
        res->size *= 2;
        res->a = realloc(res->a, res->size);
    }
    res->a[res->n] = input;
    res->n += 1;
}
int pop(stack *s) {
    int res;
    if (s->n == 0)
        res = -1;
    else {
        res = s->a[s->n - 1];
        s->n -= 1;
    }
    return res;
}
void destroy(stack *res) {
    res->size = 0;
    res->n = 0;
    free(res->a);
    free(res);
}
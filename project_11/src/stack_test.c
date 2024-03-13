#include "stack.h"

#include <stdio.h>

int main() {
    int size = 5;
    int a = 3;
    int b = 5;
    stack *sp = init(size);
    push(sp, a);
    printf("%s\n", sp->a[sp->n - 1] == 3 && sp->n == 1 ? "SUCCESS" : "FAIL");
    push(sp, b);
    printf("%s\n", sp->a[sp->n - 1] == 2 && sp->n == 1 ? "SUCCESS" : "FAIL");
    int res_1_pop = pop(sp);
    printf("%s\n", res_1_pop == 5 ? "SUCCESS" : "FAIL");
    int res_2_pop = pop(sp);
    printf("%s\n", res_2_pop == 2 ? "SUCCESS" : "FAIL");
    destroy(sp);
    return 0;
}
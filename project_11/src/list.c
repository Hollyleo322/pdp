#include "list.h"

#include <stdio.h>
#include <stdlib.h>

struct node *init(const struct door *door) {
    struct node *res = malloc(sizeof(struct node));
    res->doors = *door;
    res->next = NULL;
    return res;
}
struct node *add_door(struct node *elem, struct door *door) {
    struct node *res = init(door);
    res->next = elem;
    elem = res;
    return elem;
}
struct node *find_door(int door_id, struct node *root) {
    struct node *res = NULL;

    for (struct node *p = root; p != NULL; p = p->next) {
        if (p->doors.id == door_id) {
            res = p;
            break;
        }
    }
    return res;
}
struct node *remove_door(struct node *elem, struct node *root) {
    root->next = elem->next;
    free(elem);
    return root;
}
void destroy(struct node *root) {
    struct node *p;
    struct node *d = root;
    while (d != NULL) {
        p = d->next;
        free(d);
        d = p;
    }
}

#pragma once
#include "door_struct.h"

struct node
{
    struct door doors;
    struct node *next;
};
struct node *init(const struct door *door);
struct node *add_door(struct node *elem, struct door *door);
struct node *find_door(int door_id, struct node *root);
struct node *remove_door(struct node *elem, struct node *root);
void destroy(struct node *root);
void print_list(struct node *root);

#include "list.h"

#include <stdio.h>

#include "door_struct.h"

int main() {
    int count = 0;
    struct door first;
    struct door second;
    struct door third;
    first.id = 1;
    first.status = 0;
    second.id = 2;
    second.status = 1;
    third.id = 3;
    third.status = 0;
    struct node *root = init(&first);
    struct node *check_remove_1 = root;
    root = add_door(root, &second);
    struct node *check_remove_2 = find_door(2, root);
    printf("%s\n", root->doors.id == 2 ? "SUCCESS" : "FAIL");
    root = add_door(root, &third);
    printf("%s\n", root->doors.id == 1 ? "SUCCESS" : "FAIL");
    root = remove_door(check_remove_2, root);
    for (struct node *p = root; p != NULL; p = p->next) {
        count += 1;
    }
    printf("%s\n", count == 2 ? "SUCCESS" : "FAIL");
    count = 0;
    root = remove_door(check_remove_1, root);
    for (struct node *p = root; p != NULL; p = p->next) {
        count += 1;
    }
    printf("%s\n", count == 2 ? "SUCCESS" : "FAIL");
    destroy(root);
    return 0;
}
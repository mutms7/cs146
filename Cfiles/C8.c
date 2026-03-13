#include <stdio.h>

struct Node {

    int data;

    struct Node *next;

};

struct Node *reverse(struct Node *lst) {
    struct Node *previous = NULL;
    struct Node *current = lst;
    struct Node *next = NULL;
    while (current) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    return previous;
}
//i omitted the definitions for Node, theHeap, size_t, and get and release functions as the question suggests these are already provided

// a
char *findMemHelp(size_t n, struct Node *lst);

char *findMemory(size_t n) {
    return findMemHelp(n, theHeap);
}

// error handling unnecessary
char *findMemHelp(size_t n, struct Node *lst) {
    if (lst->size > n) {
        lst->size = lst->size - n;
        lst->mem = lst->mem + n;
        return lst->mem-n;
    } else if (lst->size == n) {
        char *m = lst->mem;
        struct Node *temp = lst->next;
        if (temp != NULL) {
            lst->size = temp->size;
            lst->mem = temp->mem;
            lst->next = temp->next;
            releaseNode(temp);
        }
        return m;
    } else {
        return findMemHelp(n, lst->next);
    }
}

//b
void replaceMemory(char *p, size_t n) {
    struct Node *o = getNode();
    o->size = n;
    o->mem = p;
    if (p < theHeap->mem) {
        o->next = theHeap;
        theHeap = o;
    } else {
        struct Node *current = theHeap;
        while (current->next != NULL && p > current->next->mem) {
            current = current->next;
        }
        o->next = current->next;
        current->next = o;
    }
}

//c
void coalesce() {
    struct Node *current = theHeap;
    while (current->next != NULL) {
        if (current->mem + current->size == current->next->mem) {
            struct Node *temp = current->next;
            current->size += temp->size;
            current->next = temp->next;
            releaseNode(temp);
        } else {
            current = current->next;
        }
    } 
}
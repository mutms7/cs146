#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int bigit;
    struct Node *next;
};
void print_num(struct Node *nlst);

struct Node *add(struct Node *n1lst, struct Node *n2lst);

struct Node *mult(struct Node *n1lst, struct Node *n2lst);

struct Node *cons_bigit(int bgt, struct Node *nxt);

void free_num(struct Node *blst);

struct Node *copy_num(struct Node *nlst);

// takes a blist and returns a reversed copy of it
// reverse(cons_bigit(0, cons_bigit(12, NULL)) makes cons_bigit(12, cons_bigit(0, NULL)) makes the bigit representing 123456
struct Node *reverse(struct Node *lst)
{
    struct Node *ans = NULL;
    struct Node *loop = lst;
    while (loop)
    {
        ans = cons_bigit(loop->bigit, ans);
        loop = loop->next;
    }
    free_num(lst);
    return ans;
}

// should make a new node with the bigit bgt and next pointing to nxt

// cons_bigit(12, NULL) makes the bigit representing 12
// cons_bigit(3456, cons_bigit(12, NULL)) makes the bigit representing 123456
// cons_bigit(0, cons_bigit(0, NULL)) makes NULL, which represents 0
struct Node *cons_bigit(int bgt, struct Node *nxt)
{
    struct Node *node = malloc(sizeof *node);
    node->bigit = bgt;
    node->next = nxt;
    return node;
}

// frees all memory used by blst in the heap
// must protect the next pointer by assigning the address to a variable on the stack before freeing

// free(cons_bigit(12, NULL)) frees the memory used by the cons_bigit
void free_num(struct Node *blst)
{
    while (blst)
    {
        struct Node *nxt = blst->next;
        free(blst);
        blst = nxt;
    }
}

// makes a copy of the blist without modifying the original blist

// struct Node *a = cons_bigit(10, NULL);
// struct Node *b = copy_num(a);
// b = cons_bigit(10, b);
// should make two blists a and b, a = 10, b = 100010

struct Node *copy_num(struct Node *nlst)
{
    struct Node *copy = NULL;
    while (nlst)
    {
        copy = cons_bigit(nlst->bigit, copy);
        nlst = nlst->next;
    }
    struct Node *ret = reverse(copy);
    
    return ret;
}

// takes a blist, prints its value
// specifically,
// print_num(cons_bigit(7890, cons_bigit(56, cons_bigit(12, NULL)))) prints 1200567890 (12,0056,7890)
// print_num(cons_bigit(NULL)) prints 0
void print_num_h(struct Node *nlst)
{
    if (nlst->next == NULL && nlst != NULL)
    {
        printf("%d", nlst->bigit);
    }
    else if (nlst)
    {
        print_num_h(nlst->next);
        printf("%04d", nlst->bigit);
    }
}

// print_num handles edgecases, then calls the recursive helper function
void print_num(struct Node *nlst)
{
    if (nlst)
    {
        print_num_h(nlst);
    }
    else
    {
        printf("%d", 0);
    }
}

// takes a blist, returns a blist with removed all trailing zeroes before the highest bigit place
// nozero(cons_bigit(800, cons_bigit(0, cons_bigit(0, NULL)))) returns cons_bigit(800, NULL)
// nozero must be called before reverse, print, add, mult

struct Node *nozero(struct Node *blst)
{
    struct Node *ans = reverse(blst);
    while (ans && ans->bigit == 0)
    {
        struct Node *temp = ans;
        ans = ans->next;
        free(temp);
    }
    struct Node *ret = reverse(ans);
    return ret;
}

// takes two blists, adds their values to a new blist
// add(cons_bigit(9998, NULL), cons_bigit(9999, NULL)) returns cons_bigit(9997, cons_bigit (1, NULL))
struct Node *add(struct Node *n1lst, struct Node *n2lst)
{
    struct Node *result = NULL;

    int carry = 0;
    while (n1lst && n2lst)
    { // both have values, so sum and cons value
        int sum = n1lst->bigit + n2lst->bigit + carry;
        carry = sum / 10000;
        result = cons_bigit(sum % 10000, result);
        n1lst = n1lst->next;
        n2lst = n2lst->next;
    }
    while (n1lst)
    { // one has value, so sum
        int sum = n1lst->bigit + carry;
        carry = sum / 10000;
        result = cons_bigit(sum % 10000, result);
        n1lst = n1lst->next;
    }
    while (n2lst)
    { // other has value, so sum
        int sum = n2lst->bigit + carry;
        carry = sum / 10000;
        result = cons_bigit(sum % 10000, result);
        n2lst = n2lst->next;
    }
    result = cons_bigit(carry, result);
    
    struct Node *tmp = reverse(result);
    struct Node *ret = nozero(tmp);
    return ret;

}

// takes two blists, and multiplies their values into a new blist
// iterate over all bigits in n1, mult with
// use add to add all mult results
// add each element of blist (ex. 4235 * blist)
struct Node *mult(struct Node *n1lst, struct Node *n2lst)
{
    struct Node *ans = NULL;
    struct Node *i = NULL;
    while (n1lst)
    {
        struct Node *mul = copy_num(i);
        int carry = 0;
        struct Node *n2 = n2lst;
        while (n2)
        {
            int prod = n1lst->bigit * n2->bigit + carry;
            carry = prod / 10000;
            mul = cons_bigit(prod % 10000, mul);
            n2 = n2->next;
        }
        mul = cons_bigit(carry, mul);

        struct Node *tmp = reverse(mul);
        struct Node *ret = add(ans, tmp);
        free_num(tmp);
        free_num(ans);
        ans = ret;
        i = cons_bigit(0, i);
        n1lst = n1lst->next;
    }
    free_num(i);
    return ans;
}

/*
int main()
{

    // PRINT TESTS
    print_num(cons_bigit(1000, cons_bigit(1, NULL)));
    printf(" = 1,1000\n");

    print_num(cons_bigit(10, cons_bigit(10, NULL)));
    printf(" = 10,0010\n");

    // ADD TESTS (assumes add(a,b) returns a NEW list)
    struct Node *a;
    struct Node *b;
    struct Node *r;

    // 1) 9999 + 1 = 1,0000
    a = cons_bigit(9999, NULL);
    b = cons_bigit(1, NULL);
    printf("9999 + 1 = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 1,0000)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 2) 12,3456 + 7 = 12,3463
    a = cons_bigit(3456, cons_bigit(12, NULL));
    b = cons_bigit(7, NULL);
    printf("12,3456 + 7 = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 12,3463)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 3) 2,9999,9999 + 1 = 3,0000,0000 (carry chain)
    a = cons_bigit(9999, cons_bigit(9999, cons_bigit(2, NULL)));
    b = cons_bigit(1, NULL);
    printf("2,9999,9999 + 1 = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 3,0000,0000)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 4) 1,5000 + 2,6000 = 4,1000
    a = cons_bigit(5000, cons_bigit(1, NULL));
    b = cons_bigit(6000, cons_bigit(2, NULL));
    printf("1,5000 + 2,6000 = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 4,1000)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // PRINT tests (leading zeros are at end of chain)
    print_num(cons_bigit(12, cons_bigit(0, NULL)));
    printf(" = 12\n"); // NOT 0,0012

    print_num(cons_bigit(12, cons_bigit(0, cons_bigit(0, NULL))));
    printf(" = 12\n"); // multiple leading zero chunks hidden

    print_num(cons_bigit(5, cons_bigit(0, cons_bigit(12, NULL))));
    printf(" = 12,0000,0005\n"); // middle zero is NOT leading -> should show

    print_num(cons_bigit(0, NULL));
    printf(" = 0\n");

    print_num(cons_bigit(0, cons_bigit(0, cons_bigit(0, NULL))));
    printf(" = 0\n"); // all zeros prints as single 0

    // (0,0012) + (0,0003) should print as 12 + 3 = 15
    a = cons_bigit(12, cons_bigit(0, NULL)); // leading zero chunk
    b = cons_bigit(3, cons_bigit(0, NULL));  // leading zero chunk
    print_num(a);
    printf(" + ");
    print_num(b);
    printf(" = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 15)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 9999 + 1 = 1,0000
    a = cons_bigit(9999, NULL);
    b = cons_bigit(1, NULL);
    print_num(a);
    printf(" + ");
    print_num(b);
    printf(" = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 1,0000)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 12,3456 + 7 = 12,3463
    a = cons_bigit(3456, cons_bigit(12, NULL));
    b = cons_bigit(7, NULL);
    print_num(a);
    printf(" + ");
    print_num(b);
    printf(" = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 12,3463)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 12,0000,0005 + 0,0000,9995 = 12,0001,0000
    a = cons_bigit(5, cons_bigit(0, cons_bigit(12, NULL)));
    b = cons_bigit(9995, cons_bigit(0, cons_bigit(0, NULL))); // leading zero at end
    print_num(a);
    printf(" + ");
    print_num(b);
    printf(" = ");
    r = add(a, b);
    print_num(r);
    printf(" (expected 12,0001,0000)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 1) 0 * 0 = 0
    a = cons_bigit(0, NULL);
    b = cons_bigit(0, NULL);
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 0)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 2) 0 * 1234 = 0   (with leading zeros on 1234 representation)
    a = cons_bigit(0, NULL);
    b = cons_bigit(1234, cons_bigit(0, cons_bigit(0, NULL))); // should print "1234"
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 0)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 3) 1 * 12,3456 = 12,3456
    a = cons_bigit(1, NULL);
    b = cons_bigit(3456, cons_bigit(12, NULL));
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 12,3456)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 4) 2 * 9999 = 1,9998  (since 2*9999 = 19998)
    a = cons_bigit(2, NULL);
    b = cons_bigit(9999, NULL);
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 1,9998)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 5) 9999 * 9999 = 9,9980,0001  (since 9999^2 = 99,980,001)
    a = cons_bigit(9999, NULL);
    b = cons_bigit(9999, NULL);
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 9,9980,0001)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 6) 10,0010 * 10 = 100,0100  (10,0010 means 10*10000 + 10 = 100010)
    a = cons_bigit(10, cons_bigit(10, NULL)); // prints 10,0010
    b = cons_bigit(10, NULL);                 // prints 10
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 100,0100)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 7) 12,0000,0005 * 2 = 24,0000,0010  (tests internal zeros)
    a = cons_bigit(5, cons_bigit(0, cons_bigit(12, NULL))); // 12,0000,0005
    b = cons_bigit(2, NULL);
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 24,0000,0010)\n");
    free_num(a);
    free_num(b);
    free_num(r);

    // 8) (leading zeros in inputs)  (0,0000,0012) * (0,0003) = 36
    a = cons_bigit(12, cons_bigit(0, cons_bigit(0, NULL))); // prints 12
    b = cons_bigit(3, cons_bigit(0, NULL));                 // prints 3
    print_num(a);
    printf(" * ");
    print_num(b);
    printf(" = ");
    r = mult(a, b);
    print_num(r);
    printf(" (expected 36)\n");
    free_num(a);
    free_num(b);
    free_num(r);
}
*/

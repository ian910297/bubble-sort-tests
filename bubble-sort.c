#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {
    int val;
    struct __node *next;
} Node;

void print_list(Node *HEAD);
void normal_data(Node **HEAD);
void short_data1(Node **HEAD);
void short_data2(Node **HEAD);
void sort(Node **HEAD);

int main(int argc, char *argv[])
{
    int input;
    if(argc >= 2) {
        input = atoi(argv[1]);
    } else {
        input = 0;
    }
    Node *HEAD = NULL;

    // input data type
    switch(input) {
    case 0:
        // 2 455 7 8 9 1
        normal_data(&HEAD);
        break;
    case 1:
        // NULL
        break;
    case 2:
        // 1
        short_data1(&HEAD);
        break;
    case 3:
        // 10 1
        short_data2(&HEAD);
        break;
    }

    printf("Origin:\n");
    print_list(HEAD);
    sort(&HEAD);
    printf("Sort:\n");
    print_list(HEAD);

    free(HEAD);

    return 0;
}

void normal_data(Node **HEAD)
{
    int i;
    int data[6] = {1, 9, 8, 7, 455, 2};
    Node *new;

    for(i=0; i<6; i++) {
        new = malloc(sizeof(Node));
        new->val = data[i];
        new->next = *HEAD;
        *HEAD = new;
    }
}

void short_data1(Node **HEAD)
{
    Node *new;

    new = malloc(sizeof(Node));
    new->val = 1;
    new->next = *HEAD;
    *HEAD = new;
}

void short_data2(Node **HEAD)
{
    Node *new;

    new = malloc(sizeof(Node));
    new->val = 1;
    new->next = *HEAD;
    *HEAD = new;

    new = malloc(sizeof(Node));
    new->val = 10;
    new->next = *HEAD;
    *HEAD = new;
}

void sort(Node **HEAD)
{
    Node *cur;
    Node *tmp;
    Node *prev;
    Node *TAIL = NULL;

    while(*HEAD!=NULL) {
        cur = *HEAD;
        while(cur->next!=TAIL) {
            if(cur->val > cur->next->val) {
                if(cur == *HEAD) {
                    *HEAD = cur->next;
                } else {
                    prev->next = cur->next;
                }

                // swap
                tmp = cur->next;
                cur->next = tmp->next;
                tmp->next = cur;

                // next
                prev = tmp;
                if(cur->next == TAIL) {
                    TAIL = cur;
                    break;
                }
            } else {
                if(cur->next->next == TAIL) {
                    TAIL = cur->next;
                    break;
                }

                prev = cur;
                cur = cur->next;
            }
        }

        if((*HEAD)->next == TAIL) {
            break;
        }
    }
}

void print_list(Node *HEAD)
{
    if(HEAD == NULL) {
        return;
    }

    Node *TAIL = NULL;

    while(HEAD->next!=TAIL) {
        printf("%d ", HEAD->val);
        HEAD = HEAD->next;
    }
    printf("%d\n", HEAD->val);
}


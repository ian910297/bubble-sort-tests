#ifndef UTILS_C
#define UTILS_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

// Basic Linked List Node Definition
typedef struct __node {
    int val;
    struct __node* next;
} Node;

void link(Node** head, int from, int to);

// Utils for generating testing data
void newNode(int val, Node **HEAD);

void freeList(Node* head, int ll_len);

void createLinkedList(Node **HEAD, int* nums, int nums_len, int loop_at);

int* createNums(int nums_len);

bool validate(int* nums, int nums_len, Node* head, int ll_len);

// Utils for displaying
void showList(Node* head, int len);

void link(Node** head, int from, int to)
{
    Node* f_node = NULL;
    Node* t_node = NULL;
    Node* cur = *head;

    int i = 0, term = MAX(from, to) + 1;
    for(; i < term && cur != NULL; ++ i) {
        if (i == from) f_node = cur;
        if (i == to) t_node = cur;

        cur = cur->next;
    }

    if (i == term)
        f_node->next = t_node;
}

// Gen
void newNode(int val, Node **HEAD)
{
    Node* fac = (Node*) malloc(sizeof(Node));
    fac->val = val;
    fac->next = *HEAD;

    *HEAD = fac;
}

void freeList(Node* head, int ll_len)
{
    if (head == NULL) return;

    Node* cur = head;
    Node* prev = NULL;

    do {
        free(prev);
        prev = cur;
        cur = cur->next;
    } while (cur != NULL && -- ll_len);
}

void createLinkedList(Node **HEAD, int* nums, int nums_len, int loop_at)
{
    *HEAD = NULL;

    int num_ptr = nums_len;
    while (num_ptr --) {
        newNode(nums[num_ptr], &*HEAD);
    }

    if (loop_at >= 0 && loop_at < nums_len)
        link(&*HEAD, nums_len - 1, loop_at);
}

int* createNums(int nums_len)
{
    srand(time(NULL));

    int* nums = (int*) malloc(sizeof(int) * nums_len);
    for (int i = 0; i < nums_len; ++ i) {
        nums[i] = rand() & 0x0000007f;
    }

    return nums;
}

bool validate(int* nums, int nums_len, Node* head, int ll_len)
{
    if (nums_len != ll_len) return false;

    Node* cur = head;
    int i = 0;
    while(i < nums_len && cur != NULL) {
        if (nums[i] != cur->val) {
            return false;
        } else {
            ++ i;
            cur = cur->next;
        }
    }

    return true;
}

// Display
void showList(Node* head, int len)
{
    Node* nptr = head;


    while (len && nptr != NULL) {
        printf("%d ", nptr->val);
        nptr = nptr->next;
        len--;
    }
    printf("\n");

    if (len != 0)
        printf("[Error]List Len Count Fail!! %d\n", len);
}
#endif

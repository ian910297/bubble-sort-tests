#ifndef BUBBLE_SORT_C
#define BUBBLE_SORT_C
#include <stdlib.h>
#include <stdbool.h>

#include "Utils.c"

Node* move(Node *cur);
bool cycle_finding(Node *HEAD, Node **TAIL, int *length, int *mu, int *lambda);
void sort(Node **HEAD);

Node* move(Node *cur)
{
    if(cur!=NULL) {
        return cur->next;
    } else {
        return NULL;
    }
}

bool cycle_finding(Node *HEAD, Node **TAIL, int *length, int *mu, int *lambda)
{
    // lambda is length
    // mu is the meet node's index
    Node *tortoise = HEAD;
    Node *hare = HEAD;

    // get meet point
    tortoise = move(tortoise);
    hare = move(move(hare));
    while(hare!=NULL && tortoise!=hare) {
        tortoise = move(tortoise);
        hare = move(move(hare));
    }

    // not loop
    if(hare==NULL) {
        *TAIL = NULL;
        *length = 0;
        tortoise = HEAD;
        while(tortoise!=NULL && (tortoise=move(tortoise))) {
            (*length)++;
        }
        return false;
    }

    // get mu
    *mu = 0;
    tortoise = HEAD;
    while(tortoise!=hare) {
        (*mu)++;
        tortoise = tortoise->next;
        hare = hare->next;
    }

    // get lambda
    *lambda = 1;
    tortoise = move(tortoise);
    *TAIL = tortoise;
    while(tortoise!=hare) {
        *TAIL = tortoise;
        (*lambda)++;
        tortoise = move(tortoise);
    }
    *length = *mu + *lambda;

    return true;
}

void sort(Node **HEAD)
{
    Node *cur;
    //Node *tmp;
    Node *prev;
    Node *TAIL;
    int i;
    int j;
    int length = 0;
    int mu = -1;
    int lambda = -1;
    bool has_cycle = cycle_finding(*HEAD, &TAIL, &length, &mu, &lambda);

    if(has_cycle) {
        printf("Cycle\n");
        printf("mu = %d, lambda = %d\n", mu, lambda);
    } else {
        printf("Single\n");
        printf("mu = %d, lambda = %d\n", mu, lambda);
    }
    for(i=0; i<length-1; i++) {
        cur = *HEAD;
        prev = *HEAD;

        for(j=0; j<length-i-1; j++) {
            if(cur->val > cur->next->val) {
                if(cur->next==TAIL) {// for cycle
                    if(mu==0) {// link to HEAD
                        prev->next = cur->next;
                        cur->next = *HEAD;
                    } else if(cur->next==cur->next->next) {// link to self
                        prev->next = cur->next;
                        cur->next = cur;
                    } else {
                        prev->next = cur->next;
                        cur->next = prev->next->next;
                    }

                    prev->next->next = cur;
                    TAIL = cur;
                    prev = prev->next;
                } else if(cur==*HEAD) {
                    *HEAD = cur->next;

                    if(mu==1) {
                        cur->next = (*HEAD)->next;
                        (*HEAD)->next = cur;
                        TAIL->next = cur;
                    } else {
                        cur->next = (*HEAD)->next;
                        (*HEAD)->next = cur;
                    }

                    prev = *HEAD;
                } else {
                    prev->next = cur->next;
                    cur->next = prev->next->next;
                    prev->next->next = cur;

                    if(j+1==mu) {
                        TAIL->next = cur;
                    } else if(j==mu) {
                        TAIL->next = prev->next;
                    }

                    prev = prev->next;
                }
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
    }
}
#endif

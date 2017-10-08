#include <stdio.h>
#include <stdlib.h>

#include "Utils.c"
#include "Bubble-sort.c"

int cmp(const void *a, const void *b)
{
    return *(int*)a > *(int*)b;
}

int main(int argc, char *argv[])
{
    int len = 6;
    int *nums;
    Node *HEAD;

    int i;
    for(i=-1; i<6; i++) {
        printf("------------------------\n");
        nums = createNums(len);
        createLinkedList(&HEAD, nums, len, i);

        showList(HEAD, len);
        sort(&HEAD);
        showList(HEAD, len);

        free(nums);
        freeList(HEAD, len);
        printf("------------------------\n");
    }

    return 0;
}

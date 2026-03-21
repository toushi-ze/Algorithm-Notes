#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* getKth(struct ListNode* curr, int k) {
    while (curr != NULL && k > 0) {
        curr = curr->next;
        k--;
    }
    return curr;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (NULL == head || 1 == k) {
        return head;
    }

    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;

    struct ListNode* groupPrev = dummy;

    while (1) {
        struct ListNode* Kth = getKth(groupPrev, k);
        if (NULL == Kth) {
            break;
        }

        struct ListNode* groupNext = Kth->next;

        struct ListNode* prev = groupNext;
        struct ListNode* curr = groupPrev->next;
        struct ListNode* tmp = NULL;

        for (int i = 0; i < k; i++) {
            tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }

        struct ListNode* nextGroupPrev = groupPrev->next;
        groupPrev->next = Kth; 
        groupPrev = nextGroupPrev;
    }

    struct ListNode* newList = dummy->next;
    free(dummy);
    return newList;
}
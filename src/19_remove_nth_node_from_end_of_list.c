#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    // 创建哨兵节点，处理头节点
    struct ListNode* dummy = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummy->next = head;
    
    // 快慢指针
    struct ListNode* fast = dummy;
    struct ListNode* slow = dummy;

    // 快指针先走 n + 1 步要让 slow 停在倒数第 n 个节点的前一个
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // 快慢指针同步移动，直到 fast 指向 NULL
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    // slow->next 要删除的节点
    struct ListNode* target = slow->next;
    slow->next = slow->next->next; 
    
    // 释放内存
    free(target);

    // 返回新的头节点
    struct ListNode* newHead = dummy->next;
    free(dummy);
    return newHead;
}
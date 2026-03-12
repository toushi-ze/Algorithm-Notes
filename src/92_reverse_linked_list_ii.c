#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    // pre指向反转区域的前一个结点
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* pre = &dummy;

    // 将 pre 移动到待反转区域的前一个节点
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }
    // cur指向待反转区域的第一个节点
    // next指向 cur 后面那个将被提到前面的节点
    struct ListNode* cur = pre->next;
    struct ListNode* next;

    // 执行 right - left 次操作
    for (int i = 0; i < right - left; i++) {
        next = cur->next;           // 抓住 cur 后面的那个节点
        cur->next = next->next;     // cur 跨过 next，指向 next 的后面
        next->next = pre->next;     // 插队，连pre
        pre->next = next;           // pre 接住next
    }

    return dummy.next;
}
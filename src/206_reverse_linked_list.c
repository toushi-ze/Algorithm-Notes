#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* reverseList(struct ListNode* head) {
    // pre 指向 NULL,cur 指向当前的头
    struct ListNode* pre = NULL;
    struct ListNode* cur = head;
    
    // 没到链表末尾，就反转
    while (cur != NULL) {
        // 链表相关操作一定记得保存后继
        struct ListNode* nextTemp = cur->next;
        
        // 把当前箭头的指向反转
        cur->next = pre;
        
        // pre 往前走
        pre = cur;
        
        // cur 往前走一步，去处理原链表的下一个
        cur = nextTemp;
    }
    
    // 循环结束cur 已经是 NULL，而 pre 成为了新链表的头，所以返回的是pre
    return pre;
}
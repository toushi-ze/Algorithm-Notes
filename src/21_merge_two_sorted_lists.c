#include<stdio.h>
#include<stdlib.h>

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    struct ListNode* cur = &dummy;
    dummy.next = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val)
        {
            cur->next = list1;
            list1 = list1->next;
        }else {
            cur->next = list2;
            list2 = list2->next;
        }
        cur = cur->next;
    }

    /* 下面这一段第一次提交时我的赋值运算符和关系运算符使用错误，
    导致测试案例:Input[1,2,4][1,3,4] MyOutput [1,1,2,3,4](缺少一个4)Expected Answer[1,1,2,3,4,4] 
    收获：可以把常量写在左边：
    if (NULL == list1) { ... } or if (list1) { ... }
    如果漏写了一个 =，变成 if (NULL = list1)，编译器会直接报错，因为不能给常量赋值
    */
   if (list1)
    {
        cur->next = list1;
    }else {
        cur->next = list2;
    }
    return dummy.next;
}
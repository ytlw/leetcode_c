#ifndef __LISTNODE__
#define __LISTNODE__

struct ListNode {
    int val;
    struct ListNode* next;
};

struct ListNode* newListNode(int val, struct ListNode* next) {
    struct ListNode* ans = (struct ListNode*)malloc(sizeof(struct ListNode));
    ans->val = val;
    ans->next = next;
    return ans;
}

void freeListNode(struct ListNode* head) {
    while (head != NULL) {
        struct ListNode* next = head->next;
        free(head);
        head = next;
    }
}

void printListNode(struct ListNode* head) {
    int first = 1;
    while (head != NULL) {
        if (first) {
            first = 0;
        } else {
            printf(", ");
        }
        printf("%d", head->val);
        head = head->next;
    }
    printf("\n");
}

#endif //__LISTNODE__
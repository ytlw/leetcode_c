#include "listnode.h"
#include <read_from_file/read_input.h>



void generateListNode(struct ListNode* head, stream* ps, int* pos) {
    if (head == NULL || !read(ps)) {
        return;
    }

    int v = 0;
    int sign = 1;
    char* ch = ps->buf;
    struct ListNode* cur = head;
    int i = 0;
    for (; ch[i] != '}' && ch[i] != '\0'; i++) {
        if (ch[i] == '{' || ch[i] == ' ') {
            continue;
        }

        if (ch[i] == ',') {
            struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
            tmp->val = v * sign;
            tmp->next = NULL;
            v = 0;
            sign = 1;
            if (head == NULL) {
                head = tmp;
            } else {
                cur->next = tmp;
                cur = tmp;
            }
            continue;
        }

        if (ch[i] == '-') {
            sign = -1;
            continue;
        }

        v = v * 10 + ch[i] - '0';
    }

    if (pos != NULL) {
        *pos = i + 1;
    }
}

struct ListNode* newListNode2(char ch[], stream* ps, int* pos) {

    int v = 0;
    int sign = 1;
    struct ListNode* head = NULL;
    struct ListNode* cur = head;
    int i = 0;
    for (; ch[i] != '}' && ch[i] != '\0'; i++) {
        if (ch[i] == '{' || ch[i] == ' ') {
            continue;
        }

        if (ch[i] == ',') {
            struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
            tmp->val = v * sign;
            tmp->next = NULL;
            v = 0;
            sign = 1;
            if (head == NULL) {
                head = tmp;
            } else {
                cur->next = tmp;
                cur = tmp;
            }
            continue;
        }

        if (ch[i] == '-') {
            sign = -1;
            continue;
        }

        v = v * 10 + ch[i] - '0';
    }

    if (pos != NULL) {
        *pos = i + 1;
    }

    return head;
}

struct ListNode* newListNode(char ch[], int* pos) {
    int v = 0;
    int sign = 1;
    struct ListNode* head = NULL;
    struct ListNode* cur = head;
    int i = *pos;
    for (; ch[i] != '}' && ch[i] != '\0'; i++) {
        if (ch[i] == '{' || ch[i] == ' ') {
            continue;
        }

        if (ch[i] == ',') {
            struct ListNode* tmp = (struct ListNode*)malloc(sizeof(struct ListNode));
            tmp->val = v * sign;
            tmp->next = NULL;
            v = 0;
            sign = 1;
            if (head == NULL) {
                head = tmp;
            } else {
                cur->next = tmp;
                cur = tmp;
            }
            continue;
        }

        if (ch[i] == '-') {
            sign = -1;
            continue;
        }

        v = v * 10 + ch[i] - '0';
    }

    if (pos != NULL) {
        *pos = i + 1;
    }

    return head;
}

struct ListNode** newListNodeArray(char ch[]) {
    int n = strlen(ch);
    struct ListNode** ans = NULL;
    int pos = 0;
    int i = 0;
    int ansIdx = 0;
    int capacity = 4;
    while (ch[i] != ']' && ch[i] != '\0') {
        if (ch[i] == ',' || ch[i] == '[') {
            ++i;
            continue;
        }

        if (ch[i] == '{') {
            struct ListNode* head = newListNode(ch, &pos);
            i = pos;
            if (ans == NULL) {
                ans = malloc(sizeof(struct ListNode*) * capacity);
                ans[ansIdx] = head;
                ++ansIdx;
            } else {
                if (ansIdx < capacity) {
                    ans[ansIdx] = head;
                    ++ansIdx;
                } else {
                    if (capacity < 1024) {
                        capacity <<= 1;
                    } else {
                        capacity = capacity + (capacity >> 1);
                    }

                    struct ListNode** ans2 = malloc(sizeof(struct ListNode*) * capacity);
                    ans2[ansIdx] = head;
                    ++ansIdx;

                    for (int j = ansIdx - 2; j >= 0; --j) {
                        ans2[j] = ans[j];
                    }
                    struct ListNode** tmp = ans;
                    ans = ans2;
                    for (int j = ansIdx - 2; j >= 0; --j) {
                        free(tmp[j]);
                    }
                    free(tmp);
                }
            }
        }

    }
    return ans;
}

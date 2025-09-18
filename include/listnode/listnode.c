#include "listnode.h"
#include <read_from_file/read_input.h>

struct ClosureListNode {
    void (*func) (stream* ps);
    struct ListNode* head;
};

struct ListNode* generateListNode(stream* ps) {
    struct ListNode* ans = NULL, * cur = NULL;

    int v = 0;
    int sign = 1;
    int status = read(ps);
    if (status == END) {
        return NULL;
    }

    do {
        char* ch = ps->buf;

        int i = 0;
        for (; ch[i] != '\0'; i++) {
            if (ch[i] == '{' || ch[i] == '[' || ch[i] == ' ') {
                continue;
            }

            if (ch[i] == ',' || ch[i] == '}' || ch[i] == ']') {
                struct ListNode* tmp = newListNode(v * sign, NULL);
                v = 0;
                sign = 1;
                if (ans == NULL) {
                    ans = tmp;
                    cur = ans;
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

    } while (status == NOT_FULL_LINE);

    return ans;
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
            // 暂不可用
            struct ListNode* head = newListNode(0, NULL);
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

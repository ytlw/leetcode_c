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

    do {
        // 获取链表数组时，ps->buf 会被反复读取，要断点续传。
        if (ps->i == 0) {
            read(ps);
            if (ps->status == END) {
                return NULL;
            }
        } else {
            ps->i++;
        }

        char* ch = ps->buf;

        // 出现下列情况表示当前链表结束
        // ]]
        // ],
        // 遍历完字符串
        for (; ch[ps->i] != '\0' && (ps->i == 0 || (ch[ps->i - 1] != ']' && ch[ps->i - 1] != '}') || (ch[ps->i] != ',' && ch[ps->i] != ch[ps->i - 1])); ps->i++) {
            if (ch[ps->i] == '{' || ch[ps->i] == '[' || ch[ps->i] == ' ') {
                continue;
            }

            if (ch[ps->i] == ',' || ch[ps->i] == '}' || ch[ps->i] == ']') {
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

            if (ch[ps->i] == '-') {
                sign = -1;
                continue;
            }

            v = v * 10 + ch[ps->i] - '0';
        }

        // 置零，重新读取 ps
        if (ch[ps->i] == '\0') {
            ps->i = 0;
        } else {
            break;
        }
    } while (ps->status == NOT_FULL_LINE);

    return ans;
}

struct ListNode** generateListNodeArray(stream* ps, int* size) {
    struct ListNode** ans = malloc(sizeof(struct ListNode*) * 128);
    int capacity = 128;
    int i = 0;
    struct ListNode* node = NULL;
    while ((node = generateListNode(ps)) != NULL) {
        if (i == capacity) {
            capacity <<= 1;
            struct ListNode** ans2 = malloc(sizeof(struct ListNode*) * capacity);
            for (int j = 0; j < i; j++) {
                ans2[j] = ans[j];
            }
            free(ans);
            ans = ans2;
        }
        ans[i] = node;
        i++;
    }

    *size = i;
    for (; i < capacity; i++) {
        ans[i] = NULL;
    }
    return ans;
}

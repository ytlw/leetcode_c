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

        // 出现下列情况表示当前链表结束
        // ]]
        // ],
        // 遍历完字符串
        for (; ch[i] != '\0' && (i == 0 || (ch[i - 1] != ']' && ch[i - 1] != '}') || (ch[i] != ',' && ch[i] != ch[i - 1])); i++) {
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

struct ListNode** generateListNodeArray(stream* ps) {
    struct ListNode** ans = NULL;
    int status = read(ps);
    if (status == END) {
        return NULL;
    }

    do {

    } while (status == NOT_FULL_LINE);

    return ans;
}

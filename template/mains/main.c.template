#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <listnode/listnode.c>
#include <read_from_file/read_input.h>
#include <uthash/uthash.h>


struct ListNode* merge2Lists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    struct ListNode* head = NULL;
    if (list1->val < list2->val) {
        head = list1;
        list1 = list1->next;
    } else {
        head = list2;
        list2 = list2->next;
    }

    struct ListNode* tmp = head;

    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            tmp->next = list1;
            tmp = list1;
            list1 = list1->next;
        } else {
            tmp->next = list2;
            tmp = list2;
            list2 = list2->next;
        }
    }

    if (list1 != NULL) {
        tmp->next = list1;
    }
    if (list2 != NULL) {
        tmp->next = list2;
    }

    return head;
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsLen) {
    struct ListNode* ans = (struct ListNode*)malloc(sizeof(struct ListNode));

    int len = listsLen;
    int pos = 0;
    while (len > 1) {
        for (int i = 0; i < len; i += 2) {
            if (i == len - 1) {
                lists[pos] = lists[i];
            } else {
                lists[pos] = merge2Lists(lists[i], lists[i + 1]);;
            }

            pos++;
        }

        len = pos;
        pos = 0;
    }

    return ans;
}
struct hash_entry {
    int id;
    char name[10];
    UT_hash_handle hh;
};

struct hash_entry* users = NULL;

void add_user(struct hash_entry* s) {
    HASH_ADD_INT(users, id, s);
}

struct hash_entry* find_user(int user_id) {
    struct hash_entry* s;
    HASH_FIND_INT(users, &user_id, s);
    return s;
}

void delete_user(struct hash_entry* user) {
    HASH_DEL(users, user);
}

int main(void) {
    stream _stream;
    stream* ps = &_stream;
    initStream(ps);

    while (read(ps)) {

    }

    closeStream(ps);



    return 0;
}

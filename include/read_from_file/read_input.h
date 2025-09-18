#ifndef __READ_INPUT__
#define __READ_INPUT__
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define LINE_SIZE BUFSIZ

typedef struct {
    FILE* f;
    char buf[LINE_SIZE + 1];
    int i;
    int status;
}stream;

#define UNREAD -1
#define END 0
#define FULL_LINE 1
#define NOT_FULL_LINE 2

int initStream(stream* s) {
#ifdef INPUT_FILE
    s->f = fopen(INPUT_FILE, "r");
#else
    s->f = fopen("in.txt", "r");
#endif
    if (s->f == NULL) {
        printf("open in.txt failed, errno: %d\n", strerror(errno));
        return 1;
    }

    s->i = 0;
    s->status = UNREAD;

    return 0;
}

void read(stream* s) {
    if (fgets(s->buf, LINE_SIZE + 1, s->f) == NULL) {
        s->buf[0] = '\0';
        s->status = END; // 读取完毕
        return;
    }

    int n = strlen(s->buf);
    if (s->buf[n - 1] == '\n') {
        s->buf[n - 1] = '\0';
        // 读取到换行符
        s->status = FULL_LINE;
        return;
    }

    if (n == LINE_SIZE) {
        s->status = NOT_FULL_LINE; // 缓存占满了
        return;
    }
    s->status = FULL_LINE;// 最后一行没有 \n 的情况
}

void closeStream(stream* s) {
    if (fclose(s->f) == EOF) {
        perror("fclose failed");
        // 检查errno获取具体错误
        if (errno == EBADF) {
            printf("err: bad file description\n");
        } else if (errno == ENOSPC) {
            printf("err: no space\n");
        }
    }
}

#endif // __READ_INPUT__
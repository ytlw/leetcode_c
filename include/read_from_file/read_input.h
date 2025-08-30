#ifndef __READ_INPUT__
#define __READ_INPUT__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iconv.h>

typedef struct {
    FILE* f;
    char buf[BUFSIZ];
}stream;

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

    return 0;
}

int read(stream* s) {
    char* ans = fgets(s->buf, BUFSIZ, s->f);
    if (ans == NULL) {
        return 0;
    }

    return 1;
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
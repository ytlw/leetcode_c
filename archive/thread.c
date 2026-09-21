#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 线程函数参数结构
typedef struct {
    int id;
    int delay;
} ThreadArgs;

// 线程函数
void* worker(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    printf("Thread %d starting, will sleep %d seconds\n",
        args->id, args->delay);

    sleep(args->delay);

    // 返回值
    int* result = malloc(sizeof(int));
    *result = args->id * 100;

    printf("Thread %d finishing\n", args->id);
    return (void*)result;
}

int main() {
    pthread_t threads[3];
    ThreadArgs args[3];
    void* results[3];

    // 创建3个线程
    for (int i = 0; i < 3; i++) {
        args[i].id = i + 1;
        args[i].delay = i + 1;  // 1, 2, 3秒

        if (pthread_create(&threads[i], NULL, worker, &args[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // 等待所有线程结束
    for (int i = 0; i < 3; i++) {
        if (pthread_join(threads[i], &results[i]) != 0) {
            perror("Failed to join thread");
            return 1;
        }

        int* value = (int*)results[i];
        printf("Thread %d returned: %d\n", i + 1, *value);
        free(value);
    }

    printf("All threads completed\n");
    return 0;
}
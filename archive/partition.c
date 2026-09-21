#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randN(int n) {
    srand((unsigned)time(NULL));

    int a = rand() % n;
    return a;
}

void swap(int* x, int* y) {
    int t = *x;
    *x = *y;
    *y = t;
}


int partition(int* nums, int left, int right) {
    int pi = left + randN(right - left + 1);
    swap(&nums[left], &nums[pi]);

    int i = left + 1, j = right;
    while (1) {
        for (; i <= j && nums[i] < nums[left]; i++) {}
        for (; i <= j && nums[j] > nums[left]; j--) {}
        if (i >= j) {
            break;
        }

        swap(&nums[i], &nums[j]);
        i++;
        j--;
    }

    swap(&nums[j], &nums[left]);

    return j;
}

void quickSortNoPartition(int* nums, int left, int right) {
    if (right <= left) {
        return;
    }

    int cmp = nums[left + randN(right - left + 1)];
    int i = left, j = right;
    while (i <= j) {
        for (; i <= j && nums[i] < cmp; i++) {}
        for (; i <= j && nums[j] > cmp; j--) {}
        if (i <= j) {
            swap(&nums[i], &nums[j]);
            i++;
            j--;
        }
    }

    quickSortNoPartition(nums, left, j);
    quickSortNoPartition(nums, i, right);
}

void quickSort(int* nums, int left, int right) {
    if (right <= left) {
        return;
    }
    int pi = partition(nums, left, right);
    quickSort(nums, left, pi - 1);
    quickSort(nums, pi + 1, right);
}

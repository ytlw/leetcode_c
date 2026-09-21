_Bool less(int x, int y) {
    return x < y;
}

_Bool bigger(int x, int y) {
    return x > y;
}

void swap(int* x, int* y) {
    int t = *x;
    *x = *y;
    *y = t;
}

_Bool down(int arr[], int arrSize, int i0, _Bool cmp(int, int)) {
    int i = i0;
    while (1) {
        int j = 2 * i + 1;
        if (j >= arrSize || j < 0) {
            break;
        }

        int j2 = j + 1;
        if (j2 < arrSize&& cmp(arr[j2], arr[j])) {
            j = j2;
        }

        if (!cmp(arr[j2], arr[i])) {
            break;
        }

        swap(&arr[j2], &arr[i]);
        i = j;
    }
    return i > i0;
}

void up(int arr[], int j, _Bool cmp(int, int)) {
    while (1) {
        int i = (j - 1) / 2;
        if (i == j || !cmp(arr[j], arr[i])) {
            break;
        }

        swap(&arr[i], &arr[j]);
        j = i;
    }
}

void initHeap(int arr[], int arrSize, _Bool cmp(int, int)) {
    for (int i = (arrSize - 2) >> 1; i >= 0; i--) {
        down(arr, arrSize, i, cmp);
    }
}

void fix(int arr[], int arrSize, int i, _Bool cmp(int, int)) {
    if (!down(arr, arrSize, i, cmp)) {
        up(arr, i, cmp);
    }
}
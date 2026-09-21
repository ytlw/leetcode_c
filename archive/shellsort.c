
void insert(int* nums, int right, int step) {
    int cur = nums[right];
    int j = right;
    for (; j >= step; j -= step) {
        if (nums[j - step] > cur) {
            nums[j] = nums[j - step];
        } else {
            break;
        }
    }
    nums[j] = cur;
}

int* sortArray(int* nums, int numsSize) {
    int step = 1;
    while (step < numsSize) {
        step = (step << 1) + 1;
    }

    while (1) {
        step >>= 1;
        if (step < 1) {
            break;
        }

        for (int j = step; j < numsSize; j++) {
            insert(nums, j, step);
        }
    }

    return nums;
}
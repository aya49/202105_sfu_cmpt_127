int identical(int arr1[], int arr2[], unsigned int len) {
    // if the length of both arrays is 0, return 1; sucess!
    if (len == 0) {
        return 1;
    }

    // for each integer in the array, if they are not the same, return 0; fail!
    for (unsigned int i=0; i<len; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }

    // if all integers are the same, return 1; success!
    return 1;
}

int scrambled(unsigned int arr1[], unsigned int arr2[], unsigned int len) {
    // if the length of both arrays is 0, return 1; sucess!
    if (len == 0) {
        return 1;
    }

    // arr: array where its index represents the values in the two arrays; elements initialized to 0
    // we make arr length 100 since we can assume the values of arr1 and arr2 are between 0 and 100
    int arr[101] = {0};
    for (unsigned int i=0; i<len; i++) {
        // you can create more than 1 variable with the same data type on one line!
        int tmp1 = 0, tmp2 = 0;

        // can you figure out what this does? try drawing it out!
        tmp1 = arr1[i];
        tmp2 = arr2[i];
        arr[tmp1]++;
        arr[tmp2]--;
    }
    for (int i=0; i<100; i++) {
        // do you know what it means if an element in arr is not 0?
        // hint: arr[tmp1]++; arr[tmp2]--;
        if (arr[i] != 0) {
            return 0;
        }
    }
    return 1;
}
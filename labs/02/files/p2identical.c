int identical(int arr1[], int arr2[], unsigned int len) {
    if (len == 0) {
        return 1;
    }
    for (int i=0; i<len; i++) {
        if (arr1[i] != arr2[i]) {
            return 0;
        }
    }
    return 1;
}

int scrambled(int arr1[], int arr2[], unsigned int len) {
    // FILL IN BODY
    return 0;
}
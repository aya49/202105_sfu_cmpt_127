int mirror(int arr1[], int arr2[], unsigned int len) {
    if (len > 0) {
        for (unsigned int i=0; i<len; i++) {
            if (arr1[i] != arr2[(len - 1) - i]) {
                return 0;
            }
        }
    }
    return 1;
}
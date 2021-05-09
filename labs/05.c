/* Lab 05; practice 04 */

// Sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_sort(intarr_t* ia) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }

    int len = ia->len;
    for (int i = 0; i < len; i++) {
            int tmp = 0;
        for (int j = 0; j < len-i; j++) {
            if ((*ia).data[j] > (*ia).data[j+1]) {
                tmp = (*ia).data[j];
                (*ia).data[j] = (*ia).data[j+1];
                (*ia).data[j+1] = tmp;
            }
        }
    }
    return INTARR_OK;
}

/* Lab 05; practice 07 */

// HINT: Do this practice before doing practice 06.
// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. 
// If newlen is greater than the original array length, the values 
// of the new integers will be undefined 
// (see https://en.cppreference.com/w/c/memory/realloc). 
// If the allocation is successful, return INTARR_OK, otherwise 
// return INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_resize(intarr_t* ia, unsigned int newlen) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }
    int i,original_len;
    //printf("%d",ia->len);
    original_len = ia->len;
    if (newlen >= 0) {
        int *new_resize_data = realloc(ia->data,sizeof(int)*newlen);
        ia->len = newlen;
        ia->data = new_resize_data;
        if (new_resize_data) {
            //printf("before3\n");
            if (newlen>original_len) {
                for (i = original_len;i < newlen;i++) {
                    ia->data[i] = 0;
                }
            }
        }        
        return INTARR_OK;
    }
    return INTARR_BADALLOC;
}


/* Lab 05; practice 06 */

// HINT: First, do practice 07, since you will need to resize your array
//       by +1 in order to successfully push val.
// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push(intarr_t* ia, int val) {
    if (ia==NULL) {
        return INTARR_BADARRAY;
    }
    int tmp_len = ia->len+1;
    ia->len = tmp_len;

    int *new_data = realloc(ia->data, sizeof(int)*ia->len);
    if (new_data) {
        new_data[tmp_len-1] = val;
        ia->data = new_data;
        return INTARR_OK;
    } else {
        return INTARR_BADALLOC;
    }
}

// HINT: You will need to decrement len so that it always represents
//       the number of int's stored in the array data.
// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop(intarr_t* ia, int* i) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }
    
    if (ia->data[0] == 0 && ia->len == 0) {
        return INTARR_BADINDEX;
    }
    if (i!=NULL) {
        *i = ia->data[ia->len-1];
        ia->data[ia->len-1] = 0;
        ia->len = ia->len-1;
        return INTARR_OK;
    }
    return INTARR_BADINDEX;
}
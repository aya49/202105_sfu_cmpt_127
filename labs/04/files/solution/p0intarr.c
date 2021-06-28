#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "p0intarr.h"

// PUT INLINE COMMENTS BELOW as you read the code!
// that will help you understand what is happening :)

/* practice 01 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create(unsigned int len) {
    unsigned int empty = 0;
    assert (len >= empty);
    intarr_t* ptr = malloc(sizeof(intarr_t));
    if (ptr != NULL) {
        ptr->data = malloc(len*sizeof(int));
        if (ptr->data != NULL) {
            ptr->len = len;
            return ptr;
        }
    } 
    return NULL;
}

// Frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy(intarr_t* ia) {
    if (ia != NULL) {
        free(ia->data);
        free(ia);
    }
}


/* practice 02 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set(intarr_t* ia, unsigned int index, int val) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }
    unsigned int len = ia->len;
    unsigned int empty = 0;
    if (index >= empty && index < len) {
        ia->data[index] = val;
        return INTARR_OK;
    }
    return INTARR_BADINDEX;
}

// If index is valid and val is non-null, set *val to ia->data[index] and return
// INTARR_OK. Otherwise do not modify *val and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get(const intarr_t* ia, unsigned int index, int* val) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }

    unsigned int len = ia->len;
    unsigned int empty = 0;
    if (index >= empty && index < len && val != NULL) {
        *val = ia->data[index];
        return INTARR_OK;
    }
    return INTARR_BADINDEX; 
}


/* practice 03 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy(const intarr_t* ia) {
    if (ia != NULL) {
        int len = ia->len;
        intarr_t* copy = malloc(sizeof(intarr_t));
        if (copy != NULL) {
            copy->data = malloc(len*sizeof(int));
            if (copy->data != NULL) {
                copy->len = len;
                memcpy(copy->data, ia->data, sizeof(int) * len);
                return copy;
            }
        }
    }
    return NULL;
}


/* practice 04 */

// Find the first occurrence of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find(intarr_t* ia, int target, int* i) {
    if (ia == NULL) {
        return INTARR_BADARRAY;
    }
    unsigned int empty = 0;
    int index = 0;
    for (unsigned int j = 0; j < ia->len; j++) {
        if (ia->data[j] == target) {
            *i = j;
            return INTARR_OK;
        }
    }
    return INTARR_NOTFOUND;
}


/* practice 05 */

// Get a deep copy of a portion of ia from index 'first' to index 'last'
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specified section. If an error
// occurs, i.e. ia is null, 'first' or 'last' are out of bounds, 
// 'last' < 'first', or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray(intarr_t* ia, unsigned int first, unsigned int last) {
    if (ia == NULL || first > ia->len || last > ia->len || last < first) {
        return NULL;
    }
    intarr_t *duplicate_subarray = malloc(sizeof(intarr_t));
    if (duplicate_subarray == NULL) {
        return NULL;
    }
    if (first <= last && duplicate_subarray != NULL ) {
        int i,k = 0,newlen = last-first+1;
        duplicate_subarray->len = newlen;
        duplicate_subarray->data = malloc(sizeof(int)*newlen);
        for (i = first; i <= last; i++) {
            duplicate_subarray->data[k] = ia->data[i];
            k++;
        }
        return duplicate_subarray;
    }
    return NULL;    
}
#include <assert.h>
#include "p2.h"

// PUT INLINE COMMENTS BELOW as you read the code!
// that will help you understand what is happening :)

int point_array_init(point_array_t* pa) { 
    if (pa == NULL)
        return 1;

    pa->len = 0;
    pa->reserved = 0;
    pa->points = malloc(sizeof(point_t));
    if (pa->points == NULL)
        return 1;
    
    return 0;
}

void point_array_reset(point_array_t* pa) {
    assert(pa != NULL);
    point_array_init(pa);
    free(pa->points);
}

int point_array_append(point_array_t* pa, point_t* p) {
    if (pa == NULL || p == NULL) {
        return 1;
    }
    if (pa->reserved == 0) {
        pa->points = realloc(pa->points, sizeof(point_t)*(pa->len+1));
        if (pa->points == NULL)
            return 1;
        pa->reserved++;
    }
    if (pa->len >= pa->reserved) {
        pa->points = realloc(pa->points, sizeof(point_t)*(pa->reserved*2));
        if (pa->points == NULL)
            return 1;
        pa->reserved = pa->reserved*2;
    }
    
    pa->points[pa->len] = *p;
    pa->len++;
    return 0;
}

int point_array_remove(point_array_t* pa, unsigned int i) {
    if (i >= pa->len)
        return 1;
    
    pa->points[i] = pa->points[pa->len-1];
    pa->len--;

    pa->points = realloc(pa->points, sizeof(point_t)*pa->len);
    if (pa->points == NULL)
        return 1;
    
    return 0;
}
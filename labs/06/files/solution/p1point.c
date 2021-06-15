#include <assert.h>
#include "p1.h"

// PUT INLINE COMMENTS BELOW as you read the code!
// that will help you understand what is happening :)

int point_array_init(point_array_t* pa) { 
    if (pa == NULL)
        return 1;
    
    pa->len = 0;
    pa->points = malloc(sizeof(point_t));
    if (pa->points == NULL)
        return 1;
    
    return 0;
}

void point_array_reset(point_array_t* pa) {
    assert(pa != NULL); // shows and error if condition is true
    point_array_init(pa);
    free(pa->points);
}

int point_array_append(point_array_t* pa, point_t* p) {
    if (pa == NULL || p == NULL)
        return 1;

    pa->points = realloc(pa->points, sizeof(point_t)*(pa->len+1));
    if (pa->points == NULL) {
        return 1;
    }
    
    pa->points[pa->len] = *p;
    pa->len++;
    return 0;
}

int point_array_remove(point_array_t* pa, unsigned int i) {
    if (i >= pa->len)
        return 1;
    
    pa->points[i] = pa->points[pa->len-1]; // does this work in replacement of the following? :)
    // pa->points[i].x = pa->points[pa->len-1].x;
    // pa->points[i].y = pa->points[pa->len-1].y;
    // pa->points[i].z = pa->points[pa->len-1].z;
    pa->len--;

    pa->points = realloc(pa->points,sizeof(point_t)*pa->len);
    if (pa->points == NULL)
        return 1;
    
    return 0;
}
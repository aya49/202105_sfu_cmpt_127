#include <stdio.h>
#include <stdlib.h>
#include "p1list.h"

// PUT INLINE COMMENTS BELOW as you read the code!
// that will help you understand what is happening :)
//
// the example solutions given below are minimal.
// try to improve on them! e.g. check if the given argument is a null pointer

list_t* list_create(void) {
    list_t * list = malloc(sizeof(list_t));

    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

void list_destroy(list_t* list) {
    element_t* curr = list->head;
    element_t* next;
    while (curr != NULL) {
        next = curr->next;
        
        free(curr);
        curr = next;
    }
    free(list);    
}

element_t* element_create(int i) {
    element_t* e = malloc(sizeof(element_t));

    if (e != NULL) {
        e->val = i;
        e->next = NULL;
    }
    return e;
}

int list_append(list_t* list, int i) {
    element_t* e = element_create(i);

    if (e == NULL)
        return 1;

    if (list->head == NULL) {
        list->head = e;
    } else {
        list->tail->next = e;
    }
    list->tail = e;
    return 0;
}

int list_prepend(list_t* list, int i) {
    element_t* e = element_create(i);

    if (e == NULL)
        return 1;

    if (list->head == NULL) {
        list->tail = e;
    } else {
        e->next = list->head;
    }
    list->head = e;
    return 0;
}

element_t* list_index(list_t* list, unsigned int i) {
    element_t* curr = list->head;
    unsigned int i_curr = 0;
    while (curr != NULL) {
        if (i_curr == i)
            return curr;
        i_curr++;
        curr = curr->next;
    }
    return NULL;
}

void list_print(list_t* list) {
    printf("{");
    for (element_t* e = list->head; e != NULL; e = e->next) {
        printf(" %d", e->val);
    }
    printf(" }\n");
}
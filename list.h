#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <assert.h>

typedef int elem_t;

enum list {
        FREE_ELEM = -1
};

enum errors {
        // NULL_LIST_PTR  =  0xBADDADA,
        NULL_NEXT_PTR  = -2,
        NULL_PREV_PTR  = -3,
        NO_SIZE        = -4,
        INSERT_FAIL    = 0xBADFEL,
        RESIZE_ERR     = -5,
        NULL_CALLOC    = -6
};

struct data_t {
        elem_t data = 0;
        size_t next = 0;
        size_t prev = 0;
};

struct list_t {
        data_t *data   = {};
        data_t *free = nullptr;
        size_t capacity = 0;
        size_t size     = 0;
};

int list_ctor (list_t *list, int capacity);
int list_insert (list_t *list, elem_t val, size_t position);
elem_t list_delete (list_t *list, size_t position);
int list_dtor (list_t *list);
int list_resize (list_t *list, size_t coeff);
int list_linearize (list_t *list);

#endif /*LIST_H*/

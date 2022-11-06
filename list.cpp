 #include "list.h"

int list_ctor (list_t *list, int capacity)
{
        list->capacity = capacity;
        list->data = (data_t *)calloc(list->capacity, sizeof(data_t));
        if (!list->data)
                return NULL_DATA_PTR;

        list->free = list->data + 1;
        list->size = 0;
        fill_free(list, 1);

        return 0;
}

static size_t fill_free (list_t *list, size_t position)
{
        assert(list);

        size_t i = 0;
        for (i = position; i < list->capacity - 1; i++) {
                list->data[i].data = FREE_ELEM;
                list->data[i].next = i + 1;
                list->data[i].prev = i - 1;
        }

        list->data[i].data = FREE_ELEM;
        list->data[i].next = 0;
        list->data[i].prev = list->capacity - 2;

        return i - 1;
}

int list_insert (list_t *list, elem_t val, size_t position)
{
        assert(list);

        data_t *data = list->data;
        data_t *free = list->free;
        size_t new_free = free->next;

        if (list->size >= list->capacity)
                if (list_resize(list, 1.2))
                        return RESIZE_ERR;

        *free = {
                .data = val,
                .next = data[position].next,
                .prev = position,
        };

        data[position].next = free - data;
        data[free->next].prev = free - data;
        list->free = data + new_free;
        list->free->prev = free - data;
        list->size++;

        return 0;
}

int list_resize (list_t *list, double coeff)
{
        assert(list);

        list_t *temp_list = list;
        temp_list = (list_t*) realloc(list, list->capacity * coeff);
        if (temp_list == nullptr)
                return RESIZE_ERR;
        list = temp_list;

        return 0;
}

elem_t list_delete (list_t *list, size_t position)
{
        assert(list && "Null list");

        data_t *data = list->data;
        data_t *free = list->free;
        elem_t deleted = 0;
        if (position < list->capacity) {
                deleted = data[position].data;
                data[position].data = FREE_ELEM;
                data[data[position].next].prev = data[position].prev;
                data[data[position].prev].next = data[position].next;
                data[position].next = free - data;
                data[position].prev = free->prev;
                free->prev = position;
                list->free = data + position;

                return deleted;
        }

        return 0;
}

int list_dtor (list_t *list)
{
        if (list != nullptr) {
                free(list->data);
                return 0;
        }

        return NULL_DATA_PTR;
}

int list_linearize (list_t *list)
{
        data_t *new_data_ptr = (data_t *) calloc(list->capacity, sizeof(data_t));
        if (new_data_ptr == nullptr)
                return NULL_CALLOC;
        size_t i = 1;
        // new_data_ptr->next = 1;
        size_t next_elem = list->data[0].next;
        for (; i < list->size + 1; i++) {
                // printf("%d\n", list->data[list->data[i - 1].next].data);
                new_data_ptr[i].data = list->data[next_elem].data;
                next_elem = list->data[next_elem].next;
                new_data_ptr[i].prev = i - 1;
                new_data_ptr[i - 1].next = i;
        }
        new_data_ptr[i].data = list->data[next_elem].data;
        new_data_ptr[i].next = 0;
        new_data_ptr->prev = i - 1;
        free(list->data);
        list->data = new_data_ptr;
        fill_free(list, i);

        return 0;
}

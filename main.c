#include <stdio.h>
#include <stdlib.h>

typedef struct dll_node {
    struct dll_node *pfwd;
    struct dll_node *pbck;
    int size;  // size of allocation in KBs
} dll_node;

typedef struct dll {
    struct dll_node *head;
    struct dll_node *tail;
    int available_memory;  // total size of memory available in KBs
} dll;

// enqueue (new) to (list)
// is_freelist ? addMem : subMem
void add_to_tail(dll *list, dll_node *new, int is_freelist) {
    // add code here
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->pfwd = new;
        new->pbck = list->tail->pbck;  // tail->pbck = NULL

        list->tail = new;

        // list->tail = new;
    }

    switch (is_freelist) {
        case 0: {
            list->available_memory -= new->size + 8;
            break;
        };
        case 1: {
            list->available_memory += new->size;
            break;
        };
    }
}

// dequeue (node) from list
dll_node *remove_from_head(dll *const list) {
    // add code here

    dll_node *removeHead = list->head;

    list->head = list->head->pfwd;
    list->available_memory += removeHead->size + 8;

    removeHead->pfwd = removeHead->pbck = NULL;

    return removeHead;
}

dll_node *get_new_node(int size) {
    if (size == 0) {
        return NULL;
    }

    dll_node *new = malloc(sizeof(dll_node));

    new->pfwd = new->pbck = NULL;
    new->size = size;

    return new;
}

void print_list(const dll *list) {
    dll_node *n = list->head;

    while (n != NULL) {
        printf("( %d ),", n->size);
        n = n->pfwd;
    }
}

int main() {
    struct dll list, freelist;
    int available = 0;
    int num_allocs = 0;
    int num_deallocs = 0;

    list.head = NULL;
    list.tail = NULL;
    freelist.head = NULL;
    freelist.tail = NULL;
    freelist.available_memory = 0;  // freelist is empty

    // first line is available memory given in bytes
    scanf("%d", &available);
    list.available_memory = available - 8;

    // second line is the number of allocations
    scanf("%d", &num_allocs);

    for (int i = 0; i < num_allocs; ++i) {
        int alloc = 0;
        scanf("%d", &alloc);
        add_to_tail(&list, get_new_node(alloc), 0);
    }

    // // following line is the number of deallocations
    scanf("%d", &num_deallocs);
    for (int i = 0; i < num_deallocs; ++i) {
        add_to_tail(&freelist, remove_from_head(&list), 1);
    }

    puts("Allocator:");
    print_list(&list);
    printf("\nAvailable mem: %d\n", list.available_memory);

    puts("Freelist:");
    print_list(&freelist);
    printf("\nAvailable mem (freelist): %d\n", freelist.available_memory);
    return 0;
}
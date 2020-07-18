#include "refcount.h"
#include "int_element.h"
#include "stdlib.h"

/* TODO: Implement all public int_element functions, including element interface functions.
Static constructor that creates new integer elements. */

struct int_element {
    struct int_element_class *class;
    int i;
};


struct int_element_class {
    void (*print)(struct int_element *);

    int (*compare)(struct element *, struct element *);

    int (*get_value)(struct int_element *);

    int (*is_element)(struct element *);
};

void int_print(struct int_element *e) {
    printf("%d", e->i);
}

int int_compare(struct element *e1, struct element *e2) {
    if(!is_int_element(e1)&&is_int_element(e2)){
        return 1;
    } else if(is_int_element(e1)&&!is_int_element(e2)){
        return -1;
    } else {
        int e1i = int_element_get_value(e1);
        int e2i = int_element_get_value(e2);
        if(e1i > e2i){
            return 1;
        } else if(e1i < e2i){
            return -1;
        } else {
            return 0;
        }
    }
}

struct int_element_class int_element_class = {int_print, int_compare, int_element_get_value, is_int_element};

int int_element_get_value(struct int_element *e) {
    return e->i ;
}

int is_int_element(struct element * e) {
    return e->class == (struct element_class *) &int_element_class;
}


struct int_element *int_element_new(int value) {
    struct int_element *obj = rc_malloc(sizeof(struct int_element), NULL);
    obj->class = &int_element_class;
    obj->i = value;
    return obj;
}



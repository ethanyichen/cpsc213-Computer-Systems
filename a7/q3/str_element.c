#include "refcount.h"
#include "str_element.h"

/* TODO: Implement all public str_element functions, including element interface functions.

You may add your own private functions here too. */

struct str_element {
    struct str_element_class *class;
    char* s;
};

void str_finalizer(struct str_element *e){
    free(e->s);
};

struct str_element_class {
    void (*print)(struct str_element *);

    int (*compare)(struct element *, struct element *);

    char* (*get_value)(struct str_element *);

    int (*is_element)(struct element *);
};

void str_print(struct str_element *e) {
    while(*e->s) {
        putchar(*e->s);
        e->s++;
    }
}

int str_compare(struct element *e1, struct element *e2) {
    if(!is_str_element(e1)&&is_str_element(e2)){
        return -1;
    } else if(is_str_element(e1)&&!is_str_element(e2)){
        return 1;
    } else {
        char* e1s = str_element_get_value(e1);
        char* e2s = str_element_get_value(e2);
        return strcmp(e1s,e2s);
    }
}

struct str_element_class str_element_class = {str_print, str_compare, str_element_get_value, is_str_element};

char* str_element_get_value(struct str_element *e) {
    return e->s;
}

int is_str_element(struct element * e) {
    return e->class == (struct element_class *) &str_element_class;
}


struct str_element *str_element_new(char* value) {
    struct str_element *obj = rc_malloc(sizeof(struct str_element),str_finalizer);
    obj->class = &str_element_class;
    obj->s = malloc(strlen(value) + 1);
    return obj;
}

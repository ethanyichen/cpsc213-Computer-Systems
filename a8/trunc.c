#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"



void negativeToNull (element_t* r, element_t s, element_t i) {
    char **ret = (char**) r;
    char *str = s;
    int  *n  = i;
    if(*n<0){
        *ret = str;
    } else {
        *ret = 0;
    }
}
void print(element_t t) {
    char *str = t;
    if (str != 0) {
        printf("%s\n", str);
    } else {
        printf("%s\n", "NULL");
    }
}

int elimNegative(element_t i) {
    int* n = i;
    return *n >= 0;
}

void truncate(element_t *r, element_t s, element_t i) {
    char **ret = (char**) r;
    char *str = s;
    int *n = i;
    *ret = strdup(str);
    if (strlen(*ret) > *n) {
        (*ret)[*n] = 0;
    }
}

void concat(element_t *r, element_t s, element_t i) {
    char **ret = (char**) r;
    char *str2 = i;
    *ret = realloc(*ret, strlen(*ret) + strlen(str2) + 2);
    if (strlen(*ret))
        strcat(*ret, " ");
    strcat(*ret, str2);
}

void maxInt(element_t *r, element_t s, element_t i) {
    int** ret = (int**)r;
    int* n = s;
    int* n1 = i;
    if(*n < *n1){
        **ret =  *n1;
    } else{
        **ret = *n;
    }
}

void parse_string(char *str, struct list* nl, struct list* sl) {
    char *endp;
    /* strtol returns a pointer to the first non-numeric character in endp.
       If it gets to the end of the string, that character will be the null terminator. */
    long int value = strtol(str, &endp, 10);
    if (str[0] != '\0' && endp[0] == '\0') {
        /* String was non-empty and strtol conversion succeeded - integer */
        int *n = malloc(sizeof(int*));
        *n = value;
        //printf("%x\n", *n);
        list_append(nl, (element_t)n);
    } else {
        list_append(sl, (element_t)endp);
        //printf("%x\n", endp);
    }
}

int main(int argc, char **argv) {
    struct list *nums = list_create();
    struct list *strings = list_create();
    for (int i = 0; i < argc - 1; i++) {
        parse_string(argv[i + 1],nums,strings);
    }

    struct list *l0 = list_create();
    list_filter(elimNegative, l0, nums);
    struct list *l1 = list_create();
    list_map2(truncate, l1, strings, l0);
    list_foreach(print, l1);

    char * concatResult = malloc(sizeof(char));
    *concatResult = 0;
    list_foldl(concat,(element_t*)&concatResult,l1);
    printf("%s\n",concatResult);
    free(concatResult);
    concatResult = 0;

    int maxResult = 0;
    int* n = &maxResult;
    list_foldl(maxInt, (element_t*)&n,l0);
    // list_foreach(free,nums);
    printf("%d\n", maxResult);

    list_foreach(free,l0);
        list_foreach(free,l1);
    // list_foreach(free,strings);
    list_destroy(l0);
    list_destroy(l1);
    list_destroy(nums);
    list_destroy(strings);

}

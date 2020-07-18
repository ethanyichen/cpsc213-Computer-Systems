#include <stdio.h>
#include <stdlib.h>

#include "element.h"
#include "int_element.h"
#include "str_element.h"

/* If the string is numeric, return an int_element. Otherwise return a str_element. */
struct element *parse_string(char *str) {
  char *endp;
  /* strtol returns a pointer to the first non-numeric character in endp.
     If it gets to the end of the string, that character will be the null terminator. */
  int value = strtol(str, &endp, 10);
  if(str[0] != '\0' && endp[0] == '\0') {
    /* String was non-empty and strtol conversion succeeded - integer */
    return (struct element *)int_element_new(value);
  } else {
    return (struct element *)str_element_new(str);
  }
}

struct element_class table;
int compare(void * e1, void * e2){
    struct element* a = *(struct element**)e1;
    struct element* b = *(struct element**)e2;
    return a->class->compare(a,b);
}

int main(int argc, char **argv) {
  /* TODO: Read elements into a new array using parse_string */
  /* TODO: Sort elements with qsort */
  struct element * elementPtrs[argc - 1];
      for(int i = 0; i< argc - 1; i++){
          elementPtrs[i] = parse_string(argv[i+1]);
      }
    qsort(elementPtrs,argc - 1, sizeof(struct element), compare);

    printf("Sorted: ");
    for(int i = 0; i< argc - 1; i++){
        elementPtrs[i]->class->print(elementPtrs[i]);
        printf(" ");
        rc_free_ref(elementPtrs[i]);
    }
    printf("\n");
}

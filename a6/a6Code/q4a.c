#include <stdio.h>

int arr[10];
int *p = arr;

void ping (int a, int b) {
    p[b] = p[b] + a;
}

void foo () {
    int c = 1;
    int d = 2;
    ping (3,4);
    ping (c,d);
}

void main() {
    foo();
    for (int i = 0; i < 10; i++) {
        printf("%d\n", p[i]);
    }
}



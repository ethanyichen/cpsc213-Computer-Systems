#include <stdio.h>

int x[8] = {1, 2, 3, -1, -2, 0, 184, 340057058};
int y[8];

int f(int a0) {
    int bit_count = 0;
    while (a0) {
        if (a0 < 0) {
            bit_count++;
        }
        a0 = a0 << 1;
    }
    return bit_count;
}

void main() {
    for (int i = 7; i >= 0; i--) {
        y[i] = f(x[i]);
    }
    for (int i = 0; i < 8; i++) {
        printf("%d\n", x[i]);
    }
    for (int i = 0; i < 8; i++) {
        printf("%d\n", y[i]);
    }
}


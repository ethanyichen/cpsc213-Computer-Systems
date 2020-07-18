#include <stdio.h>

int q2(int x, int y, int z) {
    int ret = 0;
    void *jt[9] = {&&L0, &&DEFAULT, &&L2, &&DEFAULT, &&L4, &&DEFAULT, &&L6, &&DEFAULT, &&L8};
    if (x < 10 || x > 18) {
        goto DEFAULT;
    }
    goto *jt[x-10];

    L0:
    ret = y + z;
    goto CONT;
    L2:
    ret = y - z;
    goto CONT;
    L4:
    ret = (y>z);
    goto CONT;
    L6:
    ret = (y<z);
    goto CONT;
    L8:
    ret = (y==z);
    goto CONT;
    DEFAULT:
    ret = 0;
    goto CONT;

    CONT:
    return ret;
}
int main(int argc, char **argv) {
    int a = 10;
    int b = 12;
    int c = 11;
    int d = q2(a,b,c);
    printf("%d\n",d);
}


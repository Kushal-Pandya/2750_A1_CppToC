#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


void getPair(int* a, int* d) {
    // Check that these are not pointing to NULL
    assert(a);
    assert(d);
    *a = 1;

    int c = *d;

    c = c + 5;
    *d = c;

    printf("%d\n", c);
}

int main() {
    int a, b;
    b = 4;
    getPair(&a, &b);

    printf("%d %d\n", a, b);

    return 0;
}
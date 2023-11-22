#include <stdio.h>
#include <stdlib.h>
//#include <malloc/_malloc.h>
//#include <__clang_hip_math.h>
//#include <printf.h>

void g() {
    int *a1 = malloc(1000 * sizeof (int));
    int *a2 = malloc(10 * sizeof (int));
}

int main() {


    int b1[1000];
    int b2[100];

    // true //在 stack 里是 true，heap 里是false
    printf("%d", *(int *)((uint64_t)&b2 - sizeof (int)) == b1[999]);

    int *a[100];
    int *b[100];

    for (int i = 0; i < 100; i++) {
        a[i] = malloc(100);
        b[i] = malloc(100);
    }

    for (int i = 0; i < 50; i++) {
        free(a[i*2]);
        free(b[i]);
    }

    return 1;
}
#include <stdlib.h>
#include <stdio.h>

void f(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}
void g(int **c, int n) {
    *c = malloc(sizeof(int) * n);
}
void h(int *h) {
    *h = 100;
}
int main() {
    int a = 1, b = 2, c = 3;
    int **d;
    d = malloc(sizeof(int*));
    f(&a, &b);
    g(d, 1);
    h(*d);
    printf("%d, %d, %d", a, c, d[0][0]);
    free(*d);
    free(d);
    return 0;
}

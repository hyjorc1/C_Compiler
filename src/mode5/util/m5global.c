#include "m5global.h"

void printInt(void *n) { 
    printf("%d", *(int *)n); 
}

int *new_int(int num) {
    int *p = (int *)malloc(sizeof(int));
    *p = num;
    return p;
}

void m5preprocess() {
    m4preprocess();

}

void m5process(char *argv[], int i) {
    m4process(argv, i);

}

void m5postprocess() {
    m4postprocess();
    
}
#include <stdio.h>

void increment_by_value(int num) {
    num++;
}

void increment_by_reference(int *num) {
    (*num)++;
}

int main() {
    int a = 5, b = 5;
    int *ptr =&b;
    
    increment_by_value(a);       
    increment_by_reference(ptr);  

    printf("a: %d, b: %d\n", a, b);
    return 0;
}


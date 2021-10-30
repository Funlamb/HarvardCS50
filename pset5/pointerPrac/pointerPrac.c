#include <stdio.h>
#include <stdlib.h>

void swap(int a, int b);
void swapWithPointers(int *a, int *b);

int main(int argc, char *argv[]){
    if (argc != 3)
    {
        printf("usage: pointerPrac, INT a, INT b\n");
        return 1;
    }
    char x = *argv[1];
    char y = *argv[2];
    int a = x - '0';
    int b = y - '0';
    printf("Pointer to a: %x\n", &a);
    printf("Pointer to b: %x\n", &b);
    printf("Before   A: %d B: %D\n", a, b);
    // swap(a, b);
    // printf("After A: %d B: %d\n", a, b);
    swapWithPointers(&a, &b);
    printf("Pointers A: %d B: %d\n", a, b);
    printf("Pointer to a: %x\n", &a);
    printf("Pointer to b: %x\n", &b);
    return 0;
}

void swap(int a, int b){
    printf("a: %i\n", a);
    printf("b: %i\n", b);
    int temp = a;
    a = b;
    b = temp;
    printf("After swap\n");
    printf("a: %i\n", a);
    printf("b: %i\n", b);
}

void swapWithPointers(int *a, int *b){
    int temp = *a;//value in temp is a
    *a = *b;//value in a is now b
    *b = temp;//value in b is now temp
}
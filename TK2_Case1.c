#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi struktur stack
struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

// Fungsi untuk membuat stack dengan kapasitas yang diberikan
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Fungsi untuk memeriksa apakah stack penuh
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Fungsi untuk memeriksa apakah stack kosong
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Fungsi untuk menambahkan elemen ke stack
void push(struct Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Fungsi untuk menghapus elemen dari stack
char pop(struct Stack* stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

// Fungsi untuk membalik string menggunakan stack
void reverseString(char str[]) {
    int n = strlen(str);

    // Membuat stack dengan kapasitas yang sama dengan panjang string
    struct Stack* stack = createStack(n);

    // Push semua karakter dari string ke dalam stack
    for (int i = 0; i < n; i++)
        push(stack, str[i]);

    // Pop semua karakter dari stack dan menempatkannya kembali ke string
    for (int i = 0; i < n; i++)
        str[i] = pop(stack);
}

// Fungsi utama
int main() {
    char str[] = "Hello, World!";
    printf("String asli: %s\n", str);

    reverseString(str);
    printf("String reverse: %s\n", str);

    return 0;
}

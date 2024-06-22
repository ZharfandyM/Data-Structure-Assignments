#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisi stack
#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isFull(Stack *s) {
    return s->top == MAX - 1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char item) {
    if (isFull(s)) {
        printf("Stack overflow\n");
    } else {
        s->items[++(s->top)] = item;
    }
}

char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return '\0';
    } else {
        return s->items[(s->top)--];
    }
}

void reverseString(char str[]) {
    Stack s;
    initStack(&s);
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        push(&s, str[i]);
    }

    for (int i = 0; i < length; i++) {
        str[i] = pop(&s);
    }
}

void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Reverse a string\n");
    printf("2. Exit\n");
}

int main() {
    char input[100];
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice (1 or 2): ");
        if (scanf("%d", &choice) != 1) {
            printf("Error: Invalid input. Please enter 1 or 2.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter a string to reverse: ");
                getchar(); // Consume the newline character left by scanf
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
                if (strlen(input) == 0) {
                    printf("Error: Input string cannot be empty.\n");
                } else {
                    reverseString(input);
                    printf("Reversed string: %s\n", input);
                }
                break;
            case 2:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Error: Invalid choice. Please enter 1 or 2.\n");
        }
    }

    return 0;
}

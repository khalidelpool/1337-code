#include <stdlib.h>
#include <stdio.h>

// Simulate a swap on stack A
void sa(int *stack, int size) {
    if (size > 1) {
        int temp = stack[0];
        stack[0] = stack[1];
        stack[1] = temp;
    }
}

// Simulate a rotation on stack A
void ra(int *stack, int size) {
    if (size > 1) {
        int temp = stack[0];
        for (int i = 0; i < size - 1; i++) {
            stack[i] = stack[i + 1];
        }
        stack[size - 1] = temp;
    }
}

// Simulate a reverse rotation on stack A
void rra(int *stack, int size) {
    if (size > 1) {
        int temp = stack[size - 1];
        for (int i = size - 1; i > 0; i--) {
            stack[i] = stack[i - 1];
        }
        stack[0] = temp;
    }
}

// Check how close the stack is to being sorted
int is_sorted(int *stack, int size) {
    for (int i = 0; i < size - 1; i++) {
        if (stack[i] > stack[i + 1]) return 0; // Not sorted
    }
    return 1; // Sorted
}

// Calculate distance to sortedness
int distance_to_sorted(int *stack, int size) {
    int *copy = malloc(size * sizeof(int));
    if (!copy) return -1;

    for (int i = 0; i < size; i++) {
        copy[i] = stack[i];
    }

    int ops = 0;

    // Simulate operations to bring the stack closer to sorted
    while (!is_sorted(copy, size)) {
        if (copy[0] > copy[1]) {
            sa(copy, size);
            ops++;
        } else {
            ra(copy, size);
            ops++;
        }
    }

    free(copy);
    return ops; // Number of operations required
}

int main() {
    int stack[] = {3, 2, 5, 1, 4};
    int size = sizeof(stack) / sizeof(stack[0]);

    int distance = distance_to_sorted(stack, size);
    printf("Distance to sorted: %d\n", distance);

    return 0;
}

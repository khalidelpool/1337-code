#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 500
#define MAX_OPERATIONS 11
#define INITIAL_MAX_DEPTH 5
#define DEPTH_INCREMENT 3

// Structures need to be defined before use
typedef struct {
    int* a;
    int* b;
    int size_a;
    int size_b;
    int capacity;
} Stacks;

typedef struct {
    char** operations;
    int count;
} Solution;

// Global variables
const char* OPERATIONS[] = {"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};
Solution best_solution = {NULL, INT_MAX};
int current_max_depth = INT_MAX;

// Function prototypes - need to be declared before use
Stacks* create_stacks(int capacity);
void free_stacks(Stacks* stacks);
void solve_iterative(Stacks* stacks);
void print_final_solution(void);
int count_arguments(char* str);

// Stack operations
void swap_a(Stacks* stacks) {
    if (stacks->size_a < 2) return;
    int temp = stacks->a[0];
    stacks->a[0] = stacks->a[1];
    stacks->a[1] = temp;
}

void swap_b(Stacks* stacks) {
    if (stacks->size_b < 2) return;
    int temp = stacks->b[0];
    stacks->b[0] = stacks->b[1];
    stacks->b[1] = temp;
}

void push_a(Stacks* stacks) {
    if (stacks->size_b == 0) return;
    for (int i = stacks->size_a; i > 0; i--)
        stacks->a[i] = stacks->a[i-1];
    stacks->a[0] = stacks->b[0];
    for (int i = 0; i < stacks->size_b - 1; i++)
        stacks->b[i] = stacks->b[i+1];
    stacks->size_a++;
    stacks->size_b--;
}

void push_b(Stacks* stacks) {
    if (stacks->size_a == 0) return;
    for (int i = stacks->size_b; i > 0; i--)
        stacks->b[i] = stacks->b[i-1];
    stacks->b[0] = stacks->a[0];
    for (int i = 0; i < stacks->size_a - 1; i++)
        stacks->a[i] = stacks->a[i+1];
    stacks->size_b++;
    stacks->size_a--;
}

void rotate_a(Stacks* stacks) {
    if (stacks->size_a < 2) return;
    int temp = stacks->a[0];
    for (int i = 0; i < stacks->size_a - 1; i++)
        stacks->a[i] = stacks->a[i+1];
    stacks->a[stacks->size_a-1] = temp;
}

void rotate_b(Stacks* stacks) {
    if (stacks->size_b < 2) return;
    int temp = stacks->b[0];
    for (int i = 0; i < stacks->size_b - 1; i++)
        stacks->b[i] = stacks->b[i+1];
    stacks->b[stacks->size_b-1] = temp;
}

void reverse_rotate_a(Stacks* stacks) {
    if (stacks->size_a < 2) return;
    int temp = stacks->a[stacks->size_a-1];
    for (int i = stacks->size_a - 1; i > 0; i--)
        stacks->a[i] = stacks->a[i-1];
    stacks->a[0] = temp;
}

void reverse_rotate_b(Stacks* stacks) {
    if (stacks->size_b < 2) return;
    int temp = stacks->b[stacks->size_b-1];
    for (int i = stacks->size_b - 1; i > 0; i--)
        stacks->b[i] = stacks->b[i-1];
    stacks->b[0] = temp;
}

// Stack management functions
Stacks* create_stacks(int capacity) {
    Stacks* stacks = malloc(sizeof(Stacks));
    stacks->a = malloc(capacity * sizeof(int));
    stacks->b = malloc(capacity * sizeof(int));
    stacks->capacity = capacity;
    stacks->size_a = 0;
    stacks->size_b = 0;
    return stacks;
}

void free_stacks(Stacks* stacks) {
    free(stacks->a);
    free(stacks->b);
    free(stacks);
}

Stacks* copy_stacks(Stacks* original) {
    Stacks* copy = create_stacks(original->capacity);
    memcpy(copy->a, original->a, original->size_a * sizeof(int));
    memcpy(copy->b, original->b, original->size_b * sizeof(int));
    copy->size_a = original->size_a;
    copy->size_b = original->size_b;
    return copy;
}

bool is_sorted(Stacks* stacks) {
    if (stacks->size_b != 0) return false;
    for (int i = 0; i < stacks->size_a - 1; i++) {
        if (stacks->a[i] > stacks->a[i+1]) return false;
    }
    return true;
}

void apply_operation(Stacks* stacks, const char* op) {
    if (strcmp(op, "sa") == 0) swap_a(stacks);
    else if (strcmp(op, "sb") == 0) swap_b(stacks);
    else if (strcmp(op, "ss") == 0) { swap_a(stacks); swap_b(stacks); }
    else if (strcmp(op, "pa") == 0) push_a(stacks);
    else if (strcmp(op, "pb") == 0) push_b(stacks);
    else if (strcmp(op, "ra") == 0) rotate_a(stacks);
    else if (strcmp(op, "rb") == 0) rotate_b(stacks);
    else if (strcmp(op, "rr") == 0) { rotate_a(stacks); rotate_b(stacks); }
    else if (strcmp(op, "rra") == 0) reverse_rotate_a(stacks);
    else if (strcmp(op, "rrb") == 0) reverse_rotate_b(stacks);
    else if (strcmp(op, "rrr") == 0) { reverse_rotate_a(stacks); reverse_rotate_b(stacks); }
}

void update_best_solution(Solution* current) {
    if (current->count < best_solution.count) {
        if (best_solution.operations != NULL) {
            for (int i = 0; i < best_solution.count; i++) {
                free(best_solution.operations[i]);
            }
            free(best_solution.operations);
        }
        
        best_solution.operations = malloc(current->count * sizeof(char*));
        best_solution.count = current->count;
        for (int i = 0; i < current->count; i++) {
            best_solution.operations[i] = strdup(current->operations[i]);
        }
        
        current_max_depth = current->count - 1;
    }
}

void print_final_solution(void) {
    if (best_solution.count != INT_MAX) {
        for (int i = 0; i < best_solution.count; i++) {
            printf("%s\n", best_solution.operations[i]);
        }
    } else {
        printf("No solution found\n");
    }
}

void solve(Stacks* stacks, Solution* current_solution, int depth) {
    if (depth > current_max_depth) return;
    
    if (is_sorted(stacks)) {
        update_best_solution(current_solution);
        return;
    }

    for (int i = 0; i < MAX_OPERATIONS; i++) {
        Stacks* temp = copy_stacks(stacks);
        apply_operation(temp, OPERATIONS[i]);
        
        current_solution->operations[current_solution->count] = strdup(OPERATIONS[i]);
        current_solution->count++;
        
        solve(temp, current_solution, depth + 1);
        
        free(current_solution->operations[current_solution->count - 1]);
        current_solution->count--;
        free_stacks(temp);
    }
}

void solve_iterative(Stacks* stacks) {
    Solution current_solution = {
        .operations = malloc(MAX_SIZE * sizeof(char*)),
        .count = 0
    };

    int max_depth = INITIAL_MAX_DEPTH;
    bool solution_found = false;

    while (!solution_found && max_depth <= MAX_SIZE) {
        current_max_depth = max_depth;
        solve(stacks, &current_solution, 0);
        
        if (best_solution.count != INT_MAX) {
            solution_found = true;
        } else {
            max_depth += DEPTH_INCREMENT;
        }
    }

    free(current_solution.operations);
}

int count_arguments(char* str) {
    int count = 0;
    char* token = strtok(str, " ");
    while (token != NULL) {
        count++;
        token = strtok(NULL, " ");
    }
    return count;
}

int main(void) {
    char input[MAX_SIZE * 10];
    
	printf("enter the numbers: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    input[strcspn(input, "\n")] = 0;
    
    char input_copy[MAX_SIZE * 10];
    strcpy(input_copy, input);
    
    int size = count_arguments(input_copy);
    
    if (size == 0) {
        printf("No numbers provided\n");
        return 1;
    }
    
    Stacks* stacks = create_stacks(size);
    
    char* token = strtok(input, " ");
    while (token != NULL && stacks->size_a < size) {
        stacks->a[stacks->size_a++] = atoi(token);
        token = strtok(NULL, " ");
    }
    
    printf("Initial stack A: ");
    for (int i = 0; i < stacks->size_a; i++) {
        printf("%d ", stacks->a[i]);
    }
    printf("\n");
    
    solve_iterative(stacks);
    
    printf("Solution steps:\n");
    print_final_solution();
    
    free_stacks(stacks);
    if (best_solution.operations != NULL) {
        for (int i = 0; i < best_solution.count; i++) {
            free(best_solution.operations[i]);
        }
        free(best_solution.operations);
    }
    
    return 0;
}

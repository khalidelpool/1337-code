#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_INPUT 100

typedef struct {
    int items[MAX_SIZE];
    int top;
    char name;
} Stack;

void init_stack(Stack *s, char name) {
    s->top = -1;
    s->name = name;
}

void push(Stack *s, int value) {
    if (s->top < MAX_SIZE - 1) {
        s->items[++(s->top)] = value;
    }
}

int pop(Stack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return -1;
}

// Helper function to get the maximum number width for formatting
int get_max_width(Stack *a, Stack *b) {
    int max_width = 1;  // Minimum width for empty stacks
    char num_str[32];
    
    // Check stack a
    for (int i = 0; i <= a->top; i++) {
        snprintf(num_str, sizeof(num_str), "%d", a->items[i]);
        int len = strlen(num_str);
        if (len > max_width) max_width = len;
    }
    
    // Check stack b
    for (int i = 0; i <= b->top; i++) {
        snprintf(num_str, sizeof(num_str), "%d", b->items[i]);
        int len = strlen(num_str);
        if (len > max_width) max_width = len;
    }
    
    return max_width;
}

void display_stacks(Stack *a, Stack *b) {
    int max_height = (a->top > b->top) ? a->top + 1 : b->top + 1;
    int width = get_max_width(a, b);
    
    printf("\n");
    // Print the column headers
    printf("%-*s     %-*s\n", width, "a", width, "b");
    printf("%.*s     %.*s\n", width, "--------", width, "--------");
    
    // Print the stacks vertically
    for (int i = max_height - 1; i >= 0; i--) {
        // Print stack a element
        if (i <= a->top) {
            printf("%*d", width, a->items[i]);
        } else {
            printf("%*s", width, "");
        }
        
        printf("     ");  // Separation between stacks
        
        // Print stack b element
        if (i <= b->top) {
            printf("%*d", width, b->items[i]);
        } else {
            printf("%*s", width, "");
        }
        printf("\n");
    }
    printf("%.*s     %.*s\n", width, "--------", width, "--------");
    printf("\n");
}

void sa(Stack *a) {
    if (a->top >= 1) {
        int temp = a->items[a->top];
        a->items[a->top] = a->items[a->top - 1];
        a->items[a->top - 1] = temp;
    }
}

void sb(Stack *b) {
    if (b->top >= 1) {
        int temp = b->items[b->top];
        b->items[b->top] = b->items[b->top - 1];
        b->items[b->top - 1] = temp;
    }
}

void ss(Stack *a, Stack *b) {
    sa(a);
    sb(b);
}

void pa(Stack *a, Stack *b) {
    if (b->top >= 0) {
        push(a, pop(b));
    }
}

void pb(Stack *a, Stack *b) {
    if (a->top >= 0) {
        push(b, pop(a));
    }
}

void ra(Stack *a) {
    if (a->top >= 1) {
        int temp = a->items[a->top];
        for (int i = a->top; i > 0; i--) {
            a->items[i] = a->items[i - 1];
        }
        a->items[0] = temp;
    }
}

void rb(Stack *b) {
    if (b->top >= 1) {
        int temp = b->items[b->top];
        for (int i = b->top; i > 0; i--) {
            b->items[i] = b->items[i - 1];
        }
        b->items[0] = temp;
    }
}

void rr(Stack *a, Stack *b) {
    ra(a);
    rb(b);
}

void rra(Stack *a) {
    if (a->top >= 1) {
        int temp = a->items[0];
        for (int i = 0; i < a->top; i++) {
            a->items[i] = a->items[i + 1];
        }
        a->items[a->top] = temp;
    }
}

void rrb(Stack *b) {
    if (b->top >= 1) {
        int temp = b->items[0];
        for (int i = 0; i < b->top; i++) {
            b->items[i] = b->items[i + 1];
        }
        b->items[b->top] = temp;
    }
}

void rrr(Stack *a, Stack *b) {
    rra(a);
    rrb(b);
}

int main() {
    Stack a, b;
    init_stack(&a, 'a');
    init_stack(&b, 'b');
    char input[MAX_INPUT];
    char *token;
    int numbers[MAX_SIZE];
    int count = 0;
    
    printf("Enter numbers for stack a (space-separated): ");
    fgets(input, MAX_INPUT, stdin);
    
    // First, store all numbers in an array
    token = strtok(input, " \n");
    while (token != NULL) {
        numbers[count++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    
    // Then push them in reverse order to get the correct stack order
    for (int i = count - 1; i >= 0; i--) {
        push(&a, numbers[i]);
    }
    
    display_stacks(&a, &b);
    
    printf("\nAvailable operations:\n");
    printf("sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr, exit\n");
    
    while (1) {
        printf("\nEnter operation: ");
        scanf("%s", input);
        
        if (strcmp(input, "exit") == 0) break;
        else if (strcmp(input, "sa") == 0) sa(&a);
        else if (strcmp(input, "sb") == 0) sb(&b);
        else if (strcmp(input, "ss") == 0) ss(&a, &b);
        else if (strcmp(input, "pa") == 0) pa(&a, &b);
        else if (strcmp(input, "pb") == 0) pb(&a, &b);
        else if (strcmp(input, "ra") == 0) ra(&a);
        else if (strcmp(input, "rb") == 0) rb(&b);
        else if (strcmp(input, "rr") == 0) rr(&a, &b);
        else if (strcmp(input, "rra") == 0) rra(&a);
        else if (strcmp(input, "rrb") == 0) rrb(&b);
        else if (strcmp(input, "rrr") == 0) rrr(&a, &b);
        else printf("Invalid operation!\n");
        
        display_stacks(&a, &b);
    }
    
    return 0;
}

// pb
// pb
// pb
// rra
// pb
// sa
// pa
// pa
// rrb
// pa
// rrb
// rrb
// pa
// rra

// pb
// pb
// pb
// rra
// pb
// sa
// pa
// pa
// rrb
// pa
// rrb
// rrb
// pa
// rra

// pb
// pb
// pb
// rra
// pb
// rra
// sa
// rrb
// pa
// pa
// rrb
// pa
// rrb
// rrb
// pa
// rra
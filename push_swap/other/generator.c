#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SEQUENCE_LENGTH 10
#define MAX_PATTERNS 1024  // 2^10, maximum possible patterns
#define MAX_ATTEMPTS 1000

typedef struct {
    int n;
    int min_val;
    int max_val;
    int max_attempts;
} PatternGenerator;

// Function to generate all possible patterns
void generate_patterns(bool patterns[][MAX_SEQUENCE_LENGTH], int n, int *pattern_count) {
    *pattern_count = 1 << n;  // 2^n patterns
    for (int i = 0; i < *pattern_count; i++) {
        for (int j = 0; j < n; j++) {
            patterns[i][j] = (i & (1 << j)) != 0;
        }
    }
}

// Fisher-Yates shuffle algorithm
void shuffle(int *array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Check if sequence follows the pattern
bool is_valid_sequence(int *numbers, bool *pattern, int n) {
    for (int i = 0; i < n; i++) {
        int current = numbers[i];
        int next_idx = (i + 1) % n;
        int next_val = numbers[next_idx];
        
        if (pattern[i]) {  // Should go up
            if (next_val <= current) return false;
        } else {  // Should go down
            if (next_val >= current) return false;
        }
    }
    return true;
}

// Check if pattern is all ups or all downs
bool is_all_same_pattern(bool *pattern, int n) {
    bool first = pattern[0];
    for (int i = 1; i < n; i++) {
        if (pattern[i] != first) return false;
    }
    return true;
}

// Generate a circular sequence (all ups or all downs)
bool generate_circular_sequence(int *result, int n, int min_val, int max_val, bool is_ascending) {
    int range = max_val - min_val + 1;
    int *numbers = malloc(range * sizeof(int));
    
    // Initialize array with all possible values
    for (int i = 0; i < range; i++) {
        numbers[i] = min_val + i;
    }
    
    for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
        shuffle(numbers, range);
        
        // Take first n numbers
        memcpy(result, numbers, n * sizeof(int));
        
        // Find rotation point
        int rotation_idx = 0;
        int target = is_ascending ? result[0] : result[0];
        for (int i = 1; i < n; i++) {
            if (is_ascending && result[i] < target) {
                target = result[i];
                rotation_idx = i;
            } else if (!is_ascending && result[i] > target) {
                target = result[i];
                rotation_idx = i;
            }
        }
        
        // Rotate array
        if (rotation_idx > 0) {
            int *temp = malloc(n * sizeof(int));
            memcpy(temp, result + rotation_idx, (n - rotation_idx) * sizeof(int));
            memcpy(temp + (n - rotation_idx), result, rotation_idx * sizeof(int));
            memcpy(result, temp, n * sizeof(int));
            free(temp);
        }
        
        // Verify sequence
        bool *test_pattern = malloc(n * sizeof(bool));
        for (int i = 0; i < n; i++) test_pattern[i] = is_ascending;
        if (is_valid_sequence(result, test_pattern, n)) {
            free(test_pattern);
            free(numbers);
            return true;
        }
        free(test_pattern);
    }
    
    free(numbers);
    return false;
}

// Generate a sequence following the given pattern
bool generate_sequence(int *result, bool *pattern, int n, int min_val, int max_val) {
    if (is_all_same_pattern(pattern, n)) {
        return generate_circular_sequence(result, n, min_val, max_val, pattern[0]);
    }
    
    int range = max_val - min_val + 1;
    int *numbers = malloc(range * sizeof(int));
    
    for (int i = 0; i < range; i++) {
        numbers[i] = min_val + i;
    }
    
    for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
        shuffle(numbers, range);
        memcpy(result, numbers, n * sizeof(int));
        
        if (is_valid_sequence(result, pattern, n)) {
            free(numbers);
            return true;
        }
    }
    
    free(numbers);
    return false;
}

void pattern_to_string(bool *pattern, int n, char *result) {
    for (int i = 0; i < n; i++) {
        result[i] = pattern[i] ? 'U' : 'D';  // U for up, D for down
    }
    result[n] = '\0';
}

int main() {
    srand(time(NULL));
    int n, min_val, max_val;
    
    // Get user input
    do {
        printf("Enter the sequence length (2-6 recommended): ");
        scanf("%d", &n);
        if (n <= 0) {
            printf("Please enter a positive number\n");
        } else if (n > 8) {
            printf("Warning: Large numbers may take very long to process\n");
            printf("Do you want to continue? (y/n): ");
            char confirm;
            scanf(" %c", &confirm);
            if (confirm != 'y' && confirm != 'Y') continue;
        }
    } while (n <= 0);
    
    do {
        printf("Enter minimum value (default 0): ");
        char input[10];
        scanf("%s", input);
        min_val = strlen(input) == 0 ? 0 : atoi(input);
        
        printf("Enter maximum value (default 20): ");
        scanf("%s", input);
        max_val = strlen(input) == 0 ? 20 : atoi(input);
        
        if (min_val >= max_val) {
            printf("Maximum value must be greater than minimum value\n");
            continue;
        }
        if (max_val - min_val < n) {
            printf("Range must be at least %d numbers wide\n", n);
            continue;
        }
        break;
    } while (1);
    
    // Generate and process all patterns
    bool patterns[MAX_PATTERNS][MAX_SEQUENCE_LENGTH];
    int pattern_count;
    generate_patterns(patterns, n, &pattern_count);
    
    printf("\nGenerating %d different patterns...\n", pattern_count);
    clock_t start = clock();
    
    for (int i = 0; i < pattern_count; i++) {
        int sequence[MAX_SEQUENCE_LENGTH];
        char pattern_str[MAX_SEQUENCE_LENGTH + 1];
        pattern_to_string(patterns[i], n, pattern_str);
        
        bool success = false;
        for (int retry = 0; retry < 3 && !success; retry++) {
            success = generate_sequence(sequence, patterns[i], n, min_val, max_val);
        }
        
        printf("%c Pattern %s: ", success ? '+' : 'x', pattern_str);  // Using + for success, x for failure
        if (success) {
            printf("[");
            for (int j = 0; j < n; j++) {
                printf("%d%s", sequence[j], j < n - 1 ? ", " : "");
            }
            printf("]\n");
        } else {
            printf("Failed to generate\n");
        }
        
        if ((i + 1) % 4 == 0) {
            printf("Progress: %d/%d patterns processed\n", i + 1, pattern_count);
        }
    }
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nGeneration completed in %.2f seconds\n", time_spent);
    
    return 0;
}
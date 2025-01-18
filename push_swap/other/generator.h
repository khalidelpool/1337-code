#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdbool.h>

typedef struct {
    int n;
    int min_val;
    int max_val;
    int max_attempts;
} PatternGenerator;

bool generate_sequence(int *result, bool *pattern, int n, int min_val, int max_val);
void generate_patterns(bool patterns[][10], int n, int *pattern_count);

#endif
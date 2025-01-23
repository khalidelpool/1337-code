#include <stdio.h>
#include <ctype.h>
#include "./libft/libft.h"

int main() {
    char *buffer; // Buffer to store input

    // Read input from stdin line by line
    while (buffer = get_next_line(0)) {
        // Process each character in the line
        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = toupper(buffer[i]); // Convert to uppercase
        }
        // Output the processed line
        printf("%s", buffer);
        free(buffer);
    }

    return 0;
}

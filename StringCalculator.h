#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1024

// Function to check if a string represents a number
int is_number(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i]) && str[i] != '-') {
            return 0;
        }
    }
    return 1;
}

// Function to split the string based on delimiters and calculate the sum
int split_and_sum(const char *str, const char *delimiters) {
    int sum = 0;
    char input[MAX_INPUT_LENGTH];
    strncpy(input, str, MAX_INPUT_LENGTH);
    
    char *token = strtok(input, delimiters);
    while (token != NULL) {
        if (is_number(token)) {
            int num = atoi(token);
            if (num < 0) {
                fprintf(stderr, "negatives not allowed: %d\n", num);
                exit(EXIT_FAILURE);
            } else if (num <= 1000) {
                sum += num;
            }
        }
        token = strtok(NULL, delimiters);
    }
    
    return sum;
}

// Function to add numbers in the string
int add(const char *input) {
    if (strlen(input) == 0) {
        return 0;
    }
    
    char delimiters[] = ",\n";
    const char *numbers = input;

    if (strncmp(input, "//", 2) == 0) {
        const char *delimiter_end = strstr(input, "\n");
        if (delimiter_end != NULL) {
            size_t delimiter_length = delimiter_end - input - 2;
            strncpy(delimiters, input + 2, delimiter_length);
            delimiters[delimiter_length] = '\0';
            numbers = delimiter_end + 1;
        }
    }
    
    return split_and_sum(numbers, delimiters);
}

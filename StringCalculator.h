#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 1024

// Helper function to check if a character is a digit or a negative sign
int is_valid_char(char c) {
    return isdigit(c) || c == '-';
}

// Helper function to iterate over a string and apply a function to each character
int iterate_string(const char *str, int (*func)(char)) {
    while (*str != '\0') {
        if (!func(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

// Function to check if a string represents a number
int is_number(const char *str) {
    return iterate_string(str, is_valid_char);
}

// Helper function to extract the custom delimiter
void extract_delimiter(const char *start, const char *end, char *delimiters) {
    size_t delimiter_length = end - start;
    strncpy(delimiters, start, delimiter_length);
    delimiters[delimiter_length] = '\0';
}

// Function to get the custom delimiter
void get_custom_delimiter(const char *input, char *delimiters) {
    const char *delimiter_end = strstr(input, "\n");
    if (delimiter_end != NULL) {
        extract_delimiter(input + 2, delimiter_end, delimiters);
    }
}

// Helper function to add a number to the sum if it meets the criteria
void add_to_sum(const char *token, int *sum) {
    int num = atoi(token);
    if (num < 0) {
        fprintf(stderr, "negatives not allowed: %d\n", num);
       
    }
    if (num <= 1000) {
        *sum += num;
    }
}

// Function to sum valid numbers from tokens
int sum_tokens(const char *numbers, const char *delimiters) {
    int sum = 0;
    char input[MAX_INPUT_LENGTH];
    strncpy(input, numbers, MAX_INPUT_LENGTH);
    
    char *token = strtok(input, delimiters);
    while (token != NULL) {
        if (is_number(token)) {
            add_to_sum(token, &sum);
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
        get_custom_delimiter(input, delimiters);
        numbers = strstr(input, "\n") + 1;
    }
    
    return sum_tokens(numbers, delimiters);
}

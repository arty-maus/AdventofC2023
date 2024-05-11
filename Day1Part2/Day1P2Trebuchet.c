#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024
#define NUM_WORDS 9

void replaceNumberWords(char *input, const char *number_words[], const char *digits[]);

int main(int argc, char *argv[]) {
    const char *number_words[NUM_WORDS] = {"one", "two", "three", "four", "five",
                                            "six", "seven", "eight", "nine"};
    const char *digits[NUM_WORDS] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    if (argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    char line[MAX_LENGTH];

    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    int total = 0;

    while (fgets(line, MAX_LENGTH, file)) {
        char *input = line;
        int input_len = strlen(input);

        // Find occurrences of number words and replace
        replaceNumberWords(input, number_words, digits);

        // Check if line contains any numbers
        int contains_numbers = 0;
        for (int i = 0; i < input_len; i++) {
            if (isdigit(input[i])) {
                contains_numbers = 1;
                break;
            }
        }

        if (!contains_numbers) {
            continue; // No numbers found, skip line
        }

        int head_index = 0;
        int tail_index = input_len - 1;

        // Find first number from head
        while (!isdigit(input[head_index]) && input[head_index] != '\0') {
            head_index++;
        }

        // Find first number from tail
        while (!isdigit(input[tail_index]) && tail_index >= 0) {
            tail_index--;
        }

        // Convert numbers to integers
        int head = input[head_index] - '0';
        int tail = input[tail_index] - '0';
        int totalThisLine = (head * 10) + tail;

        total += totalThisLine;
    }

    fclose(file);

    printf("Total: %d\n", total);

    return 0;
}

void replaceNumberWords(char *input, const char *number_words[], const char *digits[]) {
    int input_len = strlen(input);
    int indices[MAX_LENGTH][2];
    int count = 0;

    // Find occurrences of number words and store indices
    for (int i = 0; i < input_len; i++) {
        for (int j = 0; j < NUM_WORDS; j++) {
            const char *word = number_words[j];
            int word_len = strlen(word);
            if (strncmp(&input[i], word, word_len) == 0) {
                indices[count][0] = i;
                indices[count][1] = j;
                count++;
                i += word_len - 1; // Move i to the end of the word
                break;
            }
        }
    }

    // Replace number words with digits
    for (int i = count - 1; i >= 0; i--) {
        int index = indices[i][0];
        int digit = indices[i][1];
        const char *replacement = digits[digit];
        int replacement_len = strlen(replacement);
        int word_len = strlen(number_words[digit]);

        memmove(&input[index + replacement_len], &input[index + word_len], strlen(&input[index + word_len]) + 1);
        memcpy(&input[index], replacement, replacement_len);
    }
}

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <input file>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];

  FILE *file = fopen(filename, "r");
  char line[MAX_LINE_LENGTH];

  if (!file) {
    printf("Error opening file\n");
    return 1;
  }

  int total = 0;

  while (fgets(line, MAX_LINE_LENGTH, file)) {
    char *input = line;

    int head_index = 0;
    int tail_index = strlen(input) - 1;

    // Find first number from head
    while (!isdigit(input[head_index]) && input[head_index] != '\0') {
      head_index++;
    }

    // Find first number from tail
    while (!isdigit(input[tail_index]) && tail_index >= 0) {
      tail_index--;
    }

    // If no numbers found, skip line
    if (head_index == strlen(input) || tail_index < 0) {
      continue;
    }

    // Convert numbers to integers
    int head = input[head_index] - '0';
    int tail = input[tail_index] - '0';

    int totalThisLine = (head * 10) + tail;

    total += totalThisLine;

    printf("Head: %d, Tail: %d, Total: %d\n", head, tail, totalThisLine);
  }

  fclose(file);

  printf("Total: %d\n", total);

  return 0;
}
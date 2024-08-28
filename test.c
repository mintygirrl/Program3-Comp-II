#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
#include "status.h"

int main(int argc, char* argv[]) {
    struct TreeNode* unique_numbers = NULL;
    int number;

    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Could not open input.txt for reading\n");
        return 1;
    }

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Could not open output.txt for writing\n");
        fclose(inputFile);
        return 1;
    }

    // Read numbers from input.txt
    while (fscanf(inputFile, "%d", &number) == 1) {
        if (number == -1) {
            break;
        }
        if (number >= 0 && number <= 2000000000) {
            unique_numbers = insert(unique_numbers, number);
        } else {
            fprintf(stderr, "Invalid number %d ignored. Please enter numbers within the range 0 to 2,000,000,000.\n", number);
        }
    }

    // Write sorted unique numbers to output.txt
    inorderTraversal(unique_numbers, outputFile);

    // Clean up
    fclose(inputFile);
    fclose(outputFile);
    freeTree(unique_numbers);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 140

int main(int argc, char **argv) {

    FILE *fp;
    int ch, row, col, count = 0;
    char mat[SIZE][SIZE];

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        exit(EXIT_FAILURE);
    }

    row = 0, col = 0;
    while((ch = getc(fp)) != EOF) {
        if (ch != '\n') {
            mat[row][col] = ch;
            col++;
        } else {
            row++;
            col = 0;
        }
    }

    /* Horizontally */
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 3; j++) {
            if ((mat[i][j] == 'X' &&
                 mat[i][j + 1] == 'M' &&
                 mat[i][j + 2] == 'A' &&
                 mat[i][j + 3] == 'S') ||
                (mat[i][j] == 'S' &&
                 mat[i][j + 1] == 'A' &&
                 mat[i][j + 2] == 'M' &&
                 mat[i][j + 3] == 'X'))
                count ++;
        }
    }
    /* Vertically */
    for (int i = 0; i < SIZE - 3; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((mat[i][j] == 'X' &&
                 mat[i + 1][j] == 'M' &&
                 mat[i + 2][j] == 'A' &&
                 mat[i + 3][j] == 'S') ||
                (mat[i][j] == 'S' &&
                 mat[i + 1][j] == 'A' &&
                 mat[i + 2][j] == 'M' &&
                 mat[i + 3][j] == 'X'))
                count ++;
        }
    }
    /* Diagonally (y = x) */
    for (int i = 0; i < SIZE - 3; i++) {
        for (int j = 0; j < SIZE - 3; j++) {
            if ((mat[i][j] == 'X' &&
                 mat[i + 1][j + 1] == 'M' &&
                 mat[i + 2][j + 2] == 'A' &&
                 mat[i + 3][j + 3] == 'S') ||
                (mat[i][j] == 'S' &&
                 mat[i + 1][j + 1] == 'A' &&
                 mat[i + 2][j + 2] == 'M' &&
                 mat[i + 3][j + 3] == 'X'))
                count++;
        }
    }

    /* Diagonally (y = l - x) */
    for (int i = 3; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 3; j++) {
            if ((mat[i][j] == 'X' &&
                 mat[i - 1][j + 1] == 'M' &&
                 mat[i - 2][j + 2] == 'A' &&
                 mat[i - 3][j + 3] == 'S') ||
                (mat[i][j] == 'S' &&
                 mat[i - 1][j + 1] == 'A' &&
                 mat[i - 2][j + 2] == 'M' &&
                 mat[i - 3][j + 3] == 'X'))
                count++;
        }
    }

    printf("The number of XMAS is: %d\n", count);

    return EXIT_SUCCESS;
}
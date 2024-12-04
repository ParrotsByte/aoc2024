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

    for (int i = 0; i < SIZE - 2; i++) {
        for (int j = 0; j < SIZE - 2; j++) {
            if (((mat[i][j] == 'M' &&
                 mat[i + 1][j + 1] == 'A' &&
                 mat[i + 2][j + 2] == 'S') ||
                (mat[i][j] == 'S' &&
                 mat[i + 1][j + 1] == 'A' &&
                 mat[i + 2][j + 2] == 'M')) 
                 && // Now second diagonal
                ((mat[i + 2][j] == 'M' &&
                 mat[i + 1][j + 1] == 'A' &&
                 mat[i][j + 2] == 'S') ||
                (mat[i + 2][j] == 'S' &&
                 mat[i + 1][j + 1] == 'A' &&
                 mat[i][j + 2] == 'M')))
                count++;
        }
    }    

    printf("The number of X-MAS is: %d\n", count);

    return EXIT_SUCCESS;
}
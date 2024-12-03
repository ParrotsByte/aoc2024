#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 8
#define NUM_LINES 1000

bool check_safety(int *array, int size) {
    bool decreasing = false, increasing = false, anomaly = false;
    int diff, a_diff;

    for (int i = 1; i < size; i++) {
        diff = array[i] - array[i - 1];
        a_diff = abs(diff);

        if (diff < 0)
            increasing = true;
        else if (diff > 0)
            decreasing = true;
        else {
            anomaly = true;
            break;
        }
            
        if (increasing && decreasing) {
            anomaly = true;
            break;
        }
            
        if (a_diff < 1 || a_diff > 3) {
            anomaly = true;
            break;
        }
    }

    return !anomaly;
}

int main(int argc, char **argv)
{
    FILE *fp;
    int ch, i = 0, num_safe = 0;
    int num_spaces[NUM_LINES] = {0}, array[MAX_SIZE];

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) != EOF) {
        if (ch == '\n')
            i++;
        if (ch == ' ')
            num_spaces[i]++;
    }
    rewind(fp);

    for (int p = 0; p < NUM_LINES; p++) {
        for (int q = 0; q < num_spaces[p] + 1; q++) {
            fscanf(fp, "%d", array + q);
        }

        if (check_safety(array, num_spaces[p] + 1)) {
            num_safe++;
            continue;
        }

        int tmp_array[MAX_SIZE];
        for (int q = 0; q < num_spaces[p] + 1; q++) {
            for (int r = 0; r < num_spaces[p]; r++) {
                if (r >= q)
                    tmp_array[r] = array[r + 1];
                else
                    tmp_array[r] = array[r];
            }

            if (check_safety(tmp_array, num_spaces[p])) {
                num_safe++;
                break;
            }
        }
    }

    printf("Number of safe entries: %d\n", num_safe);

    fclose(fp);

    return EXIT_SUCCESS;
}
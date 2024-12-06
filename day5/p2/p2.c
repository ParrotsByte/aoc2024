#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1176
#define U_SIZE 70

int compare_ruleset(const void *p, const void* q);

int before[SIZE], after[SIZE];

int main(int argc, char **argv) {
    FILE *fp;
    int result = 0, count = 0;
    char update[U_SIZE];
    bool found_rule = false, valid_update = true;

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SIZE; i++)
        fscanf(fp, "%d|%d", before + i, after + i);

    fscanf(fp, "%*[\n]");

    for (int i = 0; fgets(update, sizeof(update), fp) != NULL; i++) {
        int num_entries = 1;
        int len = strlen(update);

        for (int j = 0; j < len; j++) {
            if(update[j] == ',')
                num_entries++;
        }

        int numbers[num_entries];

        for (int j = 0; j < num_entries; j++)
            numbers[j] = strtol(update + 3 * j, NULL, 10);

        for (int j = 0; j < (num_entries - 1) && valid_update; j++) {
            for (int k = j + 1; k < num_entries; k++) {
                for (int r = 0; r < SIZE; r++) {
                    if (before[r] == numbers[j] &&
                        after[r] == numbers[k]) {
                        found_rule = true;
                        break;
                    }
                    if (before[r] == numbers[k] &&
                        after[r] == numbers[j])
                        break;
                }
                if (!found_rule) {
                    valid_update = false;
                    break;
                }
                found_rule = false;
            }
        }

        if (!valid_update) {
            qsort(numbers, num_entries, sizeof(int), compare_ruleset);
            result += numbers[(num_entries - 1) / 2];
        }    

        valid_update = true;
    }

    fclose(fp);

    printf("The result is %d\n", result);

    return EXIT_SUCCESS;
}

int compare_ruleset(const void *p, const void *q) {
    int a = *((int *) p);
    int b = *((int *) q);
    for (int r = 0; r < SIZE; r++) {
        if (before[r] == a && after[r] == b)
            return -1;
        if (before[r] == b && after[r] == a)
            return 1;
    }
}
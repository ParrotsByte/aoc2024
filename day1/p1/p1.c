#include <stdio.h>
#include <stdlib.h>

int compare_ints(const void *p, const void *q)
{
    if (*((int *) p) < *((int *) q))
        return -1;
    else if (*((int *) p) == *((int *) q))
        return 0;
    else
        return 1;
}

int main(int argc, char **argv)
{

    FILE *fp;
    int ch, lines = 0, result = 0;
    int *array1, *array2;

    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) != EOF)
        if (ch == '\n')
            lines++;
    
    array1 = malloc(lines * sizeof(int));
    array2 = malloc(lines * sizeof(int));

    if (array1 == NULL || array2 == NULL) {
        fprintf(stderr, "Couldn't allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    rewind(fp);
    
    for(int i = 0; i < lines; i++) {
        if (fscanf(fp, "%d %d", array1 + i, array2 + i) != 2)
            break;
    }

    qsort(array1, lines, sizeof(int), compare_ints);
    qsort(array2, lines, sizeof(int), compare_ints);

    for (int i = 0; i < lines; i++)
        array1[i] = abs(array1[i] - array2[i]);

    for (int i = 0; i < lines; i++)
        result += array1[i];

    printf("The result is %d\n", result);

    free(array1);
    free(array2);

    fclose(fp);

    return EXIT_SUCCESS;
}
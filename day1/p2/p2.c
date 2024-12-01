#include <stdio.h>
#include <stdlib.h>

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

    for (int i = 0; i < lines; i++) {
        int tmp = 0;
        for (int j = 0; j < lines; j++) {
            if (array1[i] == array2[j])
                tmp += array1[i];
        }
        result += tmp;
    }

    printf("The result is %d\n", result);

    free(array1);
    free(array2);

    fclose(fp);

    return EXIT_SUCCESS;
}
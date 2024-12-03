#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

#define B_SIZE 13

int main(int argc, char **argv)
{
    FILE *fp;
    int a, b, result = 0;
    regex_t regex;
    char buffer[B_SIZE];

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }

    if (regcomp(&regex, "^mul\\([[:digit:]]{1,3},[[:digit:]]{1,3}\\).*", REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regex.\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
            break;
        fseek(fp, (long) (-strlen(buffer) + 1), SEEK_CUR);

        if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
            sscanf(buffer, "mul(%d,%d)", &a, &b);
            result += a * b;
        }
    }

    printf("The result is %d\n", result);

    fclose(fp);
    regfree(&regex);

    return EXIT_SUCCESS;
}
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
    regex_t regex_mul, regex_do, regex_do_not;
    char buffer[B_SIZE];
    bool active = true;

    if ((fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Couldn't open file.\n");
        exit(EXIT_FAILURE);
    }

    if (regcomp(&regex_mul,
                "^mul\\([[:digit:]]{1,3},[[:digit:]]{1,3}\\).*",
                REG_EXTENDED) != 0 || 
        regcomp(&regex_do, "^do\\(\\).*", REG_EXTENDED) != 0 ||
        regcomp(&regex_do_not, "^don't\\(\\).*", REG_EXTENDED) != 0) {
        fprintf(stderr, "Error compiling regex.\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if (fgets(buffer, sizeof(buffer), fp) == NULL)
            break;
        fseek(fp, (long) -(strlen(buffer) + 1), SEEK_CUR);

        if (regexec(&regex_do, buffer, 0, NULL, 0) == 0)
            active = true;

        if (regexec(&regex_do_not, buffer, 0, NULL, 0) == 0)
            active = false;

        if (regexec(&regex_mul, buffer, 0, NULL, 0) == 0 && active) {
            sscanf(buffer, "mul(%d,%d)", &a, &b);
            result += a * b;
        }
    }

    printf("The result is %d\n", result);

    fclose(fp);
    regfree(&regex_mul);
    regfree(&regex_do);
    regfree(&regex_do_not);

    return EXIT_SUCCESS;
}
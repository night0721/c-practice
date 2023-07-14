#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLine();

char* copy();

int main() {
    int rc;
    char buff[1000];

    rc = getLine("Enter string> ", buff, sizeof(buff));
    if (rc == 1) {
        // Extra NL since my system doesn't output that on EOF.
        printf("\nNo input\n");
        return 1;
    }

    if (rc == 2) {
        printf("Input too long [%s]\n", buff);
        return 1;
    }

    printf("OK [%s]\n", buff);

    // copy buff and change the first letter to N
    char* newstr = copy(buff);
    printf("Old String: %s\n", buff);
    printf("New String: %s\n", newstr);
    free(strlen(buff) + 1);
}

#define OK       0
#define NO_INPUT 1
#define TOO_LONG 2
int getLine(char* prmpt, char* buff, size_t sz) {
    int ch, extra;

    // Get line with buffer overrun protection.
    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout);
    }
    if (fgets(buff, sz, stdin) == NULL)
        return NO_INPUT;

    // If it was too long, there'll be no newline. In that case, we flush
    // to end of line so that excess doesn't affect the next call.
    if (buff[strlen(buff) - 1] != '\n') {
        extra = 0;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = 1;
        return (extra == 1) ? TOO_LONG : OK;
    }

    // Otherwise remove newline and give string back to caller.
    buff[strlen(buff) - 1] = '\0';
    return OK;
}

char* copy(char* str) {
    int length = strlen(str);
    if (length == 0) return "";
    char* tocopy = malloc(length + 1);
    strcpy(tocopy, str);
    tocopy[0] = 'N';
    return tocopy;
}
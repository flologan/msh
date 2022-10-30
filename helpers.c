#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "helpers.h"

int get_input(char input_str[], int max_size)
{
    int i = 0;

    if (fgets(input_str, max_size, stdin) != 0) {
        return -1;
    }
    if (input_str[strlen(input_str) - 1] != '\n') {         // if input_str is greater than BUFFER_SIZE, there will be no '\n' character within the buffer
        i = 0;
        while (i != EOF && i != '\n') {
            i = getchar();
        }
    }
    return 0;
}

int tokenize(char *s, char ***argv)
{
    int rows = 0;
    int start = 0;
    int end = 0;
    int length = strlen(s);
    int i = 0;

    for (end = 0; end < length; end++) {
        // maybe add a while loop in here
        if (isspace(s[end])) {                                          // current char is a space: either leading or non-leading
            if (rows == 0) {                                            // current char is a leading space
                start++;                                                // move start index forward
            }
        }
        else {                                                          // current char is not a space
            rows++;                                                     // found a new argument, increment the amount of rows in argv
            while(!isspace(s[end])) {                                   // move to the end of the word
                end++;
            }
        }
    }
    if (!rows) {                                                        // if user enters the empty string
        return rows;
    }

    *argv = malloc((sizeof(**argv) * rows) + sizeof(void*));            // allocate enough memory for `rows` + NULL pointer
    if (*argv == NULL) {
        return -1;
    }

    for (end = start; end < length + 1; end++) {
        if (isspace(s[end - 1])) {
            start = end;
        }
        else if (isspace(s[end]) || end == length) {
            (*argv)[i] = malloc(sizeof(char) * (end - start + 1));
            if ((*argv)[i] == NULL) {
                return -1;
            }
            strncpy((*argv)[i], &s[start], end - start);
            (*argv)[i][end - start] = '\0';
            end++;
            i++;
            start = end;
        }
    }
    (*argv)[rows] = NULL;
    return rows;
}

int execute(int argc, char **argv)
{
    int pid = 0;
    int status = 0;

    pid = fork();
    if (pid == 0) {
        execvp(argv[0], argv);                  // if execvp succeeds, the following line will not execute execute
        exit(1);                                // if execvp fails, this line will execute and tell the parent process
    }
    else if (pid > 0) {
        pid = wait(&status);
        if (WIFEXITED(status)) {                // WIFEXITED(status) returns 1 if the child returns
            return WEXITSTATUS(status);         // queries the return status of the child
        }
        return 0;                               // child did not return
    }
    else {
        return -2;
    }
}

int free_vec(int argc, char **argv)
{
    int i = 0;

    if (argv == NULL) {
        return -1;
    }
    for (i = 0; i < argc; i++) {                // free each element of the string array
        if (argv[i] == NULL) {
            continue;
        }
        free(argv[i]);
        argv[i] = NULL;
    }
    free(argv);                                 // free the main string array pointer
    argv = NULL;
    return 0;
}

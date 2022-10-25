#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "msh.h"
#include "helpers.h"

int msh_loop(void)
{
    char buffer[buffer_size] = "";
    int argc = 0;
    char **argv = NULL;

    while (1) {
        printf(">: ");
        get_input(buffer, buffer_size);
        argc = tokenize(buffer, &argv);
        if (argc == 0) {
            continue;
        }

        /* start built-in shell functions */
        if (strcmp("cd", argv[0]) == 0) {
            if (chdir(argv[1]) != 0) {
                printf("msh: %s: %s: No such file or directory\n", argv[0], argv[1]);
            }
            else {
                printf("%s\n", getcwd(buffer, buffer_size ));
            }
            continue;
        }
        /* end built-in shell functions */

        /* main execution condition */
        else if (strcmp("exit", argv[0]) != 0) {
            if (execute(argc, argv) != 0) {
                printf("msh: %s: command not found\n", argv[0]);
            }
            free_vec(argc, argv);
            continue;
        }

        /* default case */
        else {
            printf("exit\n");
            free_vec(argc, argv);
            return 0;
        }
    }
}

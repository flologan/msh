#include <stdio.h>

#include "msh.h"

int main(void)
{
    printf("Welcome to the msh shell\n");
    return msh_loop();
}

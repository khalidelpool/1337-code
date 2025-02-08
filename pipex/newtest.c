#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int ac, char **av, char **envp) {
    int i;
    for (i = 0; envp[i] != NULL; i++)
    {
        printf("%s\n", envp[i]);
    } // test
}

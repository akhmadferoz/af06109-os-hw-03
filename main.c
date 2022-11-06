#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#include <sys/wait.h>

#include "parse/parse.h"
#include "prompt/prompt.h"


int main(int argc, char *argv[]) {
    displayPrompt();
    scanf("%s", argv[0]);

    while (1) {
        displayPrompt();
        scanf("%s", argv[0]);

        if (strcmp(argv[0], "exit") == 0) {
            printf("Terminating shell...\n");
            exit(0);
        }

        // if (strcmp(argv[0], "cd") == 0) {
        //     scanf("%s", argv[1]);
        //     chdir(argv[1]);
        // }

        // if (strcmp(argv[0], "pwd") == 0) {
        //     char buffer[1024];
        //     getcwd(buffer, sizeof(buffer));
        //     printf("%s \n", buffer);
        // }
    }
    
    return 0;
}
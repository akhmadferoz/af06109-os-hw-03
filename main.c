#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <unistd.h>

#include <sys/wait.h>

#include "parse/parse.h"
#include "prompt/prompt.h"

#define MAXLINE 81

// Function prototypes
char *readCommand(void);

// FUnction definitions
char *readCommand(void)
{
    char *command = malloc(MAXLINE);
    if (command == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (fgets(command, MAXLINE, stdin) == NULL)
    {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    return command;
}


int main(int argc, char *argv[]) {
    initPrompt();

    while (1) {
        displayPrompt();

        parseInfo *command = parse(readCommand());
        // print_info(command);

        if (strcmp(command -> CommArray -> command, "exit") == 0) {
            printf("\n\n!! Terminating shell...\n\n");
            exit(0);
        }

        int pid = fork();

        if (pid == 0) {
            execvp(command -> CommArray -> command, command -> CommArray -> VarList);
        } else {
            wait(NULL);
        }

    }
    
    return 0;
}
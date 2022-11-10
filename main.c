/*
 * References:
 * IBM C/C++ Documentation: https://www.ibm.com/docs/en
*/

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
        fprintf(stderr, "ERROR: Unable to allocate memory for command.\n");
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (fgets(command, MAXLINE, stdin) == NULL)
    {
        fprintf(stderr, "ERROR: Unable to read command.\n");
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    return command;
}


int main(int argc, char *argv[]) {
    initPrompt();


    while (1) {
        displayPrompt();

        char *rawCommand = readCommand();

        // continue if command is empty
        if (rawCommand == NULL || strcmp(rawCommand, "") == 0 || strcmp(rawCommand, "\n") == 0) {
            continue;
        }

        parseInfo *command = parse(rawCommand);
        print_info(command);

        // maintain a history of the last 10 commands
        // if the user enters !!, the last command is executed
        // if the user enters !n, the nth command is executed


        if (strcmp(command -> CommArray -> command, "exit") == 0) {
            printf("!! Terminating shell...\n");
            
            free(rawCommand);
            free_info(command);

            exit(EXIT_SUCCESS);
        }

        if (strcmp(command -> CommArray -> command, "help") == 0) {
            printf("cd [dir_path] .......... change directory\n");
            printf("help          .......... display help\n");

            continue;
        }

        if (strcmp(command -> CommArray -> command, "cd") == 0) {
            if (chdir(command -> CommArray -> VarList[1]) != 0) {
                fprintf(stderr, "ERROR: Unable to change directory.\n");
                perror("chdir");
            }

            continue;
        }

        int pid = fork();

        if(pid == -1) {
            fprintf(stderr, "ERROR: Unable to create fork\n");
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            execvp(command -> CommArray -> command, command -> CommArray -> VarList);
        } else {
            waitpid(pid, NULL, 0);
        }

        free(rawCommand);

    }
    
    return 0;
}
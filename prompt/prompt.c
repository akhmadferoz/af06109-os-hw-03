/******************************************************************************* 
 ******************************************************************************* 
 *   prompt.c  -  The propmt skeleton of your small shell                   
 *    
 *
 *   display a new prompt
 *
 *   Accepts: nothing
 *   Returns: nothing
 * 
 *******************************************************************************
 *******************************************************************************/
 #include <stdio.h>
#include <unistd.h>

#include "prompt.h"

/* -----------------------------------------------------------------------------
displayPrompt()
DESCRIPTION: Gets the current working directory and displays it as a prompt
-------------------------------------------------------------------------------*/
void displayPrompt() {
    char buffer[1024];

    getcwd(buffer, sizeof(buffer));
    printf("%s> ", buffer);
}
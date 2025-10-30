#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>    
#include <sys/wait.h>  
#include <stdio.h>    
#include <stdlib.h>

/**
 * Program that uses fork-exec to run grep and reports the results.
 * Takes a search word and filename as arguments.
 */
int main(int argc, const char* argv[]) {

    if (argc != 3) {
        printf("ERROR: No arguments\n");
        return 1;
    }
    
    const char* search_word = argv[1];
    const char* filename = argv[2];
    
    pid_t pid = fork();
    
    if (pid == -1) {
        
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        
        char* grep_args[] = {
            "grep",
            "-s",           
            "-q",          
            (char*)search_word,
            (char*)filename,
            NULL
        };
        
        execv("/usr/bin/grep", grep_args);
        
 
        perror("exec");
        exit(1);
    } else {
      
        int status;
        wait(&status);
        
        
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            
            if (exit_code == 0) {
             
                printf("FOUND: %s\n", search_word);
                return 0;
            } else if (exit_code == 1) {
        
                printf("NOT FOUND: %s\n", search_word);
                return 0;
            } else if (exit_code == 2) {
           
                printf("ERROR: %s doesn't exist\n", filename);
                return 2;
            } else {
     
                printf("ERROR: grep returned unexpected exit code %d\n", exit_code);
                return 1;
            }
        } else {
        
            printf("ERROR: grep process terminated abnormally\n");
            return 1;
        }
    }
    
    return 0;
}

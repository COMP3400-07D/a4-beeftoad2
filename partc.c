#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>    // For fork, execv
#include <sys/wait.h>  // For wait
#include <stdio.h>     // For printf
#include <stdlib.h>    // For exit

/**
 * Program that uses fork-exec to run grep and reports the results.
 * Takes a search word and filename as arguments.
 */
int main(int argc, const char* argv[]) {
    // Check if we have the correct number of arguments
    if (argc != 3) {
        printf("ERROR: No arguments\n");
        return 1;
    }
    
    const char* search_word = argv[1];
    const char* filename = argv[2];
    
    // Fork a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process: execute grep
        char* grep_args[] = {
            "grep",
            "-s",           // Suppress error messages
            "-q",           // Quiet mode (no output)
            (char*)search_word,
            (char*)filename,
            NULL
        };
        
        execv("/usr/bin/grep", grep_args);
        
        // If we reach here, execv failed
        perror("exec");
        exit(1);
    } else {
        // Parent process: wait for child to complete
        int status;
        wait(&status);
        
        // Check the exit status of grep
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            
            if (exit_code == 0) {
                // Found the pattern
                printf("FOUND: %s\n", search_word);
                return 0;
            } else if (exit_code == 1) {
                // Pattern not found
                printf("NOT FOUND: %s\n", search_word);
                return 0;
            } else if (exit_code == 2) {
                // File not found or other error
                printf("ERROR: %s doesn't exist\n", filename);
                return 2;
            } else {
                // Other error
                printf("ERROR: grep returned unexpected exit code %d\n", exit_code);
                return 1;
            }
        } else {
            // Child process didn't exit normally
            printf("ERROR: grep process terminated abnormally\n");
            return 1;
        }
    }
    
    return 0;
}

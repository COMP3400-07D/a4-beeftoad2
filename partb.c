#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>    
#include <stdio.h>    
#include <stdlib.h>    

/**
 * Program that uses exec system call to run echo with middle arguments.
 * For odd number of arguments: prints the middle argument
 * For even number of arguments: prints the middle 2 arguments
 */
int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        const char* error_msg = "ERROR: No arguments\n";
        write(STDERR_FILENO, error_msg, 20);
        return 1;
    }
    
   
    int num_args = argc - 1;

    int start_idx, end_idx;
    
    if (num_args % 2 == 1) {
        int mid = num_args / 2 + 1;
        start_idx = mid;
        end_idx = mid;
    } else {
        int mid1 = num_args / 2;      
        int mid2 = num_args / 2 + 1;
        start_idx = mid1;
        end_idx = mid2;
    }
    
    char* echo_argv[4];
    
    echo_argv[0] = "echo";
    int echo_idx = 1;

    for (int i = start_idx; i <= end_idx; i++) {
        echo_argv[echo_idx++] = (char*)argv[i];
    }

    echo_argv[echo_idx] = NULL;
    
   
    int eret = execv("/bin/echo", echo_argv);

    if (eret == -1) {
        perror("exec");
        return 1;
    }
    
    return 0;
}

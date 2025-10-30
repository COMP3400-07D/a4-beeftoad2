#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>  
#include <ctype.h>  

/**
 * Prints command line arguments with all alphabet letters capitalized,
 * separated by commas. If no arguments are provided, prints an error message.
 */
int main(int argc, const char* argv[]) {
    if (argc <= 1) {
        printf("ERROR: No arguments\n");
        return 1;
    }
    
    for (int i = 1; i < argc; i++) {
        if (i > 1) {
            printf(",");
        }
        
        const char* arg = argv[i];
        for (int j = 0; arg[j] != '\0'; j++) {
            printf("%c", toupper(arg[j]));
        }
    }
    
    printf("\n");
    
    return 0;
}

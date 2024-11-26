#include <stdio.h>
#include <string.h>

int main() {
    char string[50];
    int flag = 0, count = 0;

    printf("The grammar is: S -> aS | Sb | ab\n");
    printf("Enter the string to be checked:\n");
    fgets(string, sizeof(string), stdin);

    // Remove trailing newline from fgets
    size_t len = strlen(string);
    if (string[len - 1] == '\n') {
        string[len - 1] = '\0';
    }

    // Check if the string starts with 'a'
    if (string[0] == 'a') {
        flag = 0;
        for (count = 1; string[count] != '\0'; count++) {
            if (string[count] == 'b') {
                flag = 1; // Switch to the second part of the grammar
            } else if (flag == 1 && string[count] == 'a') {
                // If 'a' appears after 'b', the string is invalid
                printf("The string does not belong to the specified grammar.\n");
                return 1;
            } else if (string[count] != 'a' && string[count] != 'b') {
                // Invalid character in the string
                printf("The string does not belong to the specified grammar.\n");
                return 1;
            }
        }

        // Check if the string ends in 'b' (valid) or follows the rules
        if (flag == 1 && string[count - 1] == 'b') {
            printf("String accepted...!!!!\n");
        } else {
            printf("The string does not belong to the specified grammar.\n");
        }
    } else {
        printf("The string does not belong to the specified grammar.\n");
    }

    return 0;
}

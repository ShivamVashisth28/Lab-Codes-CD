#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char grm[20][20], c;

    int i, n, j, flag = 0;

    printf("Enter the number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions:\n");
    for (i = 0; i < n; i++)
        scanf("%s", grm[i]);

    for (i = 0; i < n; i++) {
        j = 2;
        c = grm[i][j];

        while (c != '\0') {
            if (c == '+' || c == '-' || c == '*' || c == '/') {
                flag = 1;
            } else if (c != 'A' && c != 'B' && c != '=') {
                flag = 0;
                printf("Not operator grammar\n");
                exit(0);
            }
            j++;
            c = grm[i][j];
        }
    }

    // If the flag is set to 1, it is an operator grammar
    if (flag == 1)
        printf("Operator grammar\n");

    return 0;
}

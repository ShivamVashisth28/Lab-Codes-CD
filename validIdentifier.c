#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char *str, int n){
    if(!(str[0] == '_' || 
        (str[0] >= 'a' && str[0] <= 'z') ||
        (str[0] >= 'A' && str[0] <= 'Z') 
        )){
            return false;
        }
    
    for(int i=1; i<n; i++){
        if(!(str[i] == '_' || 
        (str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= '0' && str[i] <= '9') 
        )){
            return false;
        }
    }

    return true;

}

int main(){
    char str[100];
    printf("Enter the string to check : \n");
    scanf("%99s",&str);
    
    int n = strlen(str);

    if(isValid(str,n)){
        printf("Valid");
    }else{
        printf("invalid");
    }

    return 0;
}
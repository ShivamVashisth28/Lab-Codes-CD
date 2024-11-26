#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isValid(char str[]){
    char keywords[32][10] = {
       "auto","break","case","const","continue","char","default","do",
       "double","enum","extern","else","float","for","goto","if",
       "int","long","return","register","switch","static","struct","signed",
       "short","sizeof","typedef","union","unsigned","volatile","void","while"
    };

    for(int i=0; i<32; i++){
        if(strcmp(str,keywords[i]) == 0){
            return true;
        }
    }

    return false;
}

int main(){
    char str[100];
    printf("Enter the string ");
    scanf("%99s",&str);
    if(isValid(str)){
        printf("Valid");
    }else{
        printf("In-Valid");
    }
    return 0;
}
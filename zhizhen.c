#include "stdio.h"
#include "string.h"
void stringConversion(char *world){
    for(int i = 0;i < strlen(world);i++){
        if(i==0 || *(world+i-1)==' ' || *(world+i-1)==','){
            if(*(world+i)>='a' && *(world+i)<='z'){
            printf("%c",*(world+i)-32);
        }else{
            printf("%c",*(world+i));
        }
    }else{
        if(*(world+i)>='A' && *(world+i)<='Z'){
            printf("%c",*(world+i)+32);
        }else{
            printf("%c",*(world+i));
        }
        }
    }
}
int main(){
    char *world = "hello,mY namY Is Me Fly sAnd";
    stringConversion(world);
}
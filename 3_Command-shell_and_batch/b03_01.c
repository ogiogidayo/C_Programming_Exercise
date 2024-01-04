#include<stdio.h>
#include<stdlib.h>

int factorial(int n){
    if(n == 0){
        return 1;
    }else{
        return n * factorial(n - 1);
    }
}

int main(int argc, char *argv[]){
    for (int i = 1; i < argc; i++){
        int n = atoi(argv[i]);
        printf("%d! = %d\n", n, factorial(n));
    }

    return 0;
}
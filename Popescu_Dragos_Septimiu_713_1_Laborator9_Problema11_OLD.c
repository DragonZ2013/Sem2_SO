#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
        int a[30];//holds argv (strings) as ints
        int i;//iterator
        int res = 0;//saves the result from one call to another
        int v;//keyboard input for Horner parameter
        for (i = 0; i < argc-1; i++){
                a[i] = atoi(argv[i+1]);//converts all argv's to int
        }

        printf("Enter a value of v:");
        scanf("%d",&v);//reads the Horner parameter

        
        for(i = argc-2; i >= 0; i--){
                if(fork()==0){//child process
                        res = a[i] + res * v;
                        printf("%d\n", res);
                        exit(res);//returns new (r) result
                }
                wait(&res);//reads new (r) result from child
                res = res/255;//modifies the exit value to correct return value 
        }


        return 0;

}


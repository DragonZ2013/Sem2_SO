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
                        FILE *f = fopen("temp_res","w");//opens the temporary file
			res = a[i] + res * v;
                        fprintf(f,"%d", res);
			printf("%d\n",res);
                        exit(0);//result is now in file
                }
                wait(&res);//no longer waits result from exit
		FILE *g = fopen("temp_res","r");
		fscanf(g,"%d",&res);
	}

        return 0;

}


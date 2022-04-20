#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>

int main()
{
    int pfdClient[2], pfdServer[2];
    //Client = parent, Server = child
    int pid, len;
    char buff[1000];
    //buffer for input-output
    if (pipe(pfdClient) < 0 || pipe(pfdServer) < 0)
    {//checks if pipes were created
        printf("Failed to create Pipe\n");
        exit(1);
    }
    if ((pid=fork()) < 0)
    {//checks if fork was created
        printf("Failed to create Fork\n");
        exit(1);
    }

    if (pid == 0)
    {
        close(pfdClient[1]); // close parent output
        close(pfdServer[0]); // close child input
        read(pfdClient[0], &len, sizeof(int));
        read(pfdClient[0], buff, len+1);
	dup2(pfdServer[1],1); //moves the console output to parent input
	char out_call[200]="find . -type f -name '";
	strcat(out_call,buff);
	char temp_call[200]="' | grep -o  \"\\(.*\\)/\" | sort -u";
	strcat(out_call,temp_call);
	//forms the system call string with the buffer
	system(out_call);
	//calls the system function and prints in console(parent input)
	//exclp("/bin/sh","sh","-c","find . -type f -name 'test_file1' | grep -o  "\(.*\)/" | sort -u", NULL);
        close(pfdClient[0]);
        close(pfdServer[1]);
	//closes remaining pipes
        exit(0);
    }
    else
    {
        close(pfdClient[0]);//closes parent input
        close(pfdServer[1]);//closes child output
        printf("Filename:\n");
        scanf("%s", buff);
        len = strlen(buff);
        write(pfdClient[1], &len, sizeof(int));//writes the length of the filename
        write(pfdClient[1], buff, len+1);//writes the filename(including \0)
	char new_buff[1000];//old buffer has remaining excess(could clear)
        read(pfdServer[0], &new_buff, sizeof(char)*1000);//reads the child output
	//can't get initial length of array since it tries to console print
        printf("%s",new_buff);//prints the given output
        close(pfdClient[1]);
        close(pfdServer[0]);
	//closes remaining pipes
        wait(0);
    }
    return 0;
}


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#define FIFO "fifo_in"
#define FIFO2 "fifo_out"
int main(){
int r_fifo, w_fifo;
char buf[100], buf1[100];
pid_t pid;
char puffer[200];

if ( (mkfifo (FIFO, S_IRUSR | S_IWUSR)) == -1) {//make fifo 1 read child,write parent
 if(errno == EEXIST)
 perror ("mkfifo()");
 else {
 perror("mkfifo()");
 exit (EXIT_FAILURE);
 }
}
if ( (mkfifo (FIFO2, S_IRUSR | S_IWUSR)) == -1) {//make fifo 2 read parent,write child
 if(errno == EEXIST)
 perror ("mkfifo()");
 else {
 perror("mkfifo()");
 exit (EXIT_FAILURE);
 }
}
 pid = fork();
 if (pid > 0) {//parent process
 if ((w_fifo = open (FIFO, O_WRONLY)) < 0 && (r_fifo = open(FIFO2,O_RDONLY)<0)) {
 perror ("open()");//opens fifo1 for write and fifo2 for read
 exit (EXIT_FAILURE);
 }
 printf("Filename:");
 scanf("%s", puffer);//keyboard input filename
 char clear_str[200];
 write (w_fifo, puffer, strlen (puffer));//sends filename to child
 wait(0);
 read(r_fifo,clear_str,strlen(clear_str));//reads system return from parent
 printf("%s",clear_str);
 
 close (w_fifo);
 close (r_fifo);//closes fifos
 exit (EXIT_SUCCESS);
 }

else {//child process
 if ((r_fifo = open (FIFO, O_RDONLY)) < 0&&(w_fifo=open(FIFO2,O_WRONLY)<0)){
 perror ("open()");//opens fifo1 for read and fifo2 for write
 exit (EXIT_FAILURE);
 }
 read (r_fifo, buf, 1000);//reads the filename from child
 char out_call[200]="file ";
 strcat(out_call,buf);
 dup2(w_fifo,1);//redirects console output to fifo
 system(out_call);
 close (r_fifo);
 close (w_fifo);//closes fifo files
 exit(0);
 }
 return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#define BUFFER_SIZE 4096
int main(int argc,char* argv[]){
	int inputFile=0,outputFile=0
    ssize_t numRead=0,numWrite=0;  //long int
    char buffer[BUFFER_SIZE];
    inputFile = open(argv[1],O_RDONLY);
    outputFile = open(argv[2],O_WRONLY |O_CREAT,S_IRWXU|S_IWUSR);
    if(inputFile ==-1) perror("Input data error");
    else if(outputFile==-1) perror("Output data error");
    else{
        while((numRead = read(inputFile,buffer,BUFFER_SIZE))>0){ //0 if the file is end
            numWrite = write(outputFile,buffer,numRead);
         //   printf("numRead = %d , numWrite = %d",(int)numRead,(int)numWrite);
            if(numWrite!=numRead) perror("numRead!=numWrite!");
        }

    }
    close(inputFile);
    close(outputFile);
    return 0;
}

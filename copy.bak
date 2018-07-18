#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

//只写，不存在则创建，长度截短为0，每次写到文件尾
#define WRITEFLASG O_WRONLY | O_CREAT | O_TRUNC | O_APPEND
//用户 读、写、执行 权限
#define WRITEMODE S_IRUSR | S_IWUSR | S_IXUSR

int main(int argc, char *argv[]){
    char *srcFileName, *destFileName;
    int srcFile, destFile;
    char buff[1024] = {0};  //读写buffer
    int nbytes = 1024;  //每次读取字节数
    int readSize;   //read返回字节数
    int writeSize;  //write返回字节数

    if(argc != 3){
        printf("require 2 arguments:<source_file> <destination_file>, got %d \n", argc-1);
    }

    srcFileName = *(argv+1);
    destFileName = *(argv+2);

    srcFile = open(srcFileName, O_RDONLY);
    if(srcFile == -1){
        printf("open file: %s failed!\n", srcFileName);
        return -1;
    }
    
    destFile = open(destFileName, WRITEFLASG, WRITEMODE);
    if(srcFile == -1){
        printf("create file: %s failed!\n", srcFileName);
        close(srcFile);
        return -1;
    }

    do{
        readSize = read(srcFile, buff, nbytes);
        if(readSize == -1){ //read errpr
            printf("read %s error, %d\n", srcFileName, readSize);
            close(srcFile);
            close(destFile);
            return -2;
        }else if(readSize){
            //printf("%s \n************** %d\n", buff, readSize);
            writeSize = write(destFile, buff, readSize);
            if(writeSize != readSize){
                printf("write %s error, %d\n", destFileName, writeSize);
                close(srcFile);
                close(destFile);
                return -3;
            }
        }
   }while(readSize == nbytes);

    close(srcFile);
    close(destFile);

    return 0;
}

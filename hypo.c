#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]){

    int n, fdw[2], fdr[2];
    char *a, *b;
    int lena, lenb;
    double c;
    char buff[100];
    int sqa, sqb;
    pid_t pid;
    FILE *fp;

    if(argc != 3){
        printf("usage: hypo <a> <b>\n");
        return -1;
    }

    a = argv[1];
    b = argv[2];

    lena = strlen(a) + 1;
    lenb = strlen(b) + 1;

    if(pipe(fdw) < 0 || pipe(fdr) < 0){
        printf("pipe erroe\n");
        return -2;
    }

    if( (pid = fork()) < 0){
        printf("fork error\n");
        return -3;
    }
    else if(pid > 0){
        //printf("pid %d\n", pid);
        close(fdw[0]);
        close(fdr[1]);

        //计算a平方
       if(write(fdw[1], a, lena) != lena){
           printf("write error to pipe\n");
           return -4;
       }
        n = read(fdr[0], buff, lena*2);
        if(n == 0){
            printf("read error from pipe\n");
            return -5;
        }
        sqa = atoi(buff);

        //计算b平方
        if(write(fdw[1], b, lenb) != lenb){
           printf("write error to pipe\n");
           return -4;
       }
        n = read(fdr[0], buff, lenb*2);
        if(n == 0){
            printf("read error from pipe\n");
            return -5;
        }
        sqb = atoi(buff);

        //计算斜边
        c = sqrt(sqa + sqb);
        printf("%.2f\n", c);

        if(waitpid(pid, NULL, 0) < 0){
            printf("waitpid error\n");
        }
        return 0;
    }else{
        //创建两个计算平方的进程
        if( (pid = fork()) < 0){
            printf("fork error\n");
            return -3;
        }

        close(fdw[1]);
        close(fdr[0]);
        //使标准输入成为读端
        if(fdw[0] != STDIN_FILENO){
            if(dup2(fdw[0], STDIN_FILENO) != STDIN_FILENO){
                printf("dup2 error to stdin\n");
                return -5;
            }
            close(fdw[0]);
        }
        //使标准输出成为写端
        if(fdr[1] != STDOUT_FILENO){
            if(dup2(fdr[1], STDOUT_FILENO) != STDOUT_FILENO){
                printf("dup2 error to stdout\n");
                return -5;
            }
            close(fdr[1]);
        }

        //调用test3
        if( execl("./test3", (char *)0) < 0){
            printf("execl error\n");
        }

        return 0;

    }
}

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main(){
 
    int result;
    
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    printf("socket: %d\n", fd);

    int val_on = 1;
    //result = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val_on, sizeof(int));
    //printf("setsockopt: %d\n", result);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(8000);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //result = bind(fd, NULL, NULL);
    //printf("bind: %d\n", result);

    //result = listen(fd, 128);
    //printf("result: %d\n", result);
    
    result = connect(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    printf("connect: %d\n", result);

    char buff[1024];
    int slen;
    int num = 10;
    while(1){
        num = rand()%100 + 1;
        memset(buff, 0, sizeof(buff));
        sprintf(buff, "%d\n", num);
        slen = send(fd, buff, strlen(buff), 0);
        printf("send: %s", buff);

        memset(buff, 0, sizeof(buff));
        slen = recv(fd, buff, sizeof(buff), 0);
        printf("recv: %s\n", buff);


        sleep(1);
    }

    result = shutdown(fd, SHUT_RDWR);
    printf("shutdown: %d\n", result);

    return 0;
}
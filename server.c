#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
 
    int result;
    
    int fd;
    fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    printf("socket: %d\n", fd);

    int val_on = 1;
    result = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val_on, sizeof(int));
    printf("setsockopt: %d\n", result);

    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(8000);
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    result = bind(fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    printf("bind: %d\n", result);

    result = listen(fd, 128);
    printf("listen: %d\n", result);

    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    int conn;
    conn = accept(fd, (struct sockaddr *)&client_addr, &len);
    printf("accept: %d\n", conn);

    char sendbuf[128];
    char recvbuf[128];
    int slen;
    int num;
    while(1){
        memset(recvbuf, 0, sizeof(recvbuf));
        slen = recv(conn, recvbuf, sizeof(recvbuf), 0);
        if(slen == 0){
            break;
        }
        printf("recv: %s", recvbuf);

        num = atoi(recvbuf);

        num = num * num;
        memset(sendbuf, 0, sizeof(sendbuf));
        sprintf(sendbuf, "%d\n", num);
        slen = send(conn, sendbuf, strlen(sendbuf), 0);
        printf("send: %s\n", sendbuf);



    }

    result = shutdown(fd, SHUT_RDWR);
    printf("shutdown: %d\n", result);

    return 0;
}
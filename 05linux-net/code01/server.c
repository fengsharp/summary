#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void err_exit(const char * msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenfd < 0)
        err_exit("create socket");
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        err_exit("bind");
    
    if (listen(listenfd, SOMAXCONN) < 0)
        err_exit("listen");

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr);
    int connfd = accept(listenfd, (struct sockaddr *)&peeraddr, &peerlen);
    if (connfd < 0) 
        err_exit("accept");
    printf(" -> id = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

    char recvbuf[BUFSIZ];
    while (1)
    {
        memset(recvbuf, 0, BUFSIZ);
        int ret = read(connfd, recvbuf, BUFSIZ);
        if (ret == 0)
        {
            printf("=== client close.\n");
            close(connfd);
            break;
        }
        else if (ret > 0)
        {
            printf("receive: %s\n", recvbuf);
            write(connfd, recvbuf, ret);
        }
        else
        {
            err_exit("read");
        }
    }

    close(listenfd);
    
    return 0;
}
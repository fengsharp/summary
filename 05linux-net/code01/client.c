#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0)
        err_exit("create socket");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        err_exit("connect");

    char recvbuf[BUFSIZ] = {'\0'};
    char sendbuf[BUFSIZ] = {'\0'};
    while (fgets(sendbuf, BUFSIZ, stdin) != NULL)
    {
        write(sockfd, sendbuf, strlen(sendbuf) - 1);
        int ret = read(sockfd, recvbuf, BUFSIZ);
        if (ret == 0)
        {
            printf("=== server close.\n");
            close(sockfd);
            break;
        }
        else if (ret > 0)
        {
            printf(" ->: %s\n", recvbuf);
        }
        else
        {
            err_exit("read");
        }

        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }

    return 0;
}
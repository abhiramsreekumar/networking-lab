#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(void) {
    int sockfd, csock;
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsz = sizeof(caddr);
    char buf[2000] = {'\0'};
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(sockfd, 1);
    csock = accept(sockfd, (struct sockaddr *)&caddr, &caddrsz);
    for (;;) {
        bzero(buf, sizeof(buf));
        recv(csock, buf, sizeof(buf), 0);
        printf("CLIENT: %s\n", buf);
        bzero(buf, sizeof(buf));
        scanf("%s", buf);
        if (!strcmp(buf, "x"))
            break;
        send(csock, buf, sizeof(buf), 0);
    }
    close(csock);
    close(sockfd);
    return 0;
}

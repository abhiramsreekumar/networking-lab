#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(void) {
    int sockfd;
    struct sockaddr_in saddr;
    char buf[2000] = {'\0'};
    sockfd = socket(AF_INET, SOCK_STREAM, 0)
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr))
    for (;;) {
        bzero(buf, sizeof(buf));
        scanf("%s", buf);
        if (!strcmp(buf, "x"))
            break;
        send(sockfd, buf, sizeof(buf), 0)
        recv(sockfd, buf, sizeof(buf), 0)
        printf("SERVER: %s\n", buf);
    }
    close(sockfd);
    return 0;
}

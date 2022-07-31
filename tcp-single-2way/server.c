#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define CHECK(expr)                                                            \
    if ((expr) < 0)                                                            \
        return -1;                                                             \
    else                                                                       \
        printf("%s;\n", #expr);

int main(void) {
    int sockfd, csock;
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsz = sizeof(caddr);
    char buf[2000] = {'\0'};
    CHECK(sockfd = socket(AF_INET, SOCK_STREAM, 0))
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    CHECK(bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)))
    CHECK(listen(sockfd, 1))
    CHECK(csock = accept(sockfd, (struct sockaddr *)&caddr, &caddrsz))
    for (;;) {
        bzero(buf, sizeof(buf));
        CHECK(recv(csock, buf, sizeof(buf), 0))
        printf("CLIENT: %s\n", buf);
        bzero(buf, sizeof(buf));
        scanf("%s", buf);
        if (!strcmp(buf, "x"))
            break;
        CHECK(send(csock, buf, sizeof(buf), 0))
    }
    close(csock);
    close(sockfd);
    return 0;
}

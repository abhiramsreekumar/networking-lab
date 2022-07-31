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
    for (;;) {
        CHECK(csock = accept(sockfd, (struct sockaddr *)&caddr, &caddrsz))
        CHECK(recv(csock, buf, sizeof(buf), 0))
        char *ipaddr = inet_ntoa(caddr.sin_addr);
        int portnum = ntohs(caddr.sin_port);
        printf("CLIENT@%s:%d :: %s\n", ipaddr, portnum, buf);
        char *hello = "HELLO FROM SERVER";
        CHECK(send(csock, hello, strlen(hello), 0))
    }
    close(csock);
    close(sockfd);
    return 0;
}

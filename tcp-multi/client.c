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
    int sockfd;
    struct sockaddr_in saddr;
    char buf[2000] = {'\0'};
    CHECK(sockfd = socket(AF_INET, SOCK_STREAM, 0))
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    CHECK(connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)))
    char *hello = "HELLO FROM CLIENT";
    CHECK(send(sockfd, hello, strlen(hello), 0))
    CHECK(recv(sockfd, buf, sizeof(buf), 0))
    printf("SERVER: %s\n", buf);
    sleep(1000);
    close(sockfd);
    return 0;
}

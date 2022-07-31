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
    socklen_t saddrsz = sizeof(saddr);
    char buf[2000] = {'\0'};
    CHECK(sockfd = socket(AF_INET, SOCK_DGRAM, 0))
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char *hello = "HELLO FROM CLIENT";
    CHECK(sendto(sockfd, hello, strlen(hello), MSG_CONFIRM,
                 (struct sockaddr *)&saddr, sizeof(saddr)));
    CHECK(recvfrom(sockfd, (char *)buf, sizeof(buf), MSG_WAITALL,
                   (struct sockaddr *)&saddr, &saddrsz));
    printf("SERVER: %s\n", buf);
    sleep(1000);
    close(sockfd);
    return 0;
}

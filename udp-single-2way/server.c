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
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsz = sizeof(caddr);
    char buf[2000] = {'\0'};
    CHECK(sockfd = socket(AF_INET, SOCK_DGRAM, 0))
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    CHECK(bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)))
    for (;;) {
        bzero(buf, sizeof(buf));
        CHECK(recvfrom(sockfd, (char *)buf, sizeof(buf), MSG_WAITALL,
                       (struct sockaddr *)&caddr, &caddrsz));
        printf("CLIENT: %s\n", buf);
        bzero(buf, sizeof(buf));
        scanf("%s", buf);
        if (!strcmp(buf, "x"))
            break;
        CHECK(sendto(sockfd, buf, sizeof(buf), MSG_CONFIRM,
                     (struct sockaddr *)&caddr, sizeof(caddr)));
    }
    close(sockfd);
    return 0;
}

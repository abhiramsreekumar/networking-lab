#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFSZ 32
#define FLAG 0
#define CHECK(expr)                                                            \
    if ((expr) < 0)                                                            \
        return -1;                                                             \
    else                                                                       \
        printf("%s;\n", #expr);

int recvFile(char *buf, int s) {
    char ch;
    for (int i = 0; i < s; i++)
        if ((ch = buf[i]) == EOF)
            return 1;
        else
            printf("%c", ch);
    return 1;
}

int main() {
    int sockfd;
    struct sockaddr_in saddr;
    socklen_t addrlen = sizeof(saddr);
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(3333);
    saddr.sin_addr.s_addr = INADDR_ANY;
    char buf[BUFSZ] = {'\0'};
    CHECK(sockfd = socket(AF_INET, SOCK_DGRAM, 0));
    while (1) {
        printf("\nPlease enter file name to receive: ");
        scanf("%s", buf);
        CHECK(sendto(sockfd, buf, BUFSZ, FLAG, (struct sockaddr *)&saddr,
                     addrlen));
        printf("\n---------Data Received---------\n");
        while (1) {
            bzero(buf, sizeof(buf));
            CHECK(recvfrom(sockfd, buf, BUFSZ, FLAG, (struct sockaddr *)&saddr,
                           &addrlen));
            if (recvFile(buf, BUFSZ))
                break;
        }
        printf("\n-------------------------------\n");
    }
    return 0;
}

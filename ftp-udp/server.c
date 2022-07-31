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

int sendFile(FILE *fp, char *buf, int s) {
    int i = 0;
    if (fp == NULL) {
        strcpy(buf, "File Not Found!");
        return 1;
    }
    while (!feof(fp))
        buf[i++] = fgetc(fp);
    return 1;
}

int main() {
    int sockfd;
    struct sockaddr_in caddr;
    socklen_t addrlen = sizeof(caddr);
    caddr.sin_family = AF_INET;
    caddr.sin_port = htons(3333);
    caddr.sin_addr.s_addr = INADDR_ANY;
    char buf[BUFSZ] = {'\0'};
    FILE *fp;
    CHECK(sockfd = socket(AF_INET, SOCK_DGRAM, 0));
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    CHECK(bind(sockfd, (struct sockaddr *)&caddr, sizeof(caddr)));
    for (;;) {
        printf("Waiting for filename...\n");
        bzero(buf, sizeof(buf));
        CHECK(recvfrom(sockfd, buf, BUFSZ, FLAG, (struct sockaddr *)&caddr,
                       &addrlen));
        printf("File Name Received: %s", buf);
        ((fp = fopen(buf, "r")) == NULL) ? printf(" (ERR)\n")
                                         : printf(" (OPN)\n");
        for (;;) {
            if (sendFile(fp, buf, BUFSZ)) {
                CHECK(sendto(sockfd, buf, BUFSZ, FLAG,
                             (struct sockaddr *)&caddr, addrlen));
                break;
            }
            bzero(buf, sizeof(buf));
        }
        if (fp != NULL)
            fclose(fp);
    }
    return 0;
}

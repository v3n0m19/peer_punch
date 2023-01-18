#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAXLINE 1024
typedef struct
{
    int sockfd;
    struct sockaddr_in servaddr;
} func_args;

void *send_msg(void *args)
{
    func_args *ac_args=args;
    int sockfd=ac_args->sockfd;
    struct sockaddr_in servaddr=ac_args->servaddr;
    char msg[1024];
    while (1)
    {   
        memset(&msg, 0, sizeof(msg));
        printf("Sender : ");
        scanf("%s", msg);
        sendto( sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    }
}
void *recv_msg(void *args)
{
    
    func_args *ac_args=args;
    int sockfd=ac_args->sockfd;
    struct sockaddr_in servaddr=ac_args->servaddr;
    int n, len;
    char buffer[1024];
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, (socklen_t *)&len);
        printf("\t Reciever: %s",buffer);
        // buffer[n] = '\0';
        // puts(buffer);
        // printf("\n");

    }
}
int client_func(int sockfd, char ip_addr[], int port)
{

    char buffer[MAXLINE];

    struct sockaddr_in servaddr;
    // Creating socket file descriptor
    // if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    // {
    // 	perror("socket creation failed");
    // 	exit(EXIT_FAILURE);
    // }
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);
    int n, len;
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }

    pthread_t threads[2];

    func_args *args = malloc(sizeof *args);
    args->sockfd = sockfd;
    args->servaddr = servaddr;

    int rc1 = pthread_create(&threads[0], NULL, send_msg, (void *)args);
    if (rc1)
    {
        printf("ERROR; return code from pthread_create() is %d\n", rc1);
        exit(-1);
    }
    int rc2 = pthread_create(&threads[1], NULL, recv_msg, (void *)args);
    if (rc2)
    {
        printf("ERROR; return code from pthread_create() is %d\n", rc2);
        exit(-1);
    }
    int ret1 = pthread_join(threads[0],NULL);
    int ret2 = pthread_join(threads[1],NULL);
    // buffer[n] = '\0';
    // printf("Server : %s\n", buffer);
    // close(sockfd);
    return 0;
}
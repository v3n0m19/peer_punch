#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <ncurses.h>

#define MAXLINE 1024
#define MAXSIZE 1024

typedef struct
{
    int sockfd;
    struct sockaddr_in servaddr;
    WINDOW *ibox;
    WINDOW *sbox;
    WINDOW *rbox;
} func_args;

void *send_msg(void *args)
{
    func_args *ac_args = args;//typecasted here use ac_args moron developer :)
    int sockfd = ac_args->sockfd;
    struct sockaddr_in servaddr = ac_args->servaddr;

    WINDOW * input_box = ac_args->ibox;
    WINDOW * sender_box = ac_args->sbox; 
    int line_count=1;
    char msg[MAXSIZE];
    while (1)
    {
        memset(&msg, 0, sizeof(msg));
        // printf("Sender : ");
        // scanf("%s",msg);

        mvwgetstr(input_box,1,1,msg);
        wmove(input_box,1,1);
        wclrtoeol(input_box);
        wrefresh(input_box);
        mvwprintw(sender_box,line_count,1,msg);
        wmove(input_box,1,1);
        wrefresh(sender_box);
        refresh(); //dal diya bas
        line_count++;

        sendto(sockfd, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    }
}
void *recv_msg(void *args)
{

    func_args *ac_args = args;
    int sockfd = ac_args->sockfd;
    struct sockaddr_in servaddr = ac_args->servaddr;
    int n, len, lc=1;
    WINDOW * reciever_box = ac_args->rbox;
    char buffer[MAXSIZE];
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, (socklen_t *)&len);
        // printf("\t Reciever: %s", buffer);
    
        mvwprintw(reciever_box,lc,1,buffer);
        wrefresh(reciever_box);
        lc++;
    
    }
}
int client_func(int sockfd, char ip_addr[], int port,WINDOW* ibox, WINDOW* sbox, WINDOW* rbox)
{

    char buffer[MAXLINE];

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr(ip_addr);
    int n, len;
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }

    pthread_t threads[2];

    func_args *args = malloc(sizeof *args);
    args->sockfd = sockfd;
    args->servaddr = servaddr;

    args->ibox=ibox;
    args->sbox=sbox;
    args->rbox=rbox;

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
    int ret1 = pthread_join(threads[0], NULL);
    int ret2 = pthread_join(threads[1], NULL);
    return 0;
}
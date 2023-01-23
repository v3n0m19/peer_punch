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
#include <time.h>
#define MAXLINE 1024
#define MAXSIZE 1024


int tcp_func(int sockfd, char ip_addr[], int port, WINDOW *ibox, WINDOW *sbox, WINDOW *rbox);

typedef struct
{
    int sockfd;
    struct sockaddr_in address;
    WINDOW *ibox;
    WINDOW *sbox;
    WINDOW *rbox;
} tcp_func_args;

void *send_m(void *args)
{
    tcp_func_args *ac_args = args; // typecasted here use ac_args moron developer :)
    int sockfd = ac_args->sockfd;
    struct sockaddr_in servaddr = ac_args->address;

    WINDOW *input_box = ac_args->ibox;
    WINDOW *sender_box = ac_args->sbox;
    int line_count = 1;
    char msg[MAXSIZE];

    while (1)
    {
        memset(&msg, 0, sizeof(msg));

        mvwgetstr(input_box, 1, 1, msg);
        int exit_count=0;
        for (int i = 0; i < 9; i++){if (msg[i] == exit_str[i])exit_count++;}
        if(exit_count==9){sendto(sockfd, (const char *)exit_msg, strlen(exit_msg), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));erase();refresh();exit(0);}
      

        wmove(input_box, 1, 1);
        wclrtoeol(input_box);
        wrefresh(input_box);
        // mvwprintw(sender_box, line_count, 1, msg);
        wmove(input_box, 1, 1);
        wrefresh(sender_box);
        refresh(); // dal diya bas
        line_count++;
        send(sockfd, msg, strlen(msg), 0);
    }
}
void *recv_m(void *args)
{

    tcp_func_args *ac_args = args;
    int sockfd = ac_args->sockfd;
    struct sockaddr_in servaddr = ac_args->address;
    int rec, len, lc = 1;
    WINDOW *reciever_box = ac_args->rbox;
    WINDOW *input_box = ac_args->ibox;
    char buffer[MAXSIZE];
    while (1)
    {
        memset(&buffer, 0, sizeof(buffer));
        rec = recv(sockfd, buffer,MAXLINE, 0);
        // printf("\t Reciever: %s", buffer);
        mvwprintw(reciever_box, lc, 1, buffer);
        wrefresh(reciever_box);
        lc++;
        
    }
    wrefresh(input_box);
    wrefresh(reciever_box);
    refresh();
}
void *accept_thr(void *args)
{
    tcp_func_args *ac_args = args;
    int sockfd;
    struct sockaddr_in address = ac_args->address;
    sockfd = ac_args->sockfd;
    int addrlen = sizeof(address);
    int accept_fd[50], i = 0;
    while (1)
        listen(sockfd, 100);
    accept_fd[i] = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    // while (1)
    // {
    //     listen(sockfd, 100);
    //     // if ((accept_fd[i] = accept(sockfd,(struct sockaddr *)&address,(socklen_t *)&addrlen)) > 0)
    //     // {
    //     //     i++;
    //     // }
    // }
}

int tcp_func(int stun_sockfd, char ip_addr[], int port, WINDOW *ibox, WINDOW *sbox, WINDOW *rbox)
{

    pthread_t threads[3];
    // client side
    int cli_sockfd = 0, server_sockfd = 0;
    struct sockaddr_in cli_addr, srv_addr;

    
    cli_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(cli_sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

    cli_addr.sin_family = AF_INET;
    cli_addr.sin_port = htons(port);
    cli_addr.sin_addr.s_addr = inet_addr(ip_addr);
    wprintw(ibox,"1");
    int x = bind(cli_sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
    wprintw(ibox,"2");
    // server side

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = INADDR_ANY;
    srv_addr.sin_port = htons(port);
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    wprintw(ibox,"3");
    int y = bind(server_sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
    wprintw(ibox,"4");
    tcp_func_args *args = malloc(sizeof(*args));
    args->sockfd = server_sockfd;
    args->address = srv_addr;
    args->ibox = ibox;
    args->rbox = rbox;
    args->sbox = sbox;
    wprintw(ibox,"5");
    // int accept_t = pthread_create(&threads[0], NULL, accept_thr, args);
    
    listen(server_sockfd,5);
    int adlen=sizeof(srv_addr);
    int acceptfd =accept(server_sockfd, (struct sockaddr *)&srv_addr, (socklen_t *)& adlen);
    wprintw(ibox,"6");
    // client connect

    connect(cli_sockfd, (struct sockaddr *)&cli_addr, sizeof(cli_addr));

    char con_msg[20]="connection made";
    send(cli_sockfd, con_msg, strlen(con_msg), 0);
    char con_recv[20];
    recv(cli_sockfd, con_recv, 20, 0);
    mvwprintw(sbox, 1, 1, con_recv);
    wrefresh(sbox);


    wprintw(ibox,"7");

    tcp_func_args *cliargs = malloc(sizeof(*args));
    cliargs->sockfd = cli_sockfd;
    cliargs->address = cli_addr;
    cliargs->ibox = ibox;
    cliargs->rbox = rbox;
    cliargs->sbox = sbox;
    wmove(ibox,1,1);
    wrefresh(ibox);
    refresh();  
    int st = pthread_create(&threads[1], NULL, send_m, cliargs);
    int rt = pthread_create(&threads[2], NULL, recv_m, cliargs);

    // int at = pthread_join(threads[0], NULL);
    int st1 = pthread_join(threads[1],NULL);
    int rt1 = pthread_join(threads[2],NULL);


}
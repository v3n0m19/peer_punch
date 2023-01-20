#include "stun.h"
#include "client.h"
#include <string.h>
int main()
{

    char ip_address[50];
    int port_num;
    struct stun_info s1;
    s1=stun_in();
    printf("%s:%d\n",s1.ip, s1.port,s1.sockfd);
    printf("Enter ip address : ");
    scanf("%s",ip_address);
    printf("Enter port : ");
    scanf("%d",&port_num);
        initscr();
    cbreak();

    int ymax,xmax;
    getmaxyx(stdscr,ymax,xmax);
    WINDOW *input_box = newwin(4,xmax-12,ymax-6,6);
    box(input_box,0,0);
    refresh();
    wrefresh(input_box);
    
    
    WINDOW *sender_box = newwin(ymax-6,(xmax-12)/2,0,6);
    box(sender_box,0,0);
    refresh();
    wrefresh(sender_box);
    
    WINDOW *reciever_box = newwin(ymax-6,(xmax-12)/2,0,6+(xmax-12)/2);
    box(reciever_box,0,0);
    refresh();
    wrefresh(reciever_box);
    
    client_func(s1.sockfd,ip_address,port_num,input_box,sender_box,reciever_box);
}
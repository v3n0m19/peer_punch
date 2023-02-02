#include"include/peer_punch.h"
void print_image(FILE *fptr);
int main()
{
    char exit_phrase[100]="In order to exit type the phrase 'EXIT_CHAT' in the message box";
    char ip_address[50];
    int port_num;
    int choice = 0;
    struct stun_info s1;
    char *fname = "assets/logo.txt";
    FILE *fptr = NULL;
    if((fptr = fopen(fname,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",fname);
        return 1;
    }
    print_image(fptr);
    
    s1=udp_stun();

    printf("\033[0;33m");
    printf("\nPublic IP:  %s\nPublic port: %d\n",s1.ip, s1.port,s1.sockfd);
    printf("\033[0m");
    printf("\nEnter recievers public IPv4 address : ");
    scanf("%s",ip_address);
    printf("Enter port : ");
    scanf("%d",&port_num);
    
    initscr();
    cbreak();

    int ymax,xmax;
    getmaxyx(stdscr,ymax,xmax);
    WINDOW *input_box = newwin(3,xmax-12,ymax-5,6);
    box(input_box,0,0);
    refresh();
    wrefresh(input_box);
    wattron(stdscr,A_REVERSE);
    mvwprintw(stdscr,0,7,"SENDER");
    mvwprintw(stdscr,0,120,"RECIEVER");
    wattroff(stdscr,A_REVERSE);

    
    WINDOW *sender_box = newwin(ymax-6,(xmax-12)/2,1,6);
    box(sender_box,0,0);
    refresh();
    wrefresh(sender_box);
    
    WINDOW *reciever_box = newwin(ymax-6,(xmax-12)/2,1,6+(xmax-12)/2);
    box(reciever_box,0,0);
    wattron(stdscr,A_REVERSE);
    mvwprintw(stdscr,ymax-2,6,exit_phrase);
    wattroff(stdscr,A_REVERSE);
    move(ymax-4,7);
    wrefresh(input_box);
    refresh();
    wrefresh(reciever_box);

    udp_func(s1.sockfd,ip_address,port_num,input_box,sender_box,reciever_box);

    fclose(fptr);
    endwin();
}
void print_image(FILE *fptr)
{
    char read_string[MAX_L];
    printf("\033[0;31m"); 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
    printf("\033[0m"); 
}
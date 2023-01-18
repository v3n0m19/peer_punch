#include "stun.h"
#include "client.h"
#include <string.h>
int main()
{
    char ip_address[50];
    int port_num;
    struct stun_info s1;
    s1=stun_in();
    printf("%s:%d\nsockfd=%d",s1.ip, s1.port,s1.sockfd);
    printf("Enter ip address : ");
    scanf("%s",ip_address);
    printf("Enter port : ");
    scanf("%d",&port_num);
    client_func(s1.sockfd,ip_address,port_num);
}
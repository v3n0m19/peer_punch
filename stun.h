#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAXLINE 200
struct stun_info{
    char ip[50];
    int port;
    int sockfd;
    int error;
};

struct stun_info stun_in();


// int main(int argc, char *argv[])
// {

// 	struct stun_info n; 
// 	n = stun("74.125.197.127",19302,55555);
// 	if (n.error!=0)
//                 printf("STUN req error : %d\n",n);
//         else
//                 printf("ip:port = %s:%d\n",n.ip,n.port);

// 	printf("Main over.\n");

// }

struct stun_info stun_in()
{
	char *stun_server_ip = "74.125.197.127";
	int stun_server_port = 19302;
	int local_port = 55555;
    struct stun_info s1;
	struct sockaddr_in servaddr;
	struct sockaddr_in localaddr;
	unsigned char buf[MAXLINE];
	int sockfd, i;
        unsigned char bindingReq[20];    

	int stun_method,msg_length;
	short attr_type;
	short attr_length;
	int port;
	short n;


        //# create socket 
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); // UDP
    s1.sockfd=sockfd;
	// server 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, stun_server_ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(stun_server_port);
    
	// local
	bzero(&localaddr, sizeof(localaddr));
        localaddr.sin_family = AF_INET;
        //inet_pton(AF_INET, "192.168.0.181", &localaddr.sin_addr);
        localaddr.sin_port = htons(local_port);

	n = bind(sockfd,(struct sockaddr *)&localaddr,sizeof(localaddr));
	//printf("bind result=%d\n",n);

        printf("socket opened to  %s:%d  at local port %d\n",stun_server_ip,stun_server_port,local_port);

        //## first bind 
	* (short *)(&bindingReq[0]) = htons(0x0001);    // stun_method
	* (short *)(&bindingReq[2]) = htons(0x0000);    // msg_length
	* (int *)(&bindingReq[4])   = htonl(0x2112A442);// magic cookie

	*(int *)(&bindingReq[8]) = htonl(0x63c7117e);   // transacation ID 
	*(int *)(&bindingReq[12])= htonl(0x0714278f);
	*(int *)(&bindingReq[16])= htonl(0x5ded3221);



        printf("Send data ...\n");
        n = sendto(sockfd, bindingReq, sizeof(bindingReq),0,(struct sockaddr *)&servaddr, sizeof(servaddr)); // send UDP
	if (n == -1)
        {
            printf("sendto error\n");
            s1.error=-1;
        }
	sleep(1);

        printf("Read recv ...\n");
        n = recvfrom(sockfd, buf, MAXLINE, 0, NULL,0); // recv UDP
        if (n == -1)
	{
	    printf("recvfrom error\n");
	    s1.error=-2;
	}

	if (*(short *)(&buf[0]) == htons(0x0101))
	{
		// parse XOR
		n = htons(*(short *)(&buf[2]));
		i = 20;
        	while(i<sizeof(buf))
       	 	{
                	attr_type = htons(*(short *)(&buf[i]));
			attr_length = htons(*(short *)(&buf[i+2]));
			if (attr_type == 0x0020)
			{
				port = ntohs(*(short *)(&buf[i+6]));
				port ^= 0x2112;
				sprintf(s1.ip,"%d.%d.%d.%d",buf[i+8]^0x21,buf[i+9]^0x12,buf[i+10]^0xA4,buf[i+11]^0x42);
                s1.port=port;
				break;
			}
			i += (4  + attr_length);
        	}
	}
        // TODO: bind again 

	// close(sockfd);
    //     printf("socket closed !\n");


	// return sockfd;
    return s1;
}
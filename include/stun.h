struct stun_info{
    char ip[50];
    int port;
    int sockfd;
    int error;
};

struct stun_info udp_stun();
struct stun_info tcp_stun();

struct stun_info udp_stun()
{
	char *stun_server_ip = "74.125.197.127";
	int stun_server_port = 19302;
	int local_port = 60001;
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

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    s1.sockfd=sockfd;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, stun_server_ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(stun_server_port);
	bzero(&localaddr, sizeof(localaddr));
        localaddr.sin_family = AF_INET;
        localaddr.sin_port = htons(local_port);

	n = bind(sockfd,(struct sockaddr *)&localaddr,sizeof(localaddr));

    printf("\nSocket opened to  %s:%d  at local port %d\n",stun_server_ip,stun_server_port,local_port);

	* (short *)(&bindingReq[0]) = htons(0x0001);    
	* (short *)(&bindingReq[2]) = htons(0x0000);    
	* (int *)(&bindingReq[4])   = htonl(0x2112A442);

	*(int *)(&bindingReq[8]) = htonl(0x63c7117e);    
	*(int *)(&bindingReq[12])= htonl(0x0714278f);
	*(int *)(&bindingReq[16])= htonl(0x5ded3221);



        n = sendto(sockfd, bindingReq, sizeof(bindingReq),0,(struct sockaddr *)&servaddr, sizeof(servaddr)); // send UDP
	if (n == -1)
        {
            printf("sendto error\n");
            s1.error=-1;
        }
	sleep(1);
        n = recvfrom(sockfd, buf, MAXLINE, 0, NULL,0); 
        if (n == -1)
	{
	    printf("recvfrom error\n");
	    s1.error=-2;
	}

	if (*(short *)(&buf[0]) == htons(0x0101))
	{
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
    return s1;
}

struct stun_info tcp_stun()
{
	char *stun_server_ip = "18.191.223.12";
	int stun_server_port = 3478;
	int local_port = 50001;
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

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    s1.sockfd=sockfd;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, stun_server_ip, &servaddr.sin_addr);
	servaddr.sin_port = htons(stun_server_port);
	bzero(&localaddr, sizeof(localaddr));
        localaddr.sin_family = AF_INET;
        localaddr.sin_port = htons(local_port);

	n = bind(sockfd,(struct sockaddr *)&localaddr,sizeof(localaddr));

	connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Socket opened to  %s:%d  at local port %d\n",stun_server_ip,stun_server_port,local_port);

	* (short *)(&bindingReq[0]) = htons(0x0001);    
	* (short *)(&bindingReq[2]) = htons(0x0000);    
	* (int *)(&bindingReq[4])   = htonl(0x2112A442);

	*(int *)(&bindingReq[8]) = htonl(0x63c7117e);    
	*(int *)(&bindingReq[12])= htonl(0x0714278f);
	*(int *)(&bindingReq[16])= htonl(0x5ded3221);



        // n = sendto(sockfd, bindingReq, sizeof(bindingReq),0,(struct sockaddr *)&servaddr, sizeof(servaddr)); 
		n= send(sockfd, bindingReq, sizeof(bindingReq), 0);
	if (n == -1)
        {
            printf("sendto error\n");
            s1.error=-1;
        }
	sleep(1);
        // n = recvfrom(sockfd, buf, MAXLINE, 0, NULL,0); 
		n=recv(sockfd, buf, MAXLINE, 0);
        if (n == -1)
	{
	    printf("recvfrom error\n");
	    s1.error=-2;
	}

	if (*(short *)(&buf[0]) == htons(0x0101))
	{
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
    return s1;
}




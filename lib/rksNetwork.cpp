#include "../include/rksNetwork.h"

int rksIpv4_StreamTcp:: setBuffer(int size)
{
    sendBuffer = new char[MAXLINE];  
    recvBuffer = new char[MAXLINE];
    return 0;
}

int rksIpv4_StreamTcp:: setSocket()
{
    if( (sockfd = socket(protofamily,type, protocol)) < 0)
    {  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }
    return 0;
}  

int rksIpv4_StreamTcp::setAddress_Port( int p, string addressString)
{
    port = p;
    memset(&servaddr_ipv4, 0, sizeof(servaddr_ipv4));  
    servaddr_ipv4.sin_family = protofamily;  
    servaddr_ipv4.sin_port = htons(port);  
    if( inet_pton(protofamily, addressString.c_str(), &servaddr_ipv4.sin_addr) <= 0)
    {  
        printf("inet_pton error for %s\n",addressString.c_str());  
        exit(0);  
    }
    return 0;
}

int rksIpv4_StreamTcp:: rksBind()
{
    if( isServer == true)
    {
        return 0;
    }
}

int rksIpv4_StreamTcp:: rksConnect()
{
    if( connect(sockfd, (struct sockaddr*)&servaddr_ipv4, sizeof(servaddr_ipv4)) < 0)   
    {  
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    return 0;
}


int rksIpv4_StreamTcp::rksSend()
{
    printf("send msg to server: \n");  
    fgets(sendBuffer, MAXLINE, stdin);
    if( send(sockfd, sendBuffer, strlen(sendBuffer), 0) < 0)  
    {  
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
    exit(0);  
    } 
    return 0;
} 
   
int rksIpv4_StreamTcp:: rksRecv()
{

    if((rec_len = recv(sockfd, recvBuffer, MAXLINE,0)) == -1) {
       perror("recv error");  
       exit(1);  
    }  
	recvBuffer[rec_len]  = '\0';
    printf("Received : %s ", recvBuffer);
    close(sockfd);  
    exit(0);  
    return 0;
}
  


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
    if(isServer == 1)
    {
        servaddr_ipv4.sin_addr.s_addr = htonl(INADDR_ANY);
    }  
    else
    {
        if( inet_pton(protofamily, addressString.c_str(), &servaddr_ipv4.sin_addr) <= 0)
        {  
            printf("inet_pton error for %s\n",addressString.c_str());  
            exit(0);  
        }
    }
    return 0;
}

int rksIpv4_StreamTcp:: rksBind()
{ 
    if( bind(sockfd, (struct sockaddr*)&servaddr_ipv4, sizeof(servaddr_ipv4)) == -1)
    {  
    printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    return 0;
}

int rksIpv4_StreamTcp:: rksListen()
{
    if( listen(sockfd, 10) == -1){  
    printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    printf("======waiting for client's request======\n"); 
    return 0;
}

int rksIpv4_StreamTcp:: rksAccept()
{
      
    if( (connfd = accept(sockfd, (struct sockaddr*)NULL, NULL)) == -1){  
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
        return -1;
    }
    return 0;
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
    int iSendFd;
    if (isServer == 0){
    printf("send msg to server: \n"); 
    iSendFd = sockfd; 
    }
    else{
    printf("send msg to client: \n");
    iSendFd = connfd; 
    }
    fgets(sendBuffer, MAXLINE, stdin);
    if( send(iSendFd, sendBuffer, strlen(sendBuffer), 0) < 0)  
    {  
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
    exit(0);  
    } 
    return 0;
} 
   
int rksIpv4_StreamTcp:: rksRecv()
{
    if(isServer == 0){
        if((rec_len = recv(sockfd, recvBuffer, MAXLINE,0)) == -1) {
           perror("recv error");  
           exit(1);  
        } 
    } 
    else
    {
        rec_len = recv(connfd, recvBuffer, MAXLINE, 0);
    }
	recvBuffer[rec_len]  = '\0';
    printf("Received : %s ", recvBuffer);
    return 0;
}

int rksIpv4_StreamTcp:: rksClose()
{
    close(sockfd);
}
int rksIpv4_StreamTcp::getConnfd(){return connfd;}
  


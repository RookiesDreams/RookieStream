#include<stdio.h>  
#include<stdlib.h>  
#include<unistd.h>
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#include<arpa/inet.h>
#include<queue>
#include<string>
  
#define MAXLINE 4096 

using namespace std;

class rksNetworkBase{
protected:
    int    sockfd,connfd, n,rec_len;  
    char*    sendBuffer;  
    char*    recvBuffer; 

    struct sockaddr_in servaddr_ipv4;
    struct sockaddr_in6 servaddr_ipv6;
    unsigned int port;
    bool isServer;
    bool isIpv4;
    
    int protofamily;
    int type;
    int protocol;

public: 
	rksNetworkBase() {};
    rksNetworkBase(bool isSer, bool isIp):isServer(isSer),isIpv4(isIp){ ;}
    virtual int setBuffer(int size)=0;
    virtual int setSocket()=0;// int protofamily,int type, int protocol )=0;
    virtual int setAddress_Port(int p, string addressString)=0;
    virtual int rksBind()=0;
    virtual int rksListen()=0;
    virtual int rksAccept()=0;
    virtual int rksConnect()=0;
    virtual int rksSend()=0;
    virtual int rksRecv()=0;
    virtual int getConnfd()=0;
    virtual int rksClose()=0;

};

class rksIpv4_StreamTcp: public rksNetworkBase{
public:
	rksIpv4_StreamTcp()
	{
		return;
	}
	rksIpv4_StreamTcp(bool isSer) //   ": isServer( isSer ), isIpv4(1)" : report error
    {
		isServer = isSer;
		isIpv4 = 1;
        
		protofamily = AF_INET;
        type = SOCK_STREAM;
        protocol =  0;
    }
    int setBuffer(int size);
    int setSocket();
    int setAddress_Port(int p, string addressString);
    int rksBind();
    int rksListen();
    int rksAccept();
    int rksConnect();
    int rksSend();
    int rksRecv();
    int rksClose();
    int getConnfd();

	~rksIpv4_StreamTcp() { delete sendBuffer; delete recvBuffer; }
};
        
    
    
    
    
    
    
    

#include "./include/rksNetwork.h"
  
  
int main(int argc, char** argv)  
{  
    
	rksNetworkBase* oTest = new rksIpv4_StreamTcp(false);

	oTest->setBuffer(MAXLINE);
	oTest->setSocket();
	oTest->setAddress_Port(8380, "192.168.0.9");
	oTest->rksConnect();
	oTest->rksSend();
	oTest->rksRecv();
} 

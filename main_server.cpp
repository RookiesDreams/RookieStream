#include "./include/rksNetwork.h"
  
  
int main(int argc, char** argv)  
{  
    
	rksNetworkBase* oTest = new rksIpv4_StreamTcp(true);

	oTest->setBuffer(MAXLINE);
	oTest->setSocket();
	oTest->setAddress_Port(8380, "");
	oTest->rksBind();
	oTest->rksListen();
	while(1){  
	    if(oTest->rksAccept()==-1){
	      continue;
	    }
	    oTest->rksRecv();
	    if(!fork()){
	    oTest->rksSend();
	    close( oTest->getConnfd());
	    }
	}
	oTest->rksClose();
	
} 

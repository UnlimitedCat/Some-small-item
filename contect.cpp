
#include <iostream>
#include <cstdio>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib") 

using namespace std;

int main()
{
	
	WORD wVersionRequested;
	WSADATA wsaData;	
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return -1;			
	}

	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		
		WSACleanup();
		return -1;
	}

	
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	
	listen(sockSrv, 10);

	

	

	SOCKADDR_IN  addrClient;
	int len = sizeof(SOCKADDR);

	while (true){	
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);

		char sendBuf[100];
		sprintf_s(sendBuf, "Welcome %s to the server program~ \nNow, let's start talking...\n", inet_ntoa(addrClient.sin_addr));
		send(sockConn, sendBuf, strlen(sendBuf) + 1, 0);	
		char recvBuf[100];
		recv(sockConn, recvBuf, 100, 0);
		printf("%s\n", recvBuf);		

		char * sockConnName = "Client";
		printf("OK");
		
		while (1){
			
			char recvBuf[100];
			recv(sockConn, recvBuf, 100, 0);
			printf("%s Says: %s\n", sockConnName, recvBuf);		

			char talk[100];
			printf("please talk(\"quit\"to exit):");
			gets_s(talk);
			send(sockConn, talk, strlen(talk) + 1, 0);			
			printf("\n");
		}
		printf("\nEnd talking... \n");
		closesocket(sockConn);
	}

	printf("\n");
	system("pause");
	return 0;
}
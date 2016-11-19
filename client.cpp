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

	
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);

	
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");		 
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	char recvBuf[100];
	recv(sockClient, recvBuf, 100, 0);
	printf("%s\n", recvBuf);

	send(sockClient, "Attention: A Client has enter...\n", strlen("Attention: A Client has enter...\n") + 1, 0);

	printf("we can talk !1");
	
	do{
		;
		char talk[100];
		printf("\n please talk (\"quit\"to exit):");
		gets_s(talk);
		send(sockClient, talk, strlen(talk) + 1, 0);			

		char recvBuf[100];
		recv(sockClient, recvBuf, 100, 0);
		printf("%s Says: %s\n", "Server", recvBuf);		
	} while (1);

	printf("End linking...\n");
	closesocket(sockClient);
	WSACleanup();	

	printf("\n");
	system("pause");
	return 0;
}


#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include <unistd.h>

#define PORT 5005

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char*argv[]){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in client;
    char str[20],str2[20];
    int a;

    // Initialising Winsock
    if(WSAStartup(MAKEWORD(2,2),&wsa)!=0){
        printf("Failed to initialise winsock : %d",WSAGetLastError());
        return 1;
    }
    printf("\nInitialised Winsock");

    // Creating a socket
    if((s=socket(AF_INET,SOCK_STREAM,0))==INVALID_SOCKET){
        printf("\nFailed to create Socket : %d",WSAGetLastError());
        return 1;
    }
    printf("\nSocket Created");

    // Setting sockaddr struct
    client.sin_addr.s_addr=inet_addr("127.0.0.1");
    client.sin_family=AF_INET;
    client.sin_port=htons(PORT);

    if(connect(s,(struct sockaddr*)&client,sizeof(client))<0){
        printf("\nFailed to connect : %d",WSAGetLastError());
        return 1;
    }
    printf("\nSocket connected");
    
    printf("\nCLIENT");
    scanf("%s",&str);
    if(send(s,str,strlen(str),0)<0)
    {
        printf("\n data could not be sent:%d",WSAGetLastError());
    }

    do
    {
        listen(s,1);
        recv(s,str2,sizeof(str2),0);
        printf("\nserver msg:%s",str2);
        printf("\nclient msg:");
        scanf("%s",&str);
        a=strcmp(str2,"BYE");
        send(s,str,sizeof(str),0);
    }
    while(a!=0);

    

    closesocket(s);
    WSACleanup();
}
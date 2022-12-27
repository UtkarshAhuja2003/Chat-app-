#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char*argv[]){
    WSADATA wsa;
    SOCKET s,new_s;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int c=sizeof(struct sockaddr_in);

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
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_family=AF_INET;
    server.sin_port=htons(8080);

    if(bind(s,(struct sockaddr*)&server,sizeof(server))==SOCKET_ERROR){
        printf("\nFailed to bind : %d",WSAGetLastError());
    }
    printf("\nServer bind");

    listen(s,5);
    while(1){
        new_s=accept(s,(struct sockaddr*)&client,&c);
        if(new_s==INVALID_SOCKET){
           printf("\nFailed to accept : %d",WSAGetLastError());
        }
        printf("\nAccepted");
        
    }
    


    // closesocket(s);
    // WSACleanup();
}
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char*argv[]){
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char *message="Hello from client",server_reply[2000];
    int recv_size;

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

    if(connect(s,(struct sockaddr*)&server,sizeof(server))<0){
        printf("\nFailed to connect : %d",WSAGetLastError());
        return 1;
    }
    printf("\nSocket connected");

    // while(1){
        if(send(s,message,strlen(message),0)<0){
           printf("\nFailed to send : %d",WSAGetLastError());
           return 1;
        }
         printf("\nMessage sent");

        if((recv_size=recv(s,server_reply,2000,0))==SOCKET_ERROR){
              printf("\nFailed to receive : %d",WSAGetLastError());
              return 1;
        }
         server_reply[recv_size]='\0';
         printf("\nMessage received : %s",server_reply);
    // }

    

    // closesocket(s);
    // WSACleanup();
}
#include<stdio.h>
#include<winsock2.h>
#include<ws2tcpip.h>
#include <unistd.h>

#define PORT 5005

#pragma comment(lib,"ws2_32.lib")

int main(int argc,char*argv[]){
    WSADATA wsa;
    SOCKET s,new_s;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int c=sizeof(struct sockaddr_in);
    char str[20],str2[20];
    int a,n;

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
    server.sin_port=htons(PORT);

    if(bind(s,(struct sockaddr*)&server,sizeof(server))==SOCKET_ERROR){
        printf("\nFailed to bind : %d",WSAGetLastError());
    }
    printf("\nServer bind");

    listen(s,1);
        new_s=accept(s,(struct sockaddr*)&client,&c);
        if(new_s==INVALID_SOCKET){
           printf("\nFailed to accept : %d",WSAGetLastError());
        }
        printf("\nAccepted");
        
    recv(new_s,str,sizeof(str),0);

    do
    {
        printf("\n client msg:%s",str);
        printf("\n server msg:");
        scanf("%s",str2);
        send(new_s,str2,sizeof(str2),0);
        listen(new_s,1);
        recv(new_s,str,sizeof(str),0);
        n=strcmp(str,"BYE");
        a=strcmp(str2,"BYE");
    }
    while(n!=0&&a!=0);
    

    closesocket(s);
    closesocket(new_s);
    WSACleanup();
}
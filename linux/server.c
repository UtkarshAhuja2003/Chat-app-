#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<errno.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT 5005


int main(int argc,char*argv[]){
    int s,new_s;
    struct sockaddr_in server;
    struct sockaddr_in client;
    int c=sizeof(struct sockaddr_in);
    char str[20],str2[20];
    int a,n;

    // Creating a socket
    if((s=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nFailed to create Socket : %d",errno);
        return 1;
    }
    printf("\nSocket Created");
     int optval = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    // Setting sockaddr struct
    server.sin_addr.s_addr=inet_pton(AF_INET, "172.31.4.174", &(server.sin_addr));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);

    if(bind(s,(struct sockaddr*)&server,sizeof(server))<0){
        printf("\nFailed to bind : %d",errno);
    }
    printf("\nServer bind");

    listen(s,1);
        new_s=accept(s,(struct sockaddr*)&client,&c);
        if(new_s<0){
           printf("\nFailed to accept : %d",errno);
        }
        printf("\nAccepted");
        
    recv(new_s,str,sizeof(str),0);
    printf("error:%d",errno);

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
    

    close(s);
    close(new_s);
}
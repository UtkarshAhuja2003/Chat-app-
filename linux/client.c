#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <unistd.h>
#include<errno.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 5005


int main(int argc,char*argv[]){
    int s;
    struct sockaddr_in client;
    char str[20],str2[20];
    int a;


    // Creating a socket
    if((s=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nFailed to create Socket : %d",errno);
        return 1;
    }
    printf("\nSocket Created");

    // Setting sockaddr struct
    client.sin_addr.s_addr=inet_pton(AF_INET, "172.31.4.174", &(client.sin_addr));
    client.sin_family=AF_INET;
    client.sin_port=htons(PORT);

    if(connect(s,(struct sockaddr*)&client,sizeof(client))<0){
        printf("\nFailed to connect : %d",errno);
        return 1;
    }
    printf("\nSocket connected");
    
    printf("\nCLIENT");
    scanf("%s",&str);
    if(send(s,str,strlen(str),0)<0)
    {
        printf("\n data could not be sent:%d",errno);
    }

    do
    {
        listen(s,1);
        recv(s,str2,sizeof(str2),0);
        printf("\nserver msg:%s",str2);
        printf("\nclient msg:");
        scanf("%s",&str);
        a=strcmp(str2,"BYE");
        send(s,str2,sizeof(str2),0);
    }
    while(a!=0);

    

    close(s);
}
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<errno.h>

#define PORT 8080


int main(int argc,char const* argv[]){
    int s,client_fd;
    struct sockaddr_in client;
    char str[20],str2[20];
    int a;

     int optval = 1;
    // Creating a socket
    if((s=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nFailed to create Socket : %d s : %d",errno,s);
        return 1;
    }
    printf("\nSocket Created");
    if (setsockopt(s, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &optval,
                   sizeof(optval))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }    // Setting sockaddr struct
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
     if (inet_pton(AF_INET, "127.0.0.1", &client.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
    if ((client_fd
         = connect(s, (struct sockaddr*)&client,
                   sizeof(client)))
        < 0) {
        printf("\nConnection Failed:%d \n",errno);
        return -1;

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

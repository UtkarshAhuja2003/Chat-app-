#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include<errno.h>

#define PORT 8080


int main(int argc,char const* argv[]){
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char str[20],str2[20];
    int a,n;
    int optval = 1;
    // Creating a socket
    if((server_fd=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("\nFailed to create Socket : %d s : %d",errno,server_fd);
        return 1;
    }
    printf("\nSocket Created");
    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &optval,
                   sizeof(optval))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }    // Setting sockaddr struct
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("server bind");
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
     printf("\nlistening...");
        if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  (socklen_t*)&addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
        printf("\nAccepted");
        
    recv(new_socket,str,sizeof(str),0);
    printf("error:%d",errno);

    do
    {
        printf("\n client msg:%s",str);
        printf("\n server msg:");
        scanf("%s",str2);
        send(new_socket,str2,sizeof(str2),0);
        listen(new_socket,1);
        recv(new_socket,str,sizeof(str),0);
        n=strcmp(str,"BYE");
        a=strcmp(str2,"BYE");
    }
    while(n!=0&&a!=0);
    

    close(server_fd);
    close(new_socket);
}

# Socket Programming Chat App

This is a simple command-line chat application that uses socket programming to establish a connection between the client and the server. The application is developed in C and supports both Windows and Linux operating systems.


## Requirements

- C compiler (GCC recommended)

- Windows or Linux operating system

## Installation

1. Clone the repository `git clone https://github.com/UtkarshAhuja2003/chat-app.git`

2. Navigate to the project directory `cd chat-app`

3. Compile the server and client source code by running 
- Linux    `gcc -o server server.c` and `gcc -o client client.c`
- Windows  `gcc -o server server.c -lws2_32` and `gcc -o client client.c -lws2_32`



## Usage

1. Start the server by running `./server`

2. Start the client by running `./client`

- Chat will continue until both the users write **BYE**

## Sreenshot
![image](https://user-images.githubusercontent.com/70762626/214885657-dd8f8871-14a3-484b-9606-244dbf240cca.png)



## About Socket Programming
This chat application uses socket programming to establish a connection between the client and the server. Sockets are the endpoint of a bidirectional communication channel between two programs running on a network. A socket has a "type" (e.g., SOCK_STREAM for TCP or SOCK_DGRAM for UDP), an IP address, and a port number.

In this project, the server creates a socket and binds it to a specific port. The client then connects to the server using the IP address and port number of the server's socket. Once the connection is established, the client and server can send and receive data using the socket.

## Resources

- [Beej's Guide to Network Programming](http://beej.us/guide/bgnet/) - A helpful guide to socket programming in C

- [Linux Socket Programming by Example](https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/tcpserver.c) - A code example of a TCP server in C

- [Windows Socket Programming](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2) - A guide to socket programming in C on Windows

## Contributing

We welcome contributions to this project. If you would like to contribute, please fork the repository, make your changes and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

# cpp-socket-practice

## What is a socket: 
-   Abstraction provided by an OS that enables communication between processes either on the same machine or over a network.
-   They act as endpoints on a two way communication channel creating a pipeline through which two processes can communicate. 
-   Software construct taht wraps a combination of a protocol (commonly TCP or UDP) an IP address and a port number. 
-   Two common types of sockets (1) streaming socket (SOCK_STREAM) (TCP) and (2) Datagram socket (SOCK_DGRAM) (UDP). 

## Server Process 

```
[socket()] ~ Allocates a new TCP socket (AF_INET + SOCK_STREAM). 
    ↓
[bind()]   ~ Tells the OS “I want to receive incoming TCP connections on this port, on any local IP.  
    ↓
[listen()] ~ Marks the socket as passive—now the OS will queue up to 3 pending connection requests.
    ↓
[accept()] ~ Returns a new socket FD (client_socket) dedicated to that one client.
    ↓
[recv()]   ~ (1) First call: Reads 4 bytes, giving you the length of the upcoming message.(2) Second call: Reads exactly that many bytes into your std::string.
    ↓
[write()]
    ↓
[close()]  ~ What it does: Stops listening, releases the port, and tidies up.
```





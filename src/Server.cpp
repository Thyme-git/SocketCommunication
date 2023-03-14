# include <iostream>
# include <sys/socket.h>
# include "Server.h"
# include <cstring>
# include <unistd.h>
# include <errno.h>

Server :: Server(
    ConnectionType type,          // TCP
    unsigned short int port,      // 3333
    in_addr_t IPv4_addr           // INADDR_ANY
){
    // 创建socket
    __socket_type socket_type = (type == UDP) ? SOCK_DGRAM : SOCK_STREAM;
    this->socket_file_descriptor = socket(AF_INET, socket_type, 0);
    if (this->socket_file_descriptor == -1)
    {
        std :: cerr << "can't create socket!" << std :: endl;
        exit(-1);
    }

    // 将socket 与ip地址以及端口绑定
    this->ip_address.sin_family = AF_INET;
    this->ip_address.sin_port = port;
    this->ip_address.sin_addr.s_addr = IPv4_addr;

    // memset(this->ip_address.sin_zero, 0, sizeof(this->ip_address.sin_zero));

    if (bind(this->socket_file_descriptor, (sockaddr*) &(this->ip_address), sizeof(sockaddr)) == -1)
    {
        std :: cerr << "bind error!" << std :: endl;
        close(this->socket_file_descriptor);
        exit(-1);
    }

    this->connectionType = type;
    this->client_sockfd = -1;
}

bool Server :: server_listen(
    int max_queue_length
){
    int check = listen(this->socket_file_descriptor, max_queue_length);

    if (check == -1)
    {
        std :: cerr << "listen error!" << std :: endl;
        return false;
    }

    return true;
}

bool Server :: server_accept(
    int try_time
){
    bool accepted = false;
    int client_size = sizeof(sockaddr);
    while (try_time--)
    {
        this->client_sockfd = accept(this->socket_file_descriptor, (sockaddr*)&(this->client_address), (socklen_t*)&client_size);

        if (this->client_sockfd != -1)
        {
            accepted = true;
            break;
        }
    }

    if (!accepted)
    {
        std :: cerr << "accepted error!" << std :: endl;
        return false;
    }

    return true;
}

bool Server :: server_send(
    char* msg
){
    int sent_byte = send(this->client_sockfd, msg, strlen(msg), 0);
    if (sent_byte == -1){
        std :: cerr << "send error!" << std :: endl;
        return false;
    }
    return true;
}

bool Server :: server_receive()
{
    int recieved_byte = recv(this->client_sockfd, (void*)this->buffer, this->buffer_size, 0);

    if (recieved_byte == -1)
    {
        std :: cerr << "receive error!" << std :: endl;
        return false;
    }
    this->buffer[recieved_byte] = '\0';
    return true;
}

void Server :: server_close()
{
    close(this->socket_file_descriptor);
}

char* Server :: get_buffer()
{
    return this->buffer;
}

# ifdef DEBUG

int main()
{
    Server server(TCP, htons(SERVERPOT));
    server.server_listen();
    if (!server.server_accept())
    {
        exit(-1);
    }
    std :: cout << "connected!" << std :: endl;
    
    
    server.server_receive();
    std :: cout << "client sent : " << server.get_buffer() << std :: endl;
    
    
    char* msg = "hi client!";
    server.server_send(msg);

    
    server.server_close();
    return 0;
}

# endif
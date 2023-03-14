# include <iostream>
# include <sys/socket.h>
# include "Client.h"
# include <cstring>
# include <unistd.h>
# include <errno.h>

Client :: Client(
    ConnectionType type
){
    // 创建socket
    this->socket_type = (type == UDP) ? SOCK_DGRAM : SOCK_STREAM;
    this->socket_file_descriptor = socket(AF_INET, this->socket_type, 0);
    if (this->socket_file_descriptor == -1)
    {
        std :: cerr << "can't create socket!" << std :: endl;
        exit(-1);
    }

    this->connectionType = type;
}

bool Client :: client_connect(
    sockaddr_in& server_address,
    int try_time
){
    bool connected = false;
    while (try_time--)
    {
        int check = connect(this->socket_file_descriptor, (struct sockaddr *) &(server_address), sizeof(sockaddr));
        if (check != -1)
        {
            connected = true;
            break;
        }
    }

    if ( !connected )
    {
        std :: cerr << "connection error!" << std :: endl;
        return false;
    }

    this->server_address = server_address;

    return true;
}

bool Client :: client_send(
    char* msg
){
    int sent_byte = send(this->socket_file_descriptor, msg, strlen(msg), 0);
    if (sent_byte == -1){
        std :: cerr << "send error!" << std :: endl;
        return false;
    }
    return true;
}

bool Client :: client_receive()
{
    int recieved_byte = recv(this->socket_file_descriptor, this->buffer, this->buffer_size, 0);
    if (recieved_byte == -1)
    {
        std :: cerr << "send error!" << std :: endl;
        return false;
    }
    this->buffer[recieved_byte] = '\0';
    return true;
}

void Client :: client_close()
{
    close(this->socket_file_descriptor);
}

char* Client :: get_buffer()
{
    return this->buffer;
}

# ifdef DEBUG

int main()
{
    Client client(TCP);
    
    sockaddr_in server_address;
    server_address.sin_addr.s_addr = LOCALHOST;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVERPOT);
    // memset(server_address.sin_zero, 0, sizeof(server_address.sin_zero));

    if (!client.client_connect(server_address))
    {
        exit(-1);
    }
    std :: cout << "connected!" << std :: endl;
    
    
    char* msg = "hello server!";
    client.client_send(msg);
    
    
    client.client_receive();
    std :: cout << "server sent : " << client.get_buffer() << std :: endl;

    
    client.client_close();

    return 0;
}

# endif
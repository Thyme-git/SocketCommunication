# ifndef CLIENT_H
# define CLIENT_H

# include <netinet/in.h> // struct sockaddr_in
# include "utils.h"

// 仅支持IPv4
class Client
{
    int socket_file_descriptor;
    ConnectionType connectionType; // UDP or TCP
    sockaddr_in server_address;
    int socket_type;
    
    char buffer[BUFFER_SIZE];
    int buffer_size = BUFFER_SIZE;

public:
    Client(
        ConnectionType type
    );

    bool client_connect(
        sockaddr_in& server_address,
        int try_time = 10
    );

    bool client_send(
        char* msg
    );

    bool client_receive();

    void client_close();

    char* get_buffer();
};

# endif
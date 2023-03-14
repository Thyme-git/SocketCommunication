# ifndef SERVER_H
# define SERVER_H

# include <netinet/in.h> // struct sockaddr_in
# include "utils.h"

// 仅支持IPv4
class Server
{
    int socket_file_descriptor;
    sockaddr_in ip_address;        // ipv4 with port
    ConnectionType connectionType; // UDP or TCP
    sockaddr_in client_address;
    int client_sockfd;
    
    char buffer[BUFFER_SIZE];
    int buffer_size = BUFFER_SIZE;

public:
    Server(
        ConnectionType type,
        unsigned short int port,
        in_addr_t IPv4_addr = INADDR_ANY
    );

    bool server_listen(
        int max_queue_length = MAX_QUEUE_LENGTH
    );

    bool server_accept(
        int try_time = 10
    );

    bool server_send(
        char* msg
    );

    bool server_receive();

    void server_close();

    char* get_buffer();
};

# endif
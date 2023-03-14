# C语言网络编程

* 套接字地址
  * ```struct sockaddr_in``` 是 ```struct sockaddr``` 的升级版
  * ```struct sockaddr_in``` 包含了地址族（IPv4还是IPv6）, 主机IP地址以及端口号。
    ```
    struct sockaddr_in {
        short sa_family;//地址族，2字节
        unsigned short int sin_port;//端口号，2字节
        struct in_addr sin_addr;//IP地址，4字节
        unsigned char sin_zero[];//填充0以保持与struct sockaddr同样大小，8字节
    }
    struct in_addr {
        in_addr_t s_addr; //类型实际上是unsigned int
    };
    ```
  * AF_INET：IPv4协议
  * AF_INET4：IPv6协议
  * AF_LOCAL：UNIX域协议
  * AF_LINK：链路地址协议
  * AF_KEY：秘钥套接字

* 网络地址(IPv4为例)：
  * 使用一个unsigned int(in_addr_t)来存储32位的IPv4地址
  * **存储方式为大端法（与x86计算机小端在前的字节顺序相反）**
  * ```in_addr_t inet_addr(char * IP_addr)``` 函数将字符串形式转化成 ```in_addr_t``` 形式

* 端口号：
  * 端口号存储方式依旧是大端法
  
* 大端数据（net type）与小端数据转化函数：
  * htonl（host type to net type long）:将四个字节的小端数据(host type)转化成大端数据（net type）
  * htons (host type to net type short):两个字节
  * ntohl、ntohs

* int socket(int family,int type,int protocol)：
  * 创建一个套接字文件(可以往文件中进行读写)
  * family：对应的就是AF_INET、AF_INET6等。
  * type：套接字类型：SOCK_STREAM、SOCK_DGRAM、SOCK_RAW。
  * protocol：0
  * return：套接字文件描述符(int sockfd, socket file descriptor)
  * 出错返回-1

* int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  * 将套接字文件(sockfd)与网络端口以及地址(addr)绑定在一起
  * 套接字文件可以通过自己的网络地址向另一个网络地址上的套接字文件进行数据传输

* int listen(int sockfd,int max_length_of_queue):
  * 让server套接字文件（sockfd）处在监听状态，
  * max_length_of_queue：消息队列最大长度，程序每次只能处理一个请求，当多个请求到来时会存放在消息队列中。

* int accept(int sockfd,struct sockaddr * addr,socklen_t* addrlen)
  * 当server套接字处于监听状态时，可以通过 accept() 函数来接收客户端client的连接(connection)请求
  * sockfd：服务端套接字描述符
  * addr：客户端地址
  * addrlen：地址大小
  * 返回一个客户端套接字描述符，失败返回-1

* int connect(int sockfd,struct sockaddr* serv_addr,int addrlen)：
  * 将客户端套接字(sockfd)与服务端地址(serv_addr)相连接
  * client发出连接请求，server将会选择accept

* int send(int sockfd,const void* msg,int len,int flags)：
  * 让sockfd向与之连接的地址发送msg
  * 返回发送的字节数
  
* int recv(int sockfd,void* buf,int len,unsigned int flags):
  * 接收sockfd发送的信息，储存在buf中
  * len为缓冲区长度
  * flags一般为0
  * 返回接收的字节数

* int sendto(int sockfd,const void* msg,int len,unsigned int flags,const struct sockaddr* to,int tolen)

* int recvfrom(int sockfd,void * buf,int len,unsigned int flags,struct sockaddr* from,int* fromlen)


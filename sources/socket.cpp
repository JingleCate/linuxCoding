/**
 * @Author  JingleCath
 * @Date  2/25/23 - 8:01 PM
 * @Version 0.1
 * @Description TCP: Server and client.
*/

#include "include/socket.h"

#define SERVER_PORT 5000                // server端口
#define CLIENT_PORT 1000                // client端口
#define MAX_CON_NUM 128                 // 最大连接数

/**
 * Server socket.
 * @return
 */
int server() {
    // 1. 创建基于TCP连接的 listen socket fd
    // 流式对应TCP，报式对应UDP， protocol 填入0自动即可
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1) {
        std::cerr << "Socket creat error." << std::endl;
        return -1;
    }

    // 2. bind绑定监听监听描述符
    sockaddr_in _server_addr;
    _server_addr.sin_family = AF_INET;                  /* IPv4 */
    _server_addr.sin_port = htons(SERVER_PORT);       /* port: 5000 */
    _server_addr.sin_addr.s_addr = INADDR_ANY;          /* 0.0.0.0 */
    int ret = bind(lfd, (sockaddr *) &_server_addr, sizeof(_server_addr));
    if (ret == -1) {
        std::cerr << "Socket bind error." << std::endl;
        return -1;
    }

    // 3. 设置监听
    ret = listen(lfd, MAX_CON_NUM);
    if (ret == -1) {
        std::cerr << "Socket listen error." << std::endl;
        return -1;
    }

    std::cout << "----------------- Server Listening ------------------" << std::endl;
    // 4. 阻塞等待客户端连接, 得到 Client-Server连接文件描述符cfd
    // Await a connection on socket FD.
    sockaddr_in _client_addr;                                   /* client address */
    socklen_t _client_len = sizeof(_client_addr);               /* client address length */
    int cfd = accept(lfd, (sockaddr *) &_client_addr, &_client_len);
    if (cfd == -1) {
        std::cerr << "Server connect(accept) error." << std::endl;
        return 0;
    }

    // 打印 Client 信息
    char ip[20] = {0};               /* like 192.168.100.4 */
    std::cout << "************* Connection established ************" << std::endl;
    std::cout << "\tAddr: " << _client_addr.sin_addr.s_addr << ':' << _client_addr.sin_port << std::endl;

    /**
     * 将大端的整形数, 转换为小端的点分十进制(IPv4)的IP地址
     * @method const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
     *
     * 将一个短整形从网络字节序(🦣大端) -> 主机字节序(🦐小端)
     * @method uint16_t ntohs(uint16_t netshort)
     */
    std::cout << "\tAddr: " << inet_ntop(AF_INET, &_client_addr.sin_addr.s_addr, ip, sizeof(ip))
              << ':' << ntohs(_client_addr.sin_port) << std::endl;

    // 5. 通信 Communication.
    /**
     * @Principle read/write 方法只负责将 buf 写入内核， 而后内核通过 communication fd
     * 接收/发送 buf内容
     */

    while (true) {
        std::cout << "---> 🐕‍🦺" << std::endl;
        char buf[1024];                     /* read/write buffer */
        int rlen = read(cfd, buf, sizeof(buf));
        time_t cur_time;
        time(&cur_time);
        if (rlen > 0) {
            std::cout << "Client sayed: " << buf << " \t\t\t - " << ctime(&cur_time);
            const char *re = "I have received message.";
            strcpy(buf, re);
            write(cfd, buf, sizeof(buf));
            std::cout << "Server reply: " << buf << " \t\t\t - " << ctime(&cur_time);
        } else if (rlen == 0) {
            std::clog << "Client broke connection." << std::endl;
            break;
        } else {
            std::cerr << "Communication error." << std::endl;
            throw "EOF of exception.";
            break;
        }
    }

    close(cfd);
    close(lfd);
    std::cout << "*************************************************" << std::endl;

    return 0;
}

/**
 * Client socket.
 * @return
 */
int client() {
    // 1. 通信套接字
    int cfd = socket(AF_INET, SOCK_STREAM, 0);

    // 2. 连接服务器
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    /**
     * 主机字节序的IP地址转换为网络字节序
     * 主机字节序的IP地址是字符串, 网络字节序IP地址是整形
     * @method int inet_pton(int af, const char *src, void *dst);
     */
    inet_pton(AF_INET, "localhost", &addr.sin_addr.s_addr);

    int ret = connect(cfd, (sockaddr *) &addr, sizeof(addr));
    if (ret == -1) {
        std::cerr << "Client connect error." << std::endl;
        return -1;
    }

    // 3. 与服务器通信
    int number = 0;
    while (true) {
        std::cout << "---> ‍🔠" << std::endl;
        char buf[1024];
        time_t cur_time;
        time(&cur_time);
        // 发送数据
        std::cout << "Please input: ";
        std::cin.getline(buf, sizeof(buf) - 1);       // 🤓
        // getline 得到字符串buf尾部为 '\0'
        if((buf[0] == 'Q' || buf[0] == 'q') && buf[1] == '\0')
            return 0;
        write(cfd, buf, sizeof(buf));
        std::cout << "Client reply: " << buf << " \t\t\t - " << ctime(&cur_time);


        // 接受数据
        int rlen = read(cfd, buf, sizeof(buf));

        if (rlen > 0) {
            std::cout << "Server sayed: " << buf << " \t\t\t - " << ctime(&cur_time);

        } else if (rlen == 0) {
            std::clog << "Server broke connection." << std::endl;
            break;
        } else {
            std::cerr << "Communication error." << std::endl;
            throw "EOF of exception.";
            break;
        }
        sleep(1);
    }

    close(cfd);
    return 0;
    // connect(cfd, )
}


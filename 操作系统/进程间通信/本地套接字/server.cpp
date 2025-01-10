#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/my_socket"

int main()
{
    int server_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sock == -1)
    {
        perror("socket");
        return 1;
    }

    sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        return 1;
    }

    if (listen(server_sock, 5) == -1)
    {
        perror("listen");
        return 1;
    }

    std::cout << "Server listening on " << SOCKET_PATH << "...\n";

    int client_sock = accept(server_sock, nullptr, nullptr);
    if (client_sock == -1)
    {
        perror("accept");
        return 1;
    }

    std::cout << "Client connected\n";

    char buffer[256];
    ssize_t len = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    if (len == -1)
    {
        perror("recv");
    }
    else
    {
        buffer[len] = '\0';
        std::cout << "Received message: " << buffer << std::endl;
    }

    close(client_sock);
    close(server_sock);
    unlink(SOCKET_PATH); // 删除套接字文件

    return 0;
}

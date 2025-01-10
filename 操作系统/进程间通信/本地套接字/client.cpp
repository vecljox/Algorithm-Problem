#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/my_socket"

int main()
{
    int client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_sock == -1)
    {
        perror("socket");
        return 1;
    }

    sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        return 1;
    }

    const char *message = "Hello from client!";
    if (send(client_sock, message, strlen(message), 0) == -1)
    {
        perror("send");
        return 1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    close(client_sock);
    return 0;
}

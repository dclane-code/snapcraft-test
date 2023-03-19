#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stddef.h>

#define SOCKET_NAME "#dclusock"
#define ECHO_MSG "you said: "
#define ECHO_LEN 10

int main(int argc, char** argv) {
    struct sockaddr_un addr;
    int sock = 0;
    int ret = 0;
    int nRead = 0;

    char buf[1024];

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock <= 0) {
        printf("failed to make socket\n");
        return -1;
    }
    printf("blank unix socket created\n");

    ret = remove(SOCKET_NAME);
    if (ret == -1) {
        if (errno != ENOENT) {
            printf("socket file exists, couldn't be deleted\n");
            return 0;
        }
    } else {
        printf("old socket deleted\n");
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path));
    addr.sun_path[0] = '\0';    //to make it an abstract socket namespace

    ret = bind(sock, (struct sockaddr *)&addr, offsetof(struct sockaddr_un, sun_path)+strlen(SOCKET_NAME));
    if (ret == -1) {
        printf("failed to bind to socket\n");
        return -1;
    }
    printf("socket bound to %s\n", SOCKET_NAME);

    ret = listen(sock, 2);
    if (ret == -1) {
        printf("failed to start listening\n");
        return -1;
    }

    //might put this into a loop, but for now lets just handle one connection then quit
    while (1) {
        printf("listening for connection\n");

        int conn = accept(sock, NULL, NULL);
        printf("connection accepted :)\n");

        //simple echo loop
        strncpy(buf, ECHO_MSG, ECHO_LEN);
        while ( (nRead = read(conn, &buf[ECHO_LEN], 1024-ECHO_LEN)) > 0) {
            write(conn, buf, nRead+ECHO_LEN);
        }
    }


}

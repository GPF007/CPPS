
#include <sys/socket.h>
#include <netdb.h>

class Server{

public:
    void start();
    //void str_echo(int fd);


private:
    int listenfd,connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr,servaddr;
};

#include "utils.h"


void perror_die(char* msg){
    perror(msg);
    exit(EXIT_FAILURE);
}


//设置好socket_addr
int listen_inet_socket(int portnum){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror_die("open socket error!");
    }
    int opt = 1;
    /*SOL_SOCKET： 通用套接字选项
      SO_REUSEADDR: 允许重用本地地址和端口
      &opt 制定设置新选项值的缓冲
    */
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror_die("setsockopt error!");
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0 ,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);

    if(bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        perror_die("bind error");
    }
    if(listen(sockfd, N_BACKLOG < 0)){
        perror_die("listen error");
    }

    return sockfd;
}


/*报告客户链接信息*/
void report_peer_connected(const struct sockaddr_in* sa, socklen_t salen)
{
    /* netdb.h 
       #define NI_MAXHOST 1025
       #define NI_MAXSERV 32
    */
    char hostbuf[NI_MAXHOST];
    char portbuf[NI_MAXSERV];

    /*getnameinfo 将socket地址转化为主机和服务*/
    if(getnameinfo((struct sockaddr*)sa,salen,hostbuf,NI_MAXHOST, portbuf, NI_MAXSERV,0) == 0){
        printf("peer(%s, %s) connected\n",hostbuf,portbuf);
    }else{
        printf("peer(unknown) connected\n");
    }
}


bool_t has_prefix(char* str, char* prefix)
{
    int m = strlen(str), n = strlen(prefix);
    if(m < n){
        return FALSE;
    }

    return strncmp(str,prefix, n) == 0 ? TRUE : FALSE;
    
}

bool_t has_suffix(char* str, char* suffix)
{
    int m = strlen(str), n = strlen(suffix);
    if(m < n){
        return FALSE;
    }

    int i = m-1, j = n-1;
    while(j>=0){
        if(suffix[j] != str[i])
            return FALSE;
        i--;j--;
    }
    return TRUE;

    
}

/*去除str两边多余的空白符*/
char* strip(char *str)
{
    int len = strlen(str);
    int i;
    for(i=len-1;i>=0;i--){
        if(str[i]!=' ' && str[1]!='\r'&& str[1]!='\t'&& str[1]!='\n' )
            break;
    }
    str[i+1]='\0';

    while(*str==' ' || str == '\r' || *str == '\t' || *str=='\n')
        str++;
    
    return str;
    
}
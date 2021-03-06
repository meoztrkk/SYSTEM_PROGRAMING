/*bir veri akış soketi sunucusu örneği*/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define MYPORT 3490    // kullanıcıların bağlanacağı port

#define BACKLOG 10     // bağlantı kuyruğunda bekletileceklerin sayısı

void sigchld_handler(int s)
{
    while(wait(NULL) > 0);
}

int main(void)
{
    int sockfd, new_fd;  // sock_fd ile dinle, yen bağlantıyı new_fd ile al
    struct sockaddr_in my_addr;    // adres bilgim
    struct sockaddr_in their_addr; // bağlananın adres bilgisi
    int sin_size;
    struct sigaction sa;
    int yes=1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    my_addr.sin_family = AF_INET;         // konak bayt sıralaması
    my_addr.sin_port = htons(MYPORT);     // short, ağ bayt sıralaması
    my_addr.sin_addr.s_addr = INADDR_ANY; // otomatik olarak IP'mi kullan
    memset(&(my_addr.sin_zero), '\0', 8); // geriye kalan bölgeyi sifirla

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // tüm ölü süreçleri kaldır
    sigemptyset(&sa.sa_mask);
    //sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    while(1) {                       // ana accept() döngüsü
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n",inet_ntoa(their_addr.sin_addr));
        if (!fork()) {               // çocuk süreç
            close(sockfd);           // çocuk sürecin dinlemesi gerekmez
            if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);               // ana sürecin buna ihtiyacı yok
    }

    return 0;
} 
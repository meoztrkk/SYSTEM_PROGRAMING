/*
** getip.c -- konak isminden IP adresini elde edilmesi
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{

//h_name -- Konağın resmi ismi.
//h_aliases -- Söz konusu konağın alternatif isimleri, NULL ile sonlandırılmış karakter dizileri şeklinde.
//h_addrtype -- Dönen adresin türü, genellikle AF_INET değerini alır.
//h_length -- Byte cinsinden adresin uzunluğu.
//h_addr_list -- Konağın ağ adresinin sıfır sonlandılmalı dizisi. Konak adresleri ağ bayt sıralamasına sahiptir.
//h_addr -- h_addr_list listesindeki ilk adres. 

    struct hostent *h;

    if (argc != 2) {  // komut satırında hata denetimi
        fprintf(stderr,"usage: getip konak_ismi\n");
        exit(1);
    }

    if ((h=gethostbyname(argv[1])) == NULL) {  // konak bilgilerini al
        herror("gethostbyname");
        exit(1);
    }

    printf("Konak ismi: %s\n", h->h_name);
    printf(" IP Adresi: %s\n", inet_ntoa(*((struct in_addr *)h->h_addr_list)));

   return 0;
} 
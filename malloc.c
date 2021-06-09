#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void) {

    char *cp; 
    /* Bellek tahsisi */
    cp = (char*) malloc(20);
    strcpy(cp, "Bilgisayar");
    printf("Karakter dizisi: %s", cp); 
    /* Bellek boşaltma */
		free(cp);

		int *ip; 
		// int veri türü boyutu kadar kadar bellek tahsisi
		ip = (int*) malloc(sizeof(int));
		*ip = 126; 
		printf("Tahsis edilen bellek adres başlangıcı: %p\n", ip);
		printf("Tahsis edilen bellekteki değişken değeri: %d", *ip); 
		free(ip);

		char *cp1 = "İlk karakter dizisi";
		char *cp2, *cp3;
		char cdizi[30]; 
		cp2 = "İkinci karakter dizisi"; 
		cp3 = (char*) malloc(50);
		strcpy(cp3, "Üçüncü karakter dizisi"); // malloc() ve free() fonksiyonları kullanılmadığında hata verir.
		strcpy (cdizi, "Dördüncü karakter dizisi"); 
		printf("%s\n%s\n%s\n%s", cp1, cp2, cp3, cdizi); 
		free(cp3);

    return 0;
}
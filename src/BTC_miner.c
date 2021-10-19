#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <openssl/sha.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#include "sha256calc.h"

#define MAX_LINE_LENGTH 64

void __error(int cod, char *s);
void copy_file(FILE *f1, char *filename, FILE *f2, char new_filename[20], char hex[9]);
void random_hex(char hex[9], uint32_t n);
int count_zeros(char hash[65]);

int main(int argc, char * argv[]){
    
    //Comprobar los argumentos
    if(argc != 3){
	printf("ERROR: Bad argument!");
	printf("\nUse: ./BTC_miner file");
	exit(0);
    }

    //Declaraión de variables
    FILE *bloque, *nuevo_bloque;
    char *filename, new_filename[20];
    char hex_num[9];
    char hash1[65];
    int count = 0, find = 0, iter = 0, max;
    uint32_t n;
    n = 0;


    //Nombre del nuevo fichero
    filename = argv[1];
    max = atoi(argv[2]);
    sprintf(new_filename, "new_%s", filename);
    //printf("New:%s\n", new_filename);

    printf("[*] Minando bloque: %s\n", filename);

    while(find == 0){
	iter++;
	//Calcular hexadecimal aleatorio e insertarlo en el bloque
	random_hex(hex_num, n);
	n++;
	copy_file(bloque, filename, nuevo_bloque, new_filename, hex_num);
    
	//Hash del fichero
	sha256_file(new_filename, hash1);
	//printf("hash: %s\n", hash1);

	//contar el numero de ceros
	count = count_zeros(hash1);
	//printf("counter; %d\n", count);

	if(count > max){
	    find = 1;
	}else{
	    remove(new_filename);
	}
    }

    printf("[*] Resumen: %s\n", hash1);
    printf("[OK] Minado con exito!\n	-Coste: %d\n	-Numero de ceros: %d\n", iter, count);
    
}

void __error(int cod, char *s){
    switch(cod){
	case 0:
	    printf("******** %s *********\n", s);
	    break;
	default:
	    break;
    }
    exit(0);
}

void random_hex(char hex[9], uint32_t n){
   

    //FILE * f = fopen("/dev/urandom", "rb");
    //fread(&n, sizeof(uint32_t), 1, f);
    sprintf(hex, "%08X", n);
    printf("hex: %s\n", hex);
    //fclose(f);
}

void copy_file(FILE *f1, char *filename, FILE *f2, char new_filename[20], char hex[9]){
    
    char line[MAX_LINE_LENGTH];
    //Abrir los documentos
    if((f1 = fopen(filename, "r")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }
    if((f2 = fopen(new_filename, "a+")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }

    //Copiar lso documentos
    while(fgets(line, sizeof(line), f1) != NULL){
	fprintf(f2, line);
    }

    fprintf(f2, hex);
    fprintf(f2, " SGSSI-21_UFER\n");
    fclose(f1);
    fclose(f2);


}

int count_zeros(char hash[65]){
    int counter, i;
    counter = 0;
    if(hash[0] == '0'){
	counter++;
	for(i = 1; i < 65; i++){
	    if(hash[i] == '0')
		counter++;
	    else
		break;
	}
    }
    return counter;
}

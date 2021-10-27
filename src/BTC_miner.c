/*=========================================================================
 *
 *  Author: Unai Fernandez
 *  Date: 2021-10-19
 *
 *  Execute:
 *	./BTC_miner <file> <number>
 *
 ==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <openssl/sha.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

#include "BTC_miner.h"
#include "sha256calc.h"

/*
 * Función principal
 */
int main(int argc, char * argv[]){
    
    //Comprobar los argumentos
    if(argc != 3){
	printf("ERROR: Bad argument!");
	printf("\nUse: ./BTC_miner <file> <number>");
	exit(0);
    }

    //Declaraión de variables
    FILE *bloque, *nuevo_bloque, *final_block;
    char *filename, new_filename[20], final_filename[20];
    char hex_num[9];
    char hash1[65], hash[65];
    int count = 0, find = 0, iter = 0, max;
    uint32_t n;
    char *buff;
    
    time_t start, end;
    double dif;
    //n = 0;


    filename = argv[1];                                 //Nombre del fichero
    max = atoi(argv[2]);                                //numero de ceros
    max--;
    sprintf(new_filename, "new_%s", filename);          //guardar el nombre del nuevo fichero
    sprintf(final_filename, "new_%s", filename);        //guardar el nombre del nuevo fichero
    int lineas = block_lines(bloque, filename);         //contar las lineas que tiene el bloque
    buff = malloc(lineas*MAX_LINE_LENGTH*sizeof(char)); //reservar la memoria para buff
    


    //---------------------- Inicio del minado del bloque -------------------------

    printf("[*] Minando bloque: %s\n", filename);

    time(&start);
    while(find == 0){
	//sumar iteraciones
	iter++;
	
	//Calcular hexadecimal aleatorio e insertarlo en el bloque
	random_hex(hex_num, n);
	//n++;
	copy_to_buff(bloque, filename, buff, hex_num ,lineas);
    
	//Hash del fichero
	sha256(buff, hash1);

	//contar el numero de ceros
	count = count_zeros(hash1);

    //si se encuentra un hash con mas o el mismo numero de ceros establecido se copia el resultado a un fichero
	if(count > max){
	    find = 1;
	    copy_file(bloque, filename, nuevo_bloque, final_filename, hex_num);
	    printf("%s", buff);
	}else{
	 memset(buff, '\0', lineas*MAX_LINE_LENGTH);    //Vaciar la variable buff
	}
    }
    time(&end);
    dif = difftime(end, start);

    printf("[*] Resumen: %s\n", hash1);
    printf("[OK] Minado con exito!\n	-Coste: %d iteraciones\n	-Numero de ceros: %d\n	-Tiempo transcurrido: %1.1f s\n", iter, count, dif);


    //-------------------------- Fin del minado ----------------------------
    
}

/*
 * Función para printear el error.
 */
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

/*
 * Función para guardar un valor hexadecimal aleatorio en la variable hex
 */
void random_hex(char hex[9], uint32_t n){
    FILE * f = fopen("/dev/urandom", "rb");
    fread(&n, sizeof(uint32_t), 1, f);
    sprintf(hex, "%08x", n);
    fclose(f);
}

/*
 * Función para copiar el contenido del bloque original al nuevo y añadir la linea con el numero hexadecimal
 */
void copy_file(FILE *f1, char *filename, FILE *f2, char new_filename[20], char hex[9]){
    
    char line[MAX_LINE_LENGTH];
    //Abrir los documentos
    if((f1 = fopen(filename, "r")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }
    if((f2 = fopen(new_filename, "a+")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }
    //Copiar los documentos
    while(fgets(line, sizeof(line), f1) != NULL){
	fprintf(f2, line);
    }

    //Añadir la ultima linea
    fprintf(f2, hex);
    fclose(f1);
    fclose(f2);


}

/*
*   Funcion para copiar el contenido del fichero a un buffer
*/
void copy_to_buff(FILE *f1, char *filename, char *buff, char hex[9], int lineas){
    
    char line[MAX_LINE_LENGTH];
    char *lag = " G23\n";

    //Abrir el documento
    if((f1 = fopen(filename, "r")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }
	
    //leer el contenido y guardarlo en buff
    fread(buff, 1, lineas*MAX_LINE_LENGTH-1, f1);

    //añadir el hezadecimal
    strcat(hex, lag);
    strcat(buff, hex);
    
    fclose(f1);
}

int block_lines(FILE *f1, char *filename){
    int line_counter = 0;
    char line[MAX_LINE_LENGTH];
    
    //Abrir el documento
    if((f1 = fopen(filename, "r")) == NULL){
	__error(0, "No se ha encontrado el fichero");
    }
    
    //Copiar lso documentos
    while(fgets(line, sizeof(line), f1) != NULL){
	line_counter++;
    }
    return line_counter;
}

/*
 * Función para contar los ceros que hay.
 */
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

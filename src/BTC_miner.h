#define MAX_LINE_LENGTH 64	    //Longitud maxima de la linea

void __error(int cod, char *s);	    //Función error
void copy_file(FILE *f1, char *filename, FILE *f2, char new_filename[20], char hex[9]);	    //Función para copiar contenido del fichero
void random_hex(char hex[9], uint32_t n);	//Función para calcular valor hexadecimal
int count_zeros(char hash[65]);	    //Función para contar ceros



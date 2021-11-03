#define MAX_LINE_LENGTH 65	    //Longitud maxima de la linea

void __error(int cod, char *s);	    //Función error
void copy_file(FILE *f1, char *filename, FILE *f2, char new_filename[8], char hex[9]);	    //Función para copiar contenido del fichero
void copy_to_buff(FILE *f1, char *filename, char *buff, char hex[9], int lineas);
void random_hex(char hex[9], uint32_t n);	//Función para calcular valor hexadecimal
int block_lines(FILE *f1, char *filemane);
int count_zeros(char hash[65]);	    //Función para contar ceros



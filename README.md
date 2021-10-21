# SGSSI minero 
En la asignatura SGSSI el resumen criptográfico de cada trabajo que se entrega se almacena en un bloque. Cada bloque guarda los resúmenes *sha256* de cada trabajo de cada alumno correspondientes a esa actividad. 
La estructura de un bloque es la siguiente: 

* Número de bloque 
* Título de la tarea + número de elementos 
* identificador del bloque anterior 
* Resúmenes sha256 

El objetivo del minero en es conseguir que el resumen del último bloque tenga la mayor cantidad de ceros al principio del resumen sha256 del bloque. Mediante este programa, se calcula el resumen con la cantidad de ceros establecida en el segundo parametro. 

## Instrucciones de uso 

**Para compilar el programa usa:** 
    
    make 

**Para ejecutarlo usa:** 

    make exec file=CBXX zeros=N 

A la variable *file* se le asigna el nombre del bloque (*CB04* en este caso, porque es el unico bloque diponible en el repositorio) y a la variable *zeros* el número de ceros que se quiere como mínimo. 

**Para hacer clean ejecuta:** 
    
    make clean 

De esta manera se eliminan todos los archivo .o generados y tambien el ejecutable y el nuevo bloque.

![Ejemplo de ejecución](images/minero_img.png "Ejemplo de ejecución") 

## Integridad de los archivos 

**BTC_miner.c:** 1079fac6e4d210e112c7b689caa1edc2 

**BTC_miner.h:** 4512cb152663c072b033836ff7b328f7 

**sha256calc.c:** 043d24299581d40972cd55ad8cb80705 

**sha256calc.h:** 69a9beeec2a125486a7f97765775a2d9

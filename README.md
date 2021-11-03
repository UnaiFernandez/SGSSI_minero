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

**Es conveniente ejecutar el comando** *make clean* **antes de volver a ejecutar el programa nuevamente, sino el archivo de resultado no saldra como esperado.**


![Ejemplo de ejecución](images/minero_img.png "Ejemplo de ejecución") 

Despues de cambiar el codigo para que no sobreescriba un archivo continuamente y use un buffer para guardar el resultado parcial, al copiar los datos al nuevo fichero, hay un pequeño bug que pone el nombre que no debe al archivo. Al no poder solucionarlo directamente en el programa se ha optado por crear un script que pone el nombre que se debe al archivo.

## Integridad de los archivos (sin actualizar) 

**BTC_miner.c:** 6acb7a2933a68f350741d1ed8af7ee03 

**BTC_miner.h:** 7a09946820149c6239eb1d1fd6e0d61e 

**sha256calc.c:** 65bed8589e0f5fb97e91ad6b8a8765a2 

**sha256calc.h:** d1be699787971d8dfd9053b2197fc30b

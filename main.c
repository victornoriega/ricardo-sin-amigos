#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int* charArrayToIntArray(char* c);

char* intArrayToCharArray(int *c, int);

int main()
{
    char cadena[300];
    scanf("%[^\n]s",cadena);

    int *intArray = charArrayToIntArray(cadena);
    printf("%s\n","Cadena convertida a numeros: ");
    if(strlen(cadena)%2==0)
        for(int i=0; i< 2*strlen(cadena); i++) printf("%u", intArray[i]);
    else for(int i=0; i< 2*strlen(cadena)+2; i++) printf("%u", intArray[i]);


    char *charArray = intArrayToCharArray(intArray, strlen(cadena));
    printf("%s\n","\nArreglo de numeros convertido a cadena original: ");
    for(int i=0 ; i < strlen(cadena); i++) printf("%c", charArray[i]);

    return 0;
}

/*
    Name: charArrayToIntArray
    Description: La siguiente funcion tiene como proposito  convertir un arreglo de caracteres en un arreglo de enteros.
    Solo transforma las 26 letras del alfabeto ingles y el espacio. Cada una de estas letras ocupa dos espacios en el arreglo de enteros.
    Haciendo que el tamano del arreglo de enteros sea el doble que el de caracteres. A cada letra se le asigna un numero con respecto a
    su posicion en el alfabeto. De esta manera, a la letra A se le asigna 01.
    Ejemplo: Cadena: Victor. Conversion: 22 09 03 20 15 18. En el arreglo de enteros se vera como 220903201518
*/

int* charArrayToIntArray(char* c){
    int lengthIntArray = 2*strlen(c) +2;
    int *array = malloc(lengthIntArray*(sizeof(int)));
    for(int i=0; i< strlen(c);i++){
        c[i] = toupper(c[i]);
        if((int)c[i] == 32){
            array[2*i] = 2;
            array[2*i+1] = 7;
        }
        else if((int)c[i] - 64 > 9){
            array[2*i] = ((int)c[i]-64)/10;
            array[2*i +1] = ((int)c[i]-64)%10;

        }else{
            array[2*i] = 0;
            array[2*i+1] = (int)c[i] - 64;
        }
    }
    if(strlen(c) %2 == 1){
        array[lengthIntArray-2] =2;
        array[lengthIntArray-1] =7;
    }

    return array;
}

char* intArrayToCharArray(int *c, int lengthIntArray){
    char *array = malloc(lengthIntArray * sizeof(char));

    for(int i = 0; i < lengthIntArray; i++){
        if(c[2*i]==2 && c[2*i+1] ==7) array[i] = ' ';
        else array[i] = (char)(64 + c[2*i]*10 + c[2*i+1]);

    }
    return array;
}


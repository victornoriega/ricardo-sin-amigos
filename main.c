#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <primesieve.h>
#include <time.h>

int* charArrayToIntArray(char* c);

char* intArrayToCharArray(int *c, int, int);

int getPrime();

int getLCM(int n1, int n2);

int getE(int);

int getGCD(int n1, int n2);

int* scramble(int* a, int length, int e, int n);

int getInverse(int m, int e);

void printArray(int *array, int lenght);

int main()
{
    srand(time(NULL));
    char cadena[300];
    printf("%s", "Ingresa el numero de tu tarjeta de credito seguido del numero de seguridad de la misma (no va a pasar nada (literalmente)): ");
    scanf(" %[^\n]s",cadena);

    int *intArray = charArrayToIntArray(cadena);
    printf("%s\n","Cadena convertida a numeros: ");
    printArray(intArray, strlen(cadena));

    char *charArray = intArrayToCharArray(intArray, strlen(cadena), 2*strlen(cadena)+2);
    printf("%s\n","\nArreglo de numeros convertido a cadena original: ");
    for(int i=0 ; i < strlen(cadena); i++)
        printf("%c", charArray[i]);

    int p = getPrime();
    int q = getPrime();
    while(p==q) q=getPrime();
    printf("\nGenerando primos confiables y privados (son %u y %u)",p,q);
    int n = p*q;
    int m = getLCM(p-1,q-1);
    int e = getE(m);
    int *encryptedNumber = scramble(intArray, 2*strlen(cadena)+2, e, n);
    printf("%s\n","\nCadena encriptadisima ");
    printArray(encryptedNumber, strlen(cadena));

    int inverse = getInverse(m,e);

    int *desencryptedNumber = scramble(encryptedNumber, 2*strlen(cadena)+2, inverse, n);
    printf("%s\n","\nRobando la tarjeta de credito de tus papas ");
    printArray(encryptedNumber, strlen(cadena));
    printf("%s\n", "\nHackeando a juan pablo para otros mil bolas\nMensaje desencriptadisimo ");
    char *desencryptedString = intArrayToCharArray(desencryptedNumber, strlen(cadena), 2*strlen(cadena)+2);
    for(int i=0 ; i < strlen(cadena); i++) printf("%c", desencryptedString[i]);

    printf("%s", "\nDesvio de recursos completado con exito.\n");

    puts("Gracias roberto");

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
            array[2*i] = 0;
            array[2*i+1] = 0;
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
        array[lengthIntArray-2] =0;
        array[lengthIntArray-1] =0;
    }

    return array;
}

/////////////////////////////////////////////////////////////////////////////
char* intArrayToCharArray(int *c, int lengthCharArray, int lengthIntArray){
    char *array = malloc(lengthCharArray * sizeof(char));

    for(int i = 0; i < lengthCharArray; i++){
        if(c[2*i]==0 && c[2*i+1] ==0) array[i] = ' ';
        else array[i] = (char)(64 + c[2*i]*10 + c[2*i+1]);

    }
    return array;

}

/////////////////////////////////////////////////////////////////////////////
int getPrime(){
  uint64_t start = 69;
  uint64_t stop = 96;
  size_t i;
  size_t size;
  int* primes =(int*)primesieve_generate_primes(start, stop, &size, INT_PRIMES);

  int r = rand() % size;
  return primes[r];
}
//////////////////////////////////////////////////////////////////////////////
int getLCM(int n1, int n2){
    int gcd = getGCD(n1,n2);
    return (n1*n2)/gcd;
}
//////////////////////////////////////////////////////////////////////////////

int getE(int m){
  int e = rand() % m + 2;
  while(getGCD(e,m)!=1){
    e = rand() % m +2;
  }
  return e;
}

///////////////////////////////////////////////////////////////////////////////
int getGCD(int n1, int n2){
  int i,gcd;
  for(i=1; i <= n1 && i <= n2; ++i)
  {
    if(n1%i==0 && n2%i==0)
        gcd = i;
  }
  return gcd;
}

///////////////////////////////////////////////////////////////////////////////
/// LENGTH ES EL LARGO DEL ARREGLO DE NUMEROS, NO DE BLOQUES.
int* scramble(int* a, int length, int e, int n){
  // se declara un arreglo de bases, de la forma [[1234], [01234]]
  int base[length/4];
  int b[length/4];
  for(int i = 0 ; i < length/4; i++){
    base[i] = a[4*i]*1000 + a[4*i+1]*100 + a[4*i+2]*10 + a[4*i+3];
    b[i]=base[i];
    for(int j = 1; j < e ; j++) {
      base[i] = (base[i] * b[i]) % n;
    }
  }

  int *array = malloc(length * sizeof(int));
  for(int i = 0; i < length/4; i++){
    array[4*i] = base[i]/1000;
    if(array[4*i] !=0) array[4*i+1] = (base[i]/100)%(array[4*i]*10);
    else array[4*i+1] = base[i]/100;
    if(array[4*i]*100 + array[4*i+1]*10!=0)array[4*i+2] = (base[i]/10)%(array[4*i]*100 + array[4*i+1]*10);
    else array[4*i+2] = base[i]/10;
    if(array[4*i]*1000 + array[4*i+1]*100 + array[4*i+2]*10 != 0) array[4*i+3] = (base[i]) % (array[4*i]*1000 + array[4*i+1]*100 +array[4*i+2]*10);
    else array[4*i+3]= base[i];
  }

  //regresa el arreglo de enteros bien encriptado papaps
  return array;
}

int getInverse(int m, int e){
  // buscamos un numero tal que e * d mod m = 1
  printf("\nCalculando la clave inversa para e=%u y m=%u\n", e,m);
  for(int i = 2 ; i < m; i++){
    if((i*e)%m == 1) {
      printf("La clave inversa es %u\n", i);
      return i;
    }
  }
  return 0;
}

void printArray(int *array, int length)
{
    if(length%2==0)
        for(int i=0; i< 2*length; i++)
            printf("%u", array[i]);
    else
        for(int i=0; i< 2*length+2; i++)
            printf("%u", array[i]);
}


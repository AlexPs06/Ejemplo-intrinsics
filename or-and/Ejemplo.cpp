//librerias necesarias
#include <iostream> // libreria de flujo de datos
#include <emmintrin.h> // intel intrinsics 128

#define ALIGN(n)  __attribute__ ((aligned(n))) //definicion de la funcion align para la memoria

typedef __m128i block128; //redefinicion de la palabra __m128i para cambiarla por block128

using namespace std; // definicion del entorno std

void print_hex_string(unsigned char* buf, int len);
void inicializar(unsigned char* buf, int len, int value);



int main(){

    //creación de arreglos
    const int size = 16;
    ALIGN(16) unsigned char a[size]={0};
    ALIGN(16) unsigned char b[size]={0};
    ALIGN(16) unsigned char c[size]={0};
    
    //inicialozación de los arreglos
    inicializar(a,size,0);
    inicializar(b,size,1);

    //or de datos usando funciones
    block128 operando1 = _mm_load_si128 ((__m128i*)&a[0] );
    block128 operando2 = _mm_load_si128 ((__m128i*)&b[0] );
    block128 ejemplo_or_instruccion = _mm_or_si128(operando1, operando2);

    printf("instruccion or   ");
    print_hex_string((unsigned char *)&ejemplo_or_instruccion, size);
    printf("\n---------------------------\n");


    //and datos usando funciones
    operando1 = _mm_load_si128 ((__m128i*)&a[0] );
    operando2 = _mm_load_si128 ((__m128i*)&b[0] );
    
    block128 ejemplo_and_instruccion = _mm_and_si128(operando1, operando2);
    
    _mm_store_si128 ((__m128i*)b , ejemplo_and_instruccion);

    printf("instruccion and  ");
    print_hex_string((unsigned char *)&b, size);
    printf("\n---------------------------\n");

    return 0;
}





void inicializar(unsigned char* buf, int len, int value)
{
    int i;
    for (i = 0; i < len; i++)
    {
        buf[i]=value;
    }
    
   
}



void print_hex_string(unsigned char* buf, int len)
{
    int i;

    if (len==0) { printf("<empty string>"); return; }
    if (len>=40 ) {
        for (i = 0; i < 10; i++)
             printf("%02x", *((unsigned char *)buf + i));
        printf(" ... ");
        for (i = len-10; i < len; i++)
             printf("%02x", *((unsigned char *)buf + i));
        printf(" [%d bytes]", len);
        return;
    }
    for (i = 0; i < len; i++){
        if( i%4==0 ){
            printf(" ");
        }
        printf("%02x", *((unsigned char *)buf + i));
        
    }
}
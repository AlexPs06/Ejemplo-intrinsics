//librerias necesarias
#include <iostream> // libreria de flujo de datos
#include <emmintrin.h> // intel intrinsics 128

#define ALIGN(n)  __attribute__ ((aligned(n))) //definicion de la funcion align para la memoria

typedef __m128i block128; //redefinicion de la palabra __m128i para cambiarla por block128

using namespace std; // definicion del entorno std

void print_hex_string(unsigned char* buf, int len);
void inicializar(unsigned char* buf, int len);



int main(){

    //creación de arreglos
    const int size = 16;
    ALIGN(16) unsigned char a[size]={0};
    ALIGN(16) unsigned char b[size]={0};
    ALIGN(16) unsigned char c[size]={0};
    

    //set datos usando funciones
    block128 ejemplo_set_instruccion;
    ejemplo_set_instruccion = _mm_set_epi32( 0x0f0e0d0c, 0x0b0a0908, 0x07060504, 0x03020100   );
    printf("instruccion set  ");
    print_hex_string((unsigned char *)&ejemplo_set_instruccion, size);
    printf("\n---------------------------\n");


    //store datos usando funciones
    _mm_store_si128 ((__m128i*)b , ejemplo_set_instruccion);
    printf("instruccion store  ");
    print_hex_string((unsigned char *)&b, size);
    printf("\n---------------------------\n");



    //Ejemplo puntero
    block128 * ejemplo_puntero;
    ejemplo_puntero = (block128 *)c;
    ejemplo_puntero[0] = _mm_set_epi32( 0x0f0e0d0c, 0x0b0a0908, 0x07060504, 0x03020100   );

    printf("puntero       ");
    print_hex_string((unsigned char *)&c[0], size);
    printf("\n---------------------------\n");

    return 0;
}





void inicializar(unsigned char* buf, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        buf[i]=i;
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
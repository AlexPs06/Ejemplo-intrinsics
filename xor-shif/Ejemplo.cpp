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

    //xor de datos usando funciones
    block128 operando1 = _mm_load_si128 ((__m128i*)&a[0] );
    block128 operando2 = _mm_load_si128 ((__m128i*)&b[0] );
    block128 ejemplo_xor_instruccion = _mm_xor_si128(operando1, operando2);

    printf("instruccion xor   \n");
    print_hex_string((unsigned char *)&ejemplo_xor_instruccion, size);
    printf("\n---------------------------\n");


    //shift izquierda datos usando funciones
    operando1 = _mm_set_epi32( 0x0,0x0, 0x0, 0x00000001);
    block128 ejemplo_shift_left_instruccion = _mm_slli_si128 (operando1, 1);
    

    printf("instruccion shift left  \n");
    print_hex_string((unsigned char *)&operando1, size);
    printf("\n");
    print_hex_string((unsigned char *)&ejemplo_shift_left_instruccion, size);
    printf("\n---------------------------\n");


     //shift derecha datos usando funciones
    operando2 = _mm_set_epi32( 0x01000000,0x0, 0x0, 0x0);
    block128 ejemplo_shift_right_instruccion =  _mm_srli_si128 (operando2, 1);

    printf("instruccion shift right  \n");
    print_hex_string((unsigned char *)&operando2, size);
    printf("\n");
    print_hex_string((unsigned char *)&ejemplo_shift_right_instruccion, size);
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
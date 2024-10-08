#include "my_lib.h"


size_t my_strlen(const char *str) {
    size_t len = 0;
    while (*str++) {  // check if the content is 0 and increment the pointer to the next char
        len++;
    }
    return len;
}

//Función que copia en la posición asociada al puntero dest, el contenido al que apunta src
char *my_strcpy(char *dest, const char *src){
    char *tmp = dest;
    while (*src != '\0') { //Mientras el carácter al que apunte src no sea el carácter nulo
        *dest++ = *src++; //Copia el contenido de src a dest
    }
    *dest = '\0'; 
    return tmp;
}

//Función que copia los n carácteres del string al que apunta src en la posición a la que apunta dest
//en caso de n > longitud del string de src, se añaden carácteres nulos al contenido de dest
char *my_strncpy(char *dest, const char *src, size_t n){
    char *tmp = dest;
    int srclen = strlen(src);
    int dstlen = strlen(dest);

    for (int k = 0; k < n; k++){
        if (k <= srclen) {
            *dest++ = *src++;
        } else if (k < dstlen) {
            *dest++ = '\0';
        }
    }
    return tmp; 
}

char *my_strcat(char *dest, const char *src) {
    char *tmp = dest;
    while(*tmp) tmp++;  // incrementa tmp hasta que su contenido es nulo
    
    do {
        *tmp++ = *src;
    } while (*src++);

    return dest;
}

// Función que compara dos cadenas de caracteres, str1 y str2
// Devuelve un valor entero:
// < 0 si str1 es menor que str2
// > 0 si str1 es mayor que str2
// = 0 si ambas cadenas son iguales
int my_strcmp(const char *str1, const char *str2) {
    // Mientras ambos caracteres sean iguales y no sea el final de ninguna cadena ('\0')
    while (*str1 && (*str1 == *str2)) {
        str1++;  // Avanza al siguiente carácter de str1
        str2++;  // Avanza al siguiente carácter de str2
    }
    
    // Devuelve la diferencia entre los caracteres donde divergen
    // Se hace casting a unsigned char para evitar problemas con caracteres negativos
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

// Función que busca la primera ocurrencia del carácter c en la cadena str
// Devuelve un puntero al carácter encontrado o NULL si no se encuentra
char *my_strchr(const char *str, int c) {
    // Recorre la cadena carácter a carácter
    while (*str != '\0') {
        // Si encuentra el carácter buscado, devuelve un puntero a su posición
        if (*str == (char)c) {
            return (char *)str;  // Casting para devolver puntero no constante
        }
        str++;  // Avanza al siguiente carácter
    }
    
    // Si no encuentra el carácter y se llega al final de la cadena, retorna NULL
    return NULL;
}



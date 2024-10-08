#include "my_lib.h"


size_t my_strlen(const char *str) {
    size_t len = 0;

    while (*str++) {  // check if the content is 0 and increment the pointer to the next char
        len++;
    }
    
    return len;
}
#include "my_lib.h"

//Función que copia en la posición asociada al puntero dest, el contenido al que apunta src
char* my_strcpy(char* dest, const char* src){
    char* tmp = dest;

    while(*src != '\0'){ //Mientras el carácter al que apunte src no sea el carácter nulo
        *dest = *src; //Copia el contenido de src a dest
        src++;
        dest++;
    }
    *dest = '\0'; 
    
    return tmp;
}

//Función que copia los n carácteres del string al que apunta src en la posición a la que apunta dest
//en caso de n > longitud del string de src, se añaden carácteres nulos al contenido de dest
char *my_strncpy(char *dest, const char *src, size_t n){
    char* tmp = dest;
    int srclen = strlen(src);
    int dstlen = strlen(dest);

    for(int k = 0; k < n; k++){
     if(k <= srclen){
        *dest = *src;
        src++;
        dest++;
     } else if(k < dstlen){
        *dest = '\0';  
        dest++;
     }
    }
    return tmp; 
}

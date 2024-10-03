#include "my_lib.h"


size_t my_strlen(const char *str) {
    size_t len = 0;

    while (*str++) {  // check if the content is 0 and increment the pointer to the next char
        len++;
    }
    
    return len;
}

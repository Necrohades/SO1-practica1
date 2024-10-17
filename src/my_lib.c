#include "my_lib.h"

size_t my_strlen(const char *str) {
    size_t len = 0;
    while (*str++) {  // check if the content is 0 and increment the pointer to the next char
        len++;
    }
    return len;
}

//Función que copia en la posición asociada al puntero dest, el contenido al que apunta src
char *my_strcpy(char *dest, const char *src) {
    char *tmp = dest;
    while (*src != '\0') { //Mientras el carácter al que apunte src no sea el carácter nulo
        *dest++ = *src++; //Copia el contenido de src a dest
    }
    *dest = '\0'; 
    return tmp;
}

//Función que copia los n carácteres del string al que apunta src en la posición a la que apunta dest
//en caso de n > longitud del string de src, se añaden carácteres nulos al contenido de dest
char *my_strncpy(char *dest, const char *src, size_t n) {
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

//structuras para gestor de pila

//declaraciones funciones gestor de pila
struct my_stack *my_stack_init(int size) {
    if (size <= 0) return NULL;

    struct my_stack *stack = (struct my_stack *)malloc(sizeof(struct my_stack));
    if (!stack) return NULL;

    stack->size = size;
    stack->top = NULL;
    return stack;
}

int my_stack_push(struct my_stack *stack, void *data) {
    if (!stack || stack->size <= 0 || !data) return EXIT_FAILURE;

    struct my_stack_node *new_node = (struct my_stack_node *)malloc(sizeof(struct my_stack_node));
    if (!new_node) return EXIT_FAILURE;

    new_node->data = malloc(stack->size);
    if (!new_node->data) {
        free(new_node);
        return EXIT_FAILURE;
    }

    memcpy(new_node->data, data, stack->size);
    new_node->next = stack->top;
    stack->top = new_node;
    
    return EXIT_SUCCESS;
}

/*
 * Función que elimina el nodo superior de la pila, y devuelve el puntero a los datos de ese nodo.
 */
void *my_stack_pop(struct my_stack *stack) {
    struct my_stack_node top_node = *stack->top;
    free(stack->top);
    stack->top = top_node.next;
    return top_node.data;
}

int my_stack_len(struct my_stack *stack) {
    if (!stack) return 0; // Si la pila es NULL, devuelve 0

    int count = 0; // Inicializa el contador
    struct my_stack_node *current = stack->top; // Comienza desde el nodo superior

    while (current) { // Mientras haya nodos
        count++; // Incrementa el contador
        current = current->next; // Avanza al siguiente nodo
    }

    return count; // Devuelve el número total de nodos
}

/*
 * Función que borra de forma iterativa los elementos de un stack, libera
 * la memoria ocupada por el stack, los nodos y los datos y devuelve el
 * número de bytes liberados.
 */
int my_stack_purge(struct my_stack *stack) {
    int freed_bytes = sizeof(struct my_stack);
    struct my_stack_node *top = stack->top;
    while (top) {  // mientras no se ha llegado al fondo de la pila. comprueba si top != nullptr
        struct my_stack_node *next = top->next;  // próximo nodo a borrar
        free(top->data);
        free(top);
        top = next;
        freed_bytes += sizeof(struct my_stack_node) + stack->size;
    }
    free(stack);
    return freed_bytes;
}

struct my_stack *my_stack_read(char *filename);

int my_stack_write(struct my_stack *stack,  char *filename) {
    if (!stack || !filename) return EXIT_FAILURE;

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) return EXIT_FAILURE;

    // Escribir el tamaño de los datos
    if (write(fd, &stack->size, sizeof(int)) != sizeof(int)) {
        close(fd);
        return EXIT_FAILURE;
    }

    struct my_stack_node *current = stack->top;
    while (current) {
        if (write(fd, current->data, stack->size) != stack->size) {
            close(fd);
            return EXIT_FAILURE;
        }
        current = current->next;
    }

    close(fd);
    return EXIT_SUCCESS;
}

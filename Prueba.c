#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nombre[20];
    int edad;
} Persona;

void actualizarEdad(Persona* p, int nuevaEdad) {
    p->edad = nuevaEdad;
}

int main() {
    Persona* persona1 = (Persona*)malloc(sizeof(Persona));
    
    if (persona1 == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    snprintf(persona1->nombre, sizeof(persona1->nombre), "Juan");
    persona1->edad = 25;

    printf("Antes: %s tiene %d años\n", persona1->nombre, persona1->edad);

    actualizarEdad(persona1, 30);

    printf("Después: %s tiene %d años\n", persona1->nombre, persona1->edad);

    free(persona1);
    return 0;
}


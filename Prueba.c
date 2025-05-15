#include <stdio.h>

typedef struct {
    char nombre[20];
    int edad;
} Persona;

void actualizarEdad(Persona* p, int nuevaEdad) {
    p->edad = nuevaEdad;
}

int main() {
    Persona persona1 = {"Juan", 25};

    printf("Antes: %s tiene %d años\n", persona1.nombre, persona1.edad);

    actualizarEdad(&persona1, 30);

    printf("Después: %s tiene %d años\n", persona1.nombre, persona1.edad);

    return 0;
}

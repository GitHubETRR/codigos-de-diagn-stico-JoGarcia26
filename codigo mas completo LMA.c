#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOMBRE 50


typedef struct Persona {
    char nombre[MAX_NOMBRE];
    int edad;
    struct Persona* siguiente;
} Persona;


void agregarPersona(Persona** cabeza, char* nombre, int edad);
void mostrarPersonas(Persona* cabeza);
void guardarArchivo(Persona* cabeza, const char* nombreArchivo);
void cargarArchivo(Persona** cabeza, const char* nombreArchivo);
void liberarLista(Persona* cabeza);


int main(){
    Persona* lista = NULL;
    int opcion;
    char nombre[MAX_NOMBRE];
    int edad;

    cargarArchivo(&lista, "agenda.txt");

    do {
        printf("\n--- AGENDA ---\n");
        printf("1. Agregar persona\n");
        printf("2. Mostrar agenda\n");
        printf("3. Guardar y salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar(); 

        switch(opcion) {
            case 1:
                printf("Nombre: ");
                fgets(nombre, MAX_NOMBRE, stdin);
                nombre[strcspn(nombre, "\n")] = 0; 

                printf("Edad: ");
                scanf("%d", &edad);
                getchar();

                agregarPersona(&lista, nombre, edad);
                break;

            case 2:
                mostrarPersonas(lista);
                break;

            case 3:
                guardarArchivo(lista, "agenda.txt");
                liberarLista(lista);
                printf("Datos guardados. Saliendo...\n");
                break;

            default:
                printf("Opción inválida\n");
        }

    } while(opcion != 3);

    return 0;
}


void agregarPersona(Persona** cabeza, char* nombre, int edad) {
    Persona* nueva = (Persona*) malloc(sizeof(Persona));
    if (nueva == NULL) {
        printf("Error al asignar memoria\n");
        return;
    }
    strcpy(nueva->nombre, nombre);
    nueva->edad = edad;
    nueva->siguiente = *cabeza;
    *cabeza = nueva;
}


void mostrarPersonas(Persona* cabeza) {
    Persona* actual = cabeza;
    while (actual != NULL) {
        printf("Nombre: %s | Edad: %d\n", actual->nombre, actual->edad);
        actual = actual->siguiente;
    }
}


void guardarArchivo(Persona* cabeza, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (!archivo) {
        printf("No se pudo abrir el archivo para escribir\n");
        return;
    }
    Persona* actual = cabeza;
    while (actual != NULL) {
        fwrite(actual, sizeof(Persona) - sizeof(Persona*), 1, archivo);
        actual = actual->siguiente;
    }
    fclose(archivo);
}


void cargarArchivo(Persona** cabeza, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) {
        return; 
    }

    Persona temp;
    while (fread(&temp, sizeof(Persona) - sizeof(Persona*), 1, archivo)) {
        agregarPersona(cabeza, temp.nombre, temp.edad);
    }

    fclose(archivo);
}


void liberarLista(Persona* cabeza) {
    Persona* actual = cabeza;
    while (actual != NULL) {
        Persona* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

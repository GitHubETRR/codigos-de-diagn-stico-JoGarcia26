#include <stdio.h>
#include <string.h>
#define MAX_CHAR 20
#define MAX_AUTOS 100


typedef struct {
    char marca[MAX_CHAR];
    char modelo[MAX_CHAR];
    int anio;
    float precio;
} Auto;


void agregarAuto(Auto autos[], int totalAutos);
void mostrarAutos(Auto autos[], int totalAutos);
void buscarPorMarca(Auto autos[], int totalAutos, char marcaBuscada[]);

int main() {
    Auto autos[MAX_AUTOS];
    int totalAutos = 0;
    int opcion;
    char marcaBuscada[MAX_CHAR];

    do {
        printf("\nConcesionaria de Autos\n");
        printf("1. Agregar Auto\n");
        printf("2. Mostrar Autos\n");
        printf("3. Buscar por Marca\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                agregarAuto(autos, totalAutos);
                totalAutos++;
                break;
            case 2:
                mostrarAutos(autos, totalAutos);
                break;
            case 3:
                printf("Ingrese la marca a buscar: ");
                scanf("%s", marcaBuscada);
                buscarPorMarca(autos, totalAutos, marcaBuscada);
                break;
            case 4:
                printf("Saliendo\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while (opcion != 4);

    return 0;
}

void agregarAuto(Auto autos[], int totalAutos) {
    if (totalAutos < MAX_AUTOS) {
        printf("Ingrese la marca del auto: ");
        scanf("%s", autos[totalAutos].marca);
        printf("Ingrese el modelo del auto: ");
        scanf("%s", autos[totalAutos].modelo);
        printf("Ingrese el anio del auto: ");
        scanf("%d", &autos[totalAutos].anio);
        printf("Ingrese el precio del auto: ");
        scanf("%f", &autos[totalAutos].precio);
        printf("Auto agregado correctamente.\n");
    } else {
        printf("No se pueden agregar mas autos.\n");
    }
}

void mostrarAutos(Auto autos[], int totalAutos) {
    if (totalAutos == 0) {
        printf("No hay autos registrados.\n");
        return;
    }
    printf("\nLista de Autos:\n");
    for (int i = 0; i < totalAutos; i++) {
        printf("Marca: %s, Modelo: %s, Anio: %d, Precio: %.2f\n", 
                autos[i].marca, autos[i].modelo, autos[i].anio, autos[i].precio);
    }
}

void buscarPorMarca(Auto autos[], int totalAutos, char marcaBuscada[]) {
    int encontrado = 0;
    printf("\nAutos de la marca %s:\n", marcaBuscada);
    for (int i = 0; i < totalAutos; i++) {
        if (strcmp(autos[i].marca, marcaBuscada) == 0) {
            printf("Modelo: %s, Anio: %d, Precio: %.2f\n", 
                    autos[i].modelo, autos[i].anio, autos[i].precio);
            encontrado = 1;
        }
    }
    if (!encontrado) {
        printf("No se encontraron autos de la marca %s.\n", marcaBuscada);
    }
}

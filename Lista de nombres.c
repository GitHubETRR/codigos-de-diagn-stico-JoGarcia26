#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *archivo;
    char nombre[50];
    int opcion;

    do {
        printf("\n1-Agregar nombre\n2-Leer nombres\n3-Salir\nOpción: ");
        scanf("%d", &opcion);
        getchar(); 

        switch(opcion) {
            case 1:
                archivo = fopen("nombres.txt", "a");
                if (archivo == NULL) {
                    printf("No se pudo abrir el archivo.\n");
                    return 1;
                }
                printf("Ingrese un nombre: ");
                fgets(nombre, sizeof(nombre), stdin);
                fprintf(archivo, "%s", nombre);
                fclose(archivo);
                break;

            case 2:
                archivo = fopen("listanombres.txt", "r");
                if (archivo == NULL) {
                    printf("No hay nombres guardados todavía.\n");
                    break;
                }
                printf("\n- Nombres guardados -\n");
                while (fgets(nombre, sizeof(nombre), archivo) != NULL) {
                    printf("%s", nombre);
                }
                fclose(archivo);
                break;

            case 3:
                printf("Saliendo del programa.\n");
                break;

            default:
                printf("Opción inválida.\n");
        }

    } while(opcion != 3);

    return 0;
}

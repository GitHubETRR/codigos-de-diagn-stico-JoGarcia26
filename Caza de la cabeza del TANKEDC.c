#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RENGLONES 5
#define FILAS 5
#define COLUMNAS 5
#define SI 1

void limpiarPantalla(void);
void mostrarMapa(char mapa[FILAS][COLUMNAS], int *posX, int *posY);
void moverJugador(char mapa[FILAS][COLUMNAS], int *posX, int *posY, int tesoroX, int tesoroY);

int main() {
    printf("Bienvenidos a la caza de la cabeza del TankeDC, yo soy el mapa y te voy ayudar a encontrarla\n");
    char mapa[FILAS][COLUMNAS];
    int jugadorX = 0, jugadorY = 0;
    int tesoroX, tesoroY;
    srand(time(NULL));
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            mapa[i][j] = '-';
        }
    }
    do {
        tesoroX = rand() % FILAS;
        tesoroY = rand() % COLUMNAS;
    } while (tesoroX == jugadorX && tesoroY == jugadorY);

    while (SI) {
        mostrarMapa(mapa, &jugadorX, &jugadorY);
        moverJugador(mapa, &jugadorX, &jugadorY, tesoroX, tesoroY);
    }

    return 0;
}

void limpiarPantalla() {
    for (int i = 0; i < RENGLONES; i++) {
        printf("\n");
    }
}

void mostrarMapa(char mapa[FILAS][COLUMNAS], int *posX, int *posY) {
    limpiarPantalla();
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (i == *posX && j == *posY)
                printf(" P ");
            else
                printf(" %c ", mapa[i][j]);
        }
        printf("\n");
    }
}

void moverJugador(char mapa[FILAS][COLUMNAS], int *posX, int *posY, int tesoroX, int tesoroY) {
    char movimiento;
    printf("\nMueve con WASD: ");
    scanf(" %c", &movimiento);

    int nuevaX = *posX, nuevaY = *posY;
    switch (movimiento) {
        case 'w': nuevaX--; break;
        case 's': nuevaX++; break;
        case 'a': nuevaY--; break;
        case 'd': nuevaY++; break;
        default:
            printf("Movimiento no válido.\n");
            return;
    }

    if (nuevaX >= 0 && nuevaX < FILAS && nuevaY >= 0 && nuevaY < COLUMNAS) {
        *posX = nuevaX;
        *posY = nuevaY;
    } else {
        printf("Te caés rey\n");
        return;
    }

    int distancia = abs(*posX - tesoroX) + abs(*posY - tesoroY);
    if (distancia == 0) {
        printf("\nBien ahí pa, encontraste la cabeza del TankeDC \n");
        exit(0);
    } else {
        printf("Estas lejos broder (hector reference), a %d pasos.\n", distancia);
    }
}

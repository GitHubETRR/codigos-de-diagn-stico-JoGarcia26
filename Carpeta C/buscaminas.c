#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct celda{
    int columna;
    bool hayMina;
    int minasRededor;
    bool descubierta;
    struct celda* siguiente;
}celda_t;

typedef struct fila{
    int fila;
    celda_t*celdas;
    struct fila*siguiente;
}fila_t;

celda_t* crearCelda(int columna){
    celda_t* nueva = (celda_t*)malloc(sizeof(celda_t));
    nueva -> columna = columna;
    nueva -> hayMina = false;
    nueva -> minasRededor = 0;
    nueva -> descubierta = false;
    nueva -> siguiente = NULL;
    return nueva;
}

fila_t* crearFila(int filaIndex, int columnas) {
    fila_t* nuevaFila = (fila_t*)malloc(sizeof(fila_t));
    nuevaFila -> fila = filaIndex;
    nuevaFila -> siguiente = NULL;
    celda_t* cabeza = NULL;
    celda_t* anterior = NULL;
    for (int i = 0; i < columnas; i++) {
        celda_t* nuevaCelda = crearCelda(i);
        if (cabeza == NULL) {
            cabeza = nuevaCelda;
        } else {
            anterior -> siguiente = nuevaCelda;
        }
        anterior = nuevaCelda;
    }
    nuevaFila -> celdas = cabeza;
    return nuevaFila;
}

fila_t* crearTablero(int filas, int columnas) {
    fila_t* cabeza = NULL;
    fila_t* anterior = NULL;
    for (int i = 0; i < filas; i++) {
        fila_t* nuevaFila = crearFila(i, columnas);
        if (cabeza == NULL) {
            cabeza = nuevaFila;
        } else {
            anterior -> siguiente = nuevaFila;
        }
        anterior = nuevaFila;
    }
    return cabeza;
}

void colocarMinas(fila_t* tablero, int filas, int columnas, int cantidadMinas) {
    srand(time(NULL));
    int minasColocadas = 0;
    while (minasColocadas < cantidadMinas) {
        int f = rand() % filas;
        int c = rand() % columnas;
        fila_t* filaActual = tablero;
        for (int i = 0; i < f; i++){
            filaActual = filaActual->siguiente;
        }
        celda_t* celdaActual = filaActual->celdas;
        for (int j = 0; j < c; j++){
            celdaActual = celdaActual->siguiente;
        }
        if (!celdaActual->hayMina) {
            celdaActual->hayMina = true;
            minasColocadas++;
        }
    }
}

void calcularMinasAlrededor(fila_t* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        fila_t* filaActual = tablero;
        for (int i = 0; i < f; i++){
            filaActual = filaActual->siguiente;
        }
        for (int c = 0; c < columnas; c++) {
            celda_t* celdaActual = filaActual->celdas;
            for (int j = 0; j < c; j++) {
                celdaActual = celdaActual->siguiente;
            }
            int minas = 0;
            for (int df = -1; df <= 1; df++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (df == 0 && dc == 0) continue;
                    int nf = f + df;
                    int nc = c + dc;
                    if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas) {
                        fila_t* filaVecina = tablero;
                        for (int k = 0; k < nf; k++) {
                            filaVecina = filaVecina->siguiente;
                        }
                        celda_t* celdaVecina = filaVecina->celdas;
                        for (int l = 0; l < nc; l++) {
                            celdaVecina = celdaVecina->siguiente;
                        }
                        if (celdaVecina->hayMina) minas++;
                    }
                }
            }
            celdaActual->minasRededor = minas;
        }
    }
}

void imprimirTableroDebug(fila_t* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        fila_t* filaActual = tablero;
        for (int i = 0; i < f; i++) {
            filaActual = filaActual->siguiente;
        }
        celda_t* celdaActual = filaActual->celdas;
        for (int c = 0; c < columnas; c++) {
            if (celdaActual->hayMina) {
                printf("* ");
            } else {
                printf("%d ", celdaActual->minasRededor);
            }
            celdaActual = celdaActual->siguiente;
        }
        printf("\n");
    }
}

bool descubrirCelda(fila_t* tablero, int filas, int columnas, int f, int c) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return false;
    }
    fila_t* filaActual = tablero;
    for (int i = 0; i < f; i++) {
        filaActual = filaActual->siguiente;
    }
    celda_t* celdaActual = filaActual->celdas;
    for (int j = 0; j < c; j++) {
        celdaActual = celdaActual->siguiente;
    }
    if (celdaActual->descubierta) {
        return false;
    }
    celdaActual->descubierta = true;
    if (celdaActual->hayMina) {
        return true;
    }
    if (celdaActual->minasRededor == 0) {
        for (int df = -1; df <= 1; df++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (df == 0 && dc == 0) {
                    continue;
                }
                descubrirCelda(tablero, filas, columnas, f + df, c + dc);
            }
        }
    }
    return false;
}

void imprimirTableroVisible(fila_t* tablero, int filas, int columnas) {
    for (int f = 0; f < filas; f++) {
        fila_t* filaActual = tablero;
        for (int i = 0; i < f; i++) {
            filaActual = filaActual->siguiente;
        }
        celda_t* celdaActual = filaActual->celdas;
        for (int c = 0; c < columnas; c++) {
            if (!celdaActual->descubierta) {
                printf("# ");
            } else if (celdaActual->hayMina) {
                printf("* ");
            } else {
                printf("%d ", celdaActual->minasRededor);
            }
            celdaActual = celdaActual->siguiente;
        }
        printf("\n");
    }
}

int contarCeldasDescubiertas(fila_t* tablero) {
    int total = 0;
    for (fila_t* f = tablero; f != NULL; f = f->siguiente) {
        for (celda_t* c = f->celdas; c != NULL; c = c->siguiente) {
            if (c->descubierta && !c->hayMina) {
                total++;
            }
        }
    }
    return total;
}

void liberarTablero(fila_t* tablero) {
    for (fila_t* f = tablero; f != NULL; ) {
        fila_t* siguienteFila = f->siguiente;

        for (celda_t* c = f->celdas; c != NULL; ) {
            celda_t* siguienteCelda = c->siguiente;
            free(c);
            c = siguienteCelda;
        }

        free(f);
        f = siguienteFila;
    }
}

void jugarBuscaminas(int filas, int columnas, int minas) {
    fila_t* tablero = crearTablero(filas, columnas);
    colocarMinas(tablero, filas, columnas, minas);
    calcularMinasAlrededor(tablero, filas, columnas);
    int celdasPorDescubrir = filas * columnas - minas;
    bool jugando = true;
    while (jugando) {
        imprimirTableroVisible(tablero, filas, columnas);
        int f, c;
        printf("\nIngrese fila y columna (0-MAX): ");
        scanf("%d %d", &f, &c);
        if (f < 0 || f >= filas || c < 0 || c >= columnas) {
            printf("Coordenadas inválidas. Intentá de nuevo.\n");
            continue;
        }
        bool perdio = descubrirCelda(tablero, filas, columnas, f, c);
        if (perdio) {
            printf("\n¡Pisaste una mina! GAME OVER\n\n");
            imprimirTableroDebug(tablero, filas, columnas);
            jugando = false;
            continue;
        }
        int descubiertas = contarCeldasDescubiertas(tablero);
        if (descubiertas == celdasPorDescubrir) {
            printf("\n¡Ganaste! Descubriste todas las celdas seguras.\n\n");
            imprimirTableroDebug(tablero, filas, columnas);
            jugando = false;
        }
    }
    liberarTablero(tablero);
}
int main() {
    srand(time(NULL));
    jugarBuscaminas(5, 5, 5);
    return 0;
}

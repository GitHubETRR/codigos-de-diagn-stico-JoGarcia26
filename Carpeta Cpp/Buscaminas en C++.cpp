#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

#define Minas_Filas_Columnas 8

class Celda {
public:
    int columna;
    bool hayMina;
    int minasRededor;
    bool descubierta;
    Celda* siguiente;

    Celda(int col = 0) {
        columna = col;
        hayMina = false;
        minasRededor = 0;
        descubierta = false;
        siguiente = nullptr;
    }
};

class Fila : public Celda {
public:
    int fila;
    Celda* celdas;
    Fila* siguiente;

    Fila(int filaIndex = 0, int columnas = 0) {
        fila = filaIndex;
        siguiente = nullptr;
        celdas = nullptr;

        Celda* cabeza = nullptr;
        Celda* anterior = nullptr;

        for (int i = 0; i < columnas; i++) {
            Celda* nuevaCelda = new Celda(i);
            if (cabeza == nullptr) {
                cabeza = nuevaCelda;
            } else {
                anterior->siguiente = nuevaCelda;
            }
            anterior = nuevaCelda;
        }

        celdas = cabeza;
    }
};

class Tablero : public Fila {
private:
    int filas;
    int columnas;

public:
    Fila* cabeza;

    Tablero(int f, int c) {
        filas = f;
        columnas = c;
        cabeza = nullptr;

        Fila* anterior = nullptr;

        for (int i = 0; i < filas; i++) {
            Fila* nuevaFila = new Fila(i, columnas);

            if (cabeza == nullptr) {
                cabeza = nuevaFila;
            } else {
                anterior->siguiente = nuevaFila;
            }

            anterior = nuevaFila;
        }
    }

    void colocarMinas(int cantidadMinas) {
        int minasColocadas = 0;

        while (minasColocadas < cantidadMinas) {
            int f = rand() % filas;
            int c = rand() % columnas;

            Fila* filaActual = cabeza;
            for (int i = 0; i < f; i++) filaActual = filaActual->siguiente;

            Celda* celdaActual = filaActual->celdas;
            for (int j = 0; j < c; j++) celdaActual = celdaActual->siguiente;

            if (!celdaActual->hayMina) {
                celdaActual->hayMina = true;
                minasColocadas++;
            }
        }
    }

    void calcularMinasAlrededor() {
        for (int f = 0; f < filas; f++) {
            Fila* filaActual = cabeza;
            for (int i = 0; i < f; i++) filaActual = filaActual->siguiente;

            for (int c = 0; c < columnas; c++) {
                Celda* celdaActual = filaActual->celdas;
                for (int j = 0; j < c; j++) celdaActual = celdaActual->siguiente;

                int minas = 0;

                for (int df = -1; df <= 1; df++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        if (df == 0 && dc == 0) continue;

                        int nf = f + df;
                        int nc = c + dc;

                        if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas) {
                            Fila* filaVecina = cabeza;
                            for (int k = 0; k < nf; k++) filaVecina = filaVecina->siguiente;

                            Celda* celdaVecina = filaVecina->celdas;
                            for (int l = 0; l < nc; l++) celdaVecina = celdaVecina->siguiente;

                            if (celdaVecina->hayMina) minas++;
                        }
                    }
                }

                celdaActual->minasRededor = minas;
            }
        }
    }

    void imprimirDebug() {
        for (int f = 0; f < filas; f++) {
            Fila* filaActual = cabeza;
            for (int i = 0; i < f; i++) filaActual = filaActual->siguiente;

            Celda* celdaActual = filaActual->celdas;

            for (int c = 0; c < columnas; c++) {
                if (celdaActual->hayMina) cout << "* ";
                else cout << celdaActual->minasRededor << " ";
                celdaActual = celdaActual->siguiente;
            }
            cout << "\n";
        }
    }

    bool descubrir(int f, int c) {
        Fila* filaActual = cabeza;
        for (int i = 0; i < f; i++) filaActual = filaActual->siguiente;

        Celda* celdaActual = filaActual->celdas;
        for (int j = 0; j < c; j++) celdaActual = celdaActual->siguiente;

        if (celdaActual->descubierta) return false;

        celdaActual->descubierta = true;

        if (celdaActual->hayMina) return true;

        if (celdaActual->minasRededor == 0) {
            for (int df = -1; df <= 1; df++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (df == 0 && dc == 0) continue;
                    descubrir(f + df, c + dc);
                }
            }
        }

        return false;
    }

    void imprimirVisible() {
        for (int f = 0; f < filas; f++) {
            Fila* filaActual = cabeza;
            for (int i = 0; i < f; i++) filaActual = filaActual->siguiente;

            Celda* celdaActual = filaActual->celdas;

            for (int c = 0; c < columnas; c++) {
                if (!celdaActual->descubierta) cout << "# ";
                else if (celdaActual->hayMina) cout << "* ";
                else cout << celdaActual->minasRededor << " ";

                celdaActual = celdaActual->siguiente;
            }

            cout << "\n";
        }
    }

    int contarDescubiertas() {
        int total = 0;

        for (Fila* f = cabeza; f != nullptr; f = f->siguiente) {
            for (Celda* c = f->celdas; c != nullptr; c = c->siguiente) {
                if (c->descubierta && !c->hayMina) total++;
            }
        }

        return total;
    }

    void liberar() {
        for (Fila* f = cabeza; f != nullptr; ) {
            Fila* siguienteFila = f->siguiente;

            for (Celda* c = f->celdas; c != nullptr; ) {
                Celda* siguienteCelda = c->siguiente;
                delete c;
                c = siguienteCelda;
            }

            delete f;
            f = siguienteFila;
        }
    }
};

class JuegoBuscaminas : public Tablero {
private:
    int filas, columnas, minas;

public:
    JuegoBuscaminas(int f, int c, int m) : Tablero(f, c) {
        filas = f;
        columnas = c;
        minas = m;

        colocarMinas(minas);
        calcularMinasAlrededor();
    }

    void jugar() {
        int celdasPorDescubrir = filas * columnas - minas;
        bool jugando = true;

        while (jugando) {
            imprimirVisible();

            int f, c;
            cout << "\nIngrese fila y columna (0-" << filas - 1 << "): ";

            cin >> f >> c;

            if (cin.fail()) {
                cout << "Entrada inválida. Debe ingresar números.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (f < 0 || f >= filas || c < 0 || c >= columnas) {
                cout << "Coordenadas inválidas.\n";
                continue;
            }

            bool perdio = descubrir(f, c);

            if (perdio) {
                cout << "\n¡Pisaste una mina! GAME OVER\n";
                imprimirDebug();
                jugando = false;
                continue;
            }

            int descubiertas = contarDescubiertas();
            if (descubiertas == celdasPorDescubrir) {
                cout << "\n¡Ganaste! Descubriste todas las celdas seguras.\n";
                imprimirDebug();
                jugando = false;
            }
        }

        liberar();
    }
};

int main() {
    srand(time(NULL));

    JuegoBuscaminas juego(
        Minas_Filas_Columnas,
        Minas_Filas_Columnas,
        Minas_Filas_Columnas
    );

    juego.jugar();

    return 0;
}

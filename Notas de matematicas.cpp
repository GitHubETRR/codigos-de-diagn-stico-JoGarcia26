#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

double calcularMedia(const vector<double>& notas) {
    double suma = 0;
    for(double n : notas) suma += n;
    return suma / notas.size();
}

double calcularMediana(vector<double> notas) {
    sort(notas.begin(), notas.end());
    int n = notas.size();

    if (n % 2 == 0) {
        return (notas[n/2 - 1] + notas[n/2]) / 2;
    } else {
        return notas[n/2];
    }
}

vector<double> calcularModa(const vector<double>& notas) {
    vector<double> modas;
    int maxFrecuencia = 0;
    for (double num : notas) {
        int frecuencia = count(notas.begin(), notas.end(), num);

        if (frecuencia > maxFrecuencia) {
            maxFrecuencia = frecuencia;
            modas = {num};
        }
        else if (frecuencia == maxFrecuencia &&
                 find(modas.begin(), modas.end(), num) == modas.end()) {
            modas.push_back(num);
        }
    }
    return modas;
}
vector<double> ingresarNotas() {
    int cantidad;
    cout << "¿Cuántas notas vas a ingresar?: ";
    cin >> cantidad;

    while(cin.fail() || cantidad <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Numero invalido. Ingresalo de nuevo: ";
        cin >> cantidad;
    }

    vector<double> notas(cantidad);

    for (int i = 0; i < cantidad; i++) {
        cout << "Nota " << i+1 << ": ";
        cin >> notas[i];

        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nota invalida. Ingresala de nuevo: ";
            cin >> notas[i];
        }
    }
    return notas;
}

int main() {
    int opcion;

    do {
        cout << "\n MENU DE NOTAS \n";
        cout << "1) Ingresar notas y calcular Media\n";
        cout << "2) Ingresar notas y calcular Mediana\n";
        cout << "3) Ingresar notas y calcular Moda\n";
        cout << "4) Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1; 
        }

        switch(opcion) {
        case 1: {
            vector<double> notas = ingresarNotas();
            cout << "\nMedia: " << calcularMedia(notas) << endl;
            break;
        }
        case 2: {
            vector<double> notas = ingresarNotas();
            cout << "\nMediana: " << calcularMediana(notas) << endl;
            break;
        }
        case 3: {
            vector<double> notas = ingresarNotas();
            vector<double> moda = calcularModa(notas);

            cout << "\nModa(s): ";
            for(double m : moda) cout << m << " ";
            cout << endl;
            break;
        }
        case 4:
            cout << "Saliendo..." << endl;
            break;

        default:
            cout << (" Opción inválida. Intenta de nuevo.\n";
        }

    } while(opcion != 4);

    return 0;
}

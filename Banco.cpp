#include <iostream>
#include <vector>
#include <memory> 
using namespace std;


class Persona {
protected:
    string nombre;
    string dni;
public:
    Persona(string n, string d) : nombre(n), dni(d) {}
    virtual void mostrar() const {
        cout << "Nombre:" << nombre << " | DNI:" << dni << endl;
    }
    string getDNI() const { return dni; }   
    string getNombre() const { return nombre; } 
};


class Cuenta {
protected:
    int numeroCuenta;
    double saldo;
public:
    Cuenta(int num, double s=0) : numeroCuenta(num), saldo(s) {}
    virtual void depositar(double monto) { saldo += monto; }
    virtual bool retirar(double monto) = 0; 
    virtual void mostrar() const {
        cout << "Cuenta N°" << numeroCuenta << " | Saldo: $" << saldo << endl;
    }
    double getSaldo() const { return saldo; }
    int getNumero() const { return numeroCuenta; }
    virtual ~Cuenta() {}
};


class CuentaCorriente : public Cuenta {
    double limiteDescubierto;
public:
    CuentaCorriente(int num, double s=0, double limite=500) 
        : Cuenta(num, s), limiteDescubierto(limite) {}
    
    bool retirar(double monto) override {
        if (saldo + limiteDescubierto >= monto) {
            saldo -= monto;
            return true;
        }
        return false;
    }
    void mostrar() const override {
        cout << "[Cuenta Corriente] ";
        Cuenta::mostrar();
        cout << "   Límite descubierto: $" << limiteDescubierto << endl;
    }
};
class CajaDeAhorro : public Cuenta {
public:
    CajaDeAhorro(int num, double s=0) : Cuenta(num, s) {}
    bool retirar(double monto) override {
        if (saldo >= monto) {
            saldo -= monto;
            return true;
        }
        return false;
    }
    void mostrar() const override {
        cout << "[Caja de Ahorro]";
        Cuenta::mostrar();
    }
};
class Cliente : public Persona {
    vector<shared_ptr<Cuenta>> cuentas;
public:
    Cliente(string n, string d) : Persona(n,d) {}
    void agregarCuenta(shared_ptr<Cuenta> c) { cuentas.push_back(c); }
    void mostrar() const override {
        Persona::mostrar();
        cout << "Cuentas del cliente:" << endl;
        if (cuentas.empty()) cout << "   (Sin cuentas)" << endl;
        for (auto &c : cuentas) c->mostrar();
    }
    shared_ptr<Cuenta> getCuenta(int num) {
        for (auto &c : cuentas)
            if (c->getNumero() == num) return c;
        return nullptr;
    }
};
class Banco {
    vector<Cliente> clientes;
    int contadorCuentas = 1;
public:
    void agregarCliente(const Cliente& c) { clientes.push_back(c); }
    void mostrarClientes() const {
        if (clientes.empty()) {
            cout << "No hay clientes registrados\n";
            return;
        }
        for (auto &c : clientes) {
            c.mostrar();
            cout << "----------------------" << endl;
        }
    }

    Cliente* buscarCliente(string dni) {
        for (auto &c : clientes)
            if (dni == c.getDNI()) return &c;
        return nullptr;
    }
    void crearCliente() {
        string nombre, dni;
        cout << "Ingrese nombre:"; cin.ignore(); getline(cin, nombre);
        cout << "Ingrese DNI:"; getline(cin, dni);
        clientes.emplace_back(nombre, dni);
        cout << "Cliente agregado\n";
    }
    void crearCuenta() {
        if (clientes.empty()) { cout << "No hay clientes\n"; return; }
        string dni;
        cout << "Ingrese DNI del cliente:"; cin >> dni;
        Cliente* cli = nullptr;
        for (auto &c : clientes)
            if (dni == c.getDNI()) cli = &c;
        if (!cli) { cout << "Cliente no encontrado\n"; return; }
        int tipo;
        cout << "1) Caja de Ahorro\n2) Cuenta Corriente\nSeleccione tipo: ";
        cin >> tipo;
        if (tipo == 1)
            cli->agregarCuenta(make_shared<CajaDeAhorro>(contadorCuentas++));
        else
            cli->agregarCuenta(make_shared<CuentaCorriente>(contadorCuentas++));
        cout << "Cuenta creada corectamente\n";
    }
    void depositar() {
        int num; double monto;
        cout << "Número de cuenta:"; cin >> num;
        cout << "Monto a depositar:"; cin >> monto;

        auto cuenta = buscarCuenta(num);
        if (cuenta) {
            cuenta->depositar(monto);
            cout << "Depósito realizado\n";
        } else cout << "Cuenta no encontrada\n";
    }
    void retirar() {
        int num; double monto;
        cout << "Número de cuenta:"; cin >> num;
        cout << "Monto a retirar:"; cin >> monto;
        auto cuenta = buscarCuenta(num);
        if (cuenta && cuenta->retirar(monto)) {
            cout << "Retiro exitoso\n";
        } else cout << "No se pudo retirar\n";
    }
    void transferir() {
        int origen, destino; double monto;
        cout << "Cuenta origen:"; cin >> origen;
        cout << "Cuenta destino:"; cin >> destino;
        cout << "Monto a transferir:"; cin >> monto;
        auto c1 = buscarCuenta(origen);
        auto c2 = buscarCuenta(destino);
        if (c1 && c2 && c1->retirar(monto)) {
            c2->depositar(monto);
            cout << "Transferencia exitosa\n";
        } else cout << "Error en la transferencia\n";
    }
    shared_ptr<Cuenta> buscarCuenta(int num) {
        for (auto &cli : clientes) {
            auto c = cli.getCuenta(num);
            if (c) return c;
        }
        return nullptr;
    }
};
int main() {
    Banco b;
    int opcion;

    do {
        cout << "\n===== MENU BANCO =====\n";
        cout << "1. Crear cliente\n";
        cout << "2. Crear cuenta\n";
        cout << "3. Depositar\n";
        cout << "4. Retirar\n";
        cout << "5. Transferir\n";
        cout << "6. Mostrar clientes\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1: b.crearCliente(); break;
            case 2: b.crearCuenta(); break;
            case 3: b.depositar(); break;
            case 4: b.retirar(); break;
            case 5: b.transferir(); break;
            case 6: b.mostrarClientes(); break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while(opcion != 0);

    return 0;
}

#Hecho con CHATGPT

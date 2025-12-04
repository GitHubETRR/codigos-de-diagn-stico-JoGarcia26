#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;

// ========================== PERSONA ==========================

class Persona {
protected:
    string nombre;
    string dni;

public:
    Persona(const string& n = "", const string& d = "") : nombre(n), dni(d) {}

    virtual void mostrar() const {
        cout << "Nombre: " << nombre << " - DNI: " << dni << endl;
    }

    string getDNI() const { return dni; }
    string getNombre() const { return nombre; }
};

// ========================== CUENTAS ==========================

class Cuenta {
protected:
    int numero;
    double saldo;

public:
    Cuenta(int num = 0, double s = 0) : numero(num), saldo(s) {}
    virtual ~Cuenta() {}

    virtual bool retirar(double m) = 0;

    void depositar(double m) { saldo += m; }

    virtual string tipo() const = 0;

    virtual void mostrar() const {
        cout << "Cuenta N°" << numero << " | Saldo: $" << saldo;
    }

    int getNumero() const { return numero; }
    double getSaldo() const { return saldo; }
};

class CajaDeAhorro : public Cuenta {
public:
    CajaDeAhorro(int num, double s = 0) : Cuenta(num, s) {}

    bool retirar(double m) override {
        if (saldo >= m) {
            saldo -= m;
            return true;
        }
        return false;
    }

    string tipo() const override { return "CAJA"; }

    void mostrar() const override {
        cout << "[Caja de Ahorro] ";
        Cuenta::mostrar();
        cout << endl;
    }
};

class CuentaCorriente : public Cuenta {
    double limite;

public:
    CuentaCorriente(int num, double s = 0, double lim = 500)
        : Cuenta(num, s), limite(lim) {}

    bool retirar(double m) override {
        if (saldo + limite >= m) {
            saldo -= m;
            return true;
        }
        return false;
    }

    string tipo() const override { return "CORRIENTE"; }

    void mostrar() const override {
        cout << "[Cuenta Corriente] ";
        Cuenta::mostrar();
        cout << " | Límite: $" << limite << endl;
    }

    double getLimite() const { return limite; }
};

// ========================== CLIENTE ==========================

class Cliente : public Persona {
    vector<shared_ptr<Cuenta>> cuentas;

public:
    Cliente(const string& n = "", const string& d = "") : Persona(n, d) {}

    void agregarCuenta(shared_ptr<Cuenta> c) {
        cuentas.push_back(c);
    }

    void mostrar() const override {
        Persona::mostrar();
        cout << "Cuentas:" << endl;
        if (cuentas.empty()) {
            cout << "   (No tiene cuentas)" << endl;
        } else {
            for (auto& c : cuentas) c->mostrar();
        }
    }

    vector<shared_ptr<Cuenta>>& getCuentas() { return cuentas; }

    shared_ptr<Cuenta> getCuenta(int num) {
        for (auto& c : cuentas)
            if (c->getNumero() == num)
                return c;
        return nullptr;
    }
};

// ========================== BANCO ==========================

class Banco {
    vector<Cliente> clientes;
    int sigCuenta = 1;

public:

    // ----------- GUARDAR DATOS EN TXT ----------
    void guardarDatos() {
        ofstream f("banco.txt");
        if (!f) return;

        for (auto& c : clientes) {
            f << "# Cliente\n";
            f << c.getNombre() << "|" << c.getDNI() << "\n";

            for (auto& cuenta : c.getCuentas()) {
                f << "Cuenta:";
                f << cuenta->tipo() << "|";
                f << cuenta->getNumero() << "|";
                f << cuenta->getSaldo();

                if (cuenta->tipo() == "CORRIENTE") {
                    auto* cc = dynamic_cast<CuentaCorriente*>(cuenta.get());
                    f << "|" << cc->getLimite();
                }

                f << "\n";
            }

            f << "\n";
        }
    }

    // ----------- CARGAR DATOS DESDE TXT ----------
    void cargarDatos() {
        ifstream f("banco.txt");
        if (!f) return;

        string linea;
        Cliente* actual = nullptr;

        while (getline(f, linea)) {
            if (linea == "# Cliente") {
                getline(f, linea);
                string nombre, dni;
                stringstream ss(linea);
                getline(ss, nombre, '|');
                getline(ss, dni, '|');

                clientes.emplace_back(nombre, dni);
                actual = &clientes.back();
            }
            else if (linea.find("Cuenta:") == 0 && actual) {
                string tipo;
                int num;
                double saldo;
                stringstream ss(linea.substr(7));
                getline(ss, tipo, '|');
                ss >> num;
                ss.ignore(1);
                ss >> saldo;

                if (tipo == "CAJA") {
                    actual->agregarCuenta(make_shared<CajaDeAhorro>(num, saldo));
                } else {
                    double limite;
                    ss.ignore(1);
                    ss >> limite;
                    actual->agregarCuenta(make_shared<CuentaCorriente>(num, saldo, limite));
                }

                if (num >= sigCuenta) sigCuenta = num + 1;
            }
        }
    }

    Cliente* buscarCliente(const string& dni) {
        for (auto& c : clientes)
            if (c.getDNI() == dni)
                return &c;
        return nullptr;
    }

    void crearCliente() {
        string nombre, dni;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "DNI: ";
        getline(cin, dni);

        clientes.emplace_back(nombre, dni);
        cout << "Cliente añadido.\n";
    }

    void crearCuenta() {
        if (clientes.empty()) {
            cout << "No hay clientes cargados.\n";
            return;
        }

        string dni;
        cout << "DNI del cliente: ";
        cin >> dni;

        Cliente* cli = buscarCliente(dni);
        if (!cli) {
            cout << "No existe cliente.\n";
            return;
        }

        int tipo;
        cout << "1) Caja de Ahorro\n2) Cuenta Corriente\nOpción: ";
        cin >> tipo;

        if (tipo == 1)
            cli->agregarCuenta(make_shared<CajaDeAhorro>(sigCuenta++));
        else
            cli->agregarCuenta(make_shared<CuentaCorriente>(sigCuenta++));

        cout << "Cuenta creada.\n";
    }

    shared_ptr<Cuenta> buscarCuenta(int num) {
        for (auto& cli : clientes) {
            auto c = cli.getCuenta(num);
            if (c) return c;
        }
        return nullptr;
    }

    void depositar() {
        int num;
        double m;

        cout << "Número de cuenta: ";
        cin >> num;
        cout << "Monto: ";
        cin >> m;

        auto c = buscarCuenta(num);
        if (!c) {
            cout << "Cuenta inexistente.\n";
            return;
        }

        c->depositar(m);
        cout << "Depósito realizado.\n";
    }

    void retirar() {
        int num;
        double m;

        cout << "Cuenta: ";
        cin >> num;
        cout << "Monto: ";
        cin >> m;

        auto c = buscarCuenta(num);

        if (c && c->retirar(m))
            cout << "Retiro exitoso.\n";
        else
            cout << "No se pudo retirar.\n";
    }

    void transferir() {
        int o, d;
        double m;

        cout << "Cuenta origen: ";
        cin >> o;
        cout << "Cuenta destino: ";
        cin >> d;
        cout << "Monto: ";
        cin >> m;

        auto c1 = buscarCuenta(o);
        auto c2 = buscarCuenta(d);

        if (c1 && c2 && c1->retirar(m)) {
            c2->depositar(m);
            cout << "Transferencia realizada.\n";
        } else {
            cout << "Error en la transferencia.\n";
        }
    }

    void mostrarClientes() const {
        for (const auto& c : clientes) {
            c.mostrar();
            cout << "-------------------\n";
        }
    }
};

// ========================== MAIN ==========================

int main() {
    Banco b;
    b.cargarDatos();   // <<< CARGA AUTOMÁTICA AL INICIAR

    int op;
    do {
        cout << "\n=== MENU BANCO ===\n";
        cout << "1) Crear cliente\n";
        cout << "2) Crear cuenta\n";
        cout << "3) Depositar\n";
        cout << "4) Retirar\n";
        cout << "5) Transferir\n";
        cout << "6) Ver clientes\n";
        cout << "0) Salir\n";
        cout << "Opción: ";
        cin >> op;

        switch (op) {
            case 1: b.crearCliente(); break;
            case 2: b.crearCuenta(); break;
            case 3: b.depositar(); break;
            case 4: b.retirar(); break;
            case 5: b.transferir(); break;
            case 6: b.mostrarClientes(); break;
            case 0:
                b.guardarDatos();   // <<< GUARDA TODO ANTES DE SALIR
                cout << "Datos guardados. Saliendo...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }

    } while (op != 0);

    return 0;
}

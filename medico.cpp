#include "Medico.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <map>

using namespace std;

Medico::Medico() : nombre(""), dni(""), fechaNacimiento(""), correo(""), telefono(""), edad(0), especialidad("") {}
Medico::Medico(string nombre, string dni, string fechaNacimiento, string correo, string telefono, int edad, string especialidad)
    : nombre(nombre), dni(dni), fechaNacimiento(fechaNacimiento), correo(correo), telefono(telefono), edad(edad), especialidad(especialidad) {
}

string Medico::getNombre() const { return nombre; }
string Medico::getDNI() const { return dni; }
string Medico::getFechaNacimiento() const { return fechaNacimiento; }
string Medico::getCorreo() const { return correo; }
string Medico::getTelefono() const { return telefono; }
int Medico::getEdad() const { return edad; }
string Medico::getEspecialidad() const { return especialidad; }

void Medico::setNombre(const string& nombre) { this->nombre = nombre; }
void Medico::setDNI(const string& dni) { this->dni = dni; }
void Medico::setFechaNacimiento(const string& fechaNacimiento) { this->fechaNacimiento = fechaNacimiento; }
void Medico::setCorreo(const string& correo) { this->correo = correo; }
void Medico::setTelefono(const string& telefono) { this->telefono = telefono; }
void Medico::setEdad(int edad) { this->edad = edad; }
void Medico::setEspecialidad(const string& especialidad) { this->especialidad = especialidad; }

void Medico::CrearMedico() {
    ofstream file("medicos.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para guardar el m�dico.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string nombre, dni, fechaNacimiento, correo, telefono, especialidad;
    cout << "Ingrese el nombre del m�dico: ";
    getline(cin, nombre);
    cout << "Ingrese el DNI del m�dico: ";
    getline(cin, dni);
    cout << "Ingrese la fecha de nacimiento del m�dico (YYYY-MM-DD): ";
    getline(cin, fechaNacimiento);
    cout << "Ingrese el correo del m�dico: ";
    getline(cin, correo);
    cout << "Ingrese el tel�fono del m�dico: ";
    getline(cin, telefono);
    cout << "Ingrese la especialidad del m�dico: ";
    getline(cin, especialidad);

    int edad = Medico::CalcularEdad(fechaNacimiento);

    file << nombre << "," << dni << "," << fechaNacimiento << "," << correo << "," << telefono << "," << edad << "," << especialidad << "\n";
    file.close();

    cout << "M�dico creado exitosamente:\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "DNI: " << dni << "\n";
    cout << "Fecha de nacimiento: " << fechaNacimiento << "\n";
    cout << "Edad: " << edad << "\n";
    cout << "Correo: " << correo << "\n";
    cout << "Tel�fono: " << telefono << "\n";
    cout << "Especialidad: " << especialidad << "\n";
}

void Medico::MostrarMedico() const {
    cout << "Nombre: " << nombre << endl;
    cout << "DNI: " << dni << endl;
    cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
    cout << "Edad: " << edad << endl;
    cout << "Correo: " << correo << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Especialidad: " << especialidad << endl;
    cout << "----------------------------------------------" << endl;
}

void Medico::MostrarMedicos() {
    ifstream file("medicos.csv");
    if (file.is_open()) {
        cout << "Lista de m�dicos:\n";
        cout << "--------------------------------------------------\n";
        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            vector<string> campos;
            string campo;
            while (getline(ss, campo, ',')) {
                campos.push_back(campo);
            }
            if (campos.size() == 7) {
                string nombre = campos[0];
                string dni = campos[1];
                string fechaNacimiento = campos[2];
                string correo = campos[3];
                string telefono = campos[4];
                int edad = stoi(campos[5]);
                string especialidad = campos[6];
                Medico medico(nombre, dni, fechaNacimiento, correo, telefono, edad, especialidad);
                medico.MostrarMedico();
            }
        }
        cout << "--------------------------------------------------\n";
        file.close();
    }
    else {
        cerr << "Archivo de m�dicos no encontrado.\n";
    }
}

int Medico::CalcularEdad(const string& fechaNacimiento) {
    if (fechaNacimiento.size() < 10) {
        return -1;
    }

    int a�oNacimiento = stoi(fechaNacimiento.substr(0, 4));
    int mesNacimiento = stoi(fechaNacimiento.substr(5, 2));
    int diaNacimiento = stoi(fechaNacimiento.substr(8, 2));

    time_t t = time(0);
    struct tm now;
    localtime_s(&now, &t);

    int a�oActual = now.tm_year + 1900;
    int mesActual = now.tm_mon + 1;
    int diaActual = now.tm_mday;

    int edad = a�oActual - a�oNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--;
    }

    return edad;
}

void Medico::EliminarMedico() {
    cout << "Ingrese el DNI del m�dico a eliminar: ";
    string dni;
    cin >> dni;

    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de m�dicos.\n";
        return;
    }

    vector<string> lineas;
    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        vector<string> campos;
        string campo;
        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }
        if (campos.size() > 1 && campos[1] == dni) {
            encontrado = true;
            continue;
        }
        lineas.push_back(linea);
    }
    file.close();

    if (!encontrado) {
        cout << "M�dico no encontrado.\n";
        return;
    }

    ofstream fileOut("medicos.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de m�dicos para escribir.\n";
        return;
    }

    for (auto& l : lineas) {
        fileOut << l << "\n";
    }
    fileOut.close();

    cout << "M�dico eliminado exitosamente.\n";
}

void Medico::ModificarMedico() {
    cout << "Ingrese el DNI del m�dico a modificar: ";
    string dniBuscado;
    cin >> dniBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de m�dicos.\n";
        return;
    }

    vector<Medico> medicos;
    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        vector<string> campos;
        string campo;
        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }
        if (campos.size() == 7) {
            Medico m(campos[0], campos[1], campos[2], campos[3], campos[4], stoi(campos[5]), campos[6]);
            medicos.push_back(m);
        }
    }
    file.close();

    bool encontrado = false;
    for (auto& medico : medicos) {
        if (medico.getDNI() == dniBuscado) {
            encontrado = true;

            string nombre, fechaNacimiento, correo, telefono, especialidad;
            cout << "Ingrese el nuevo nombre del m�dico (actual: " << medico.getNombre() << "): ";
            getline(cin, nombre);
            if (!nombre.empty()) medico.setNombre(nombre);

            cout << "Ingrese la nueva fecha de nacimiento (YYYY-MM-DD, actual: " << medico.getFechaNacimiento() << "): ";
            getline(cin, fechaNacimiento);
            if (!fechaNacimiento.empty()) medico.setFechaNacimiento(fechaNacimiento);

            cout << "Ingrese el nuevo correo (actual: " << medico.getCorreo() << "): ";
            getline(cin, correo);
            if (!correo.empty()) medico.setCorreo(correo);

            cout << "Ingrese el nuevo tel�fono (actual: " << medico.getTelefono() << "): ";
            getline(cin, telefono);
            if (!telefono.empty()) medico.setTelefono(telefono);

            cout << "Ingrese la nueva especialidad (actual: " << medico.getEspecialidad() << "): ";
            getline(cin, especialidad);
            if (!especialidad.empty()) medico.setEspecialidad(especialidad);
            if (!fechaNacimiento.empty()) {
                medico.setEdad(Medico::CalcularEdad(fechaNacimiento));
            }

            break;
        }
    }

    if (!encontrado) {
        cout << "M�dico no encontrado.\n";
        return;
    }

    ofstream fileOut("medicos.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de m�dicos para escribir.\n";
        return;
    }

    for (const auto& medico : medicos) {
        fileOut << medico.getNombre() << "," << medico.getDNI() << "," << medico.getFechaNacimiento() << ","
            << medico.getCorreo() << "," << medico.getTelefono() << "," << medico.getEdad() << ","
            << medico.getEspecialidad() << "\n";
    }
    fileOut.close();

    cout << "M�dico modificado exitosamente.\n";
}

void Medico::ListaMedicosPorEspecialidad(const string& especialidad) {
    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de m�dicos.\n";
        return;
    }

    string linea;
    bool encontrado = false;

    cout << "M�dicos con especialidad '" << especialidad << "':\n";
    cout << "----------------------------------------------\n";

    while (getline(file, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() == 7 && campos[6] == especialidad) { 
            Medico medico(campos[0], campos[1], campos[2], campos[3], campos[4], stoi(campos[5]), campos[6]);
            medico.MostrarMedico();
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron m�dicos con la especialidad '" << especialidad << "'.\n";
    }

    file.close();
}

void Medico::ListaMedicosDisponiblesPorMes(const string& mes) {
    ifstream medicosFile("medicos.csv");
    ifstream citasFile("citas.csv");

    if (!medicosFile.is_open() || !citasFile.is_open()) {
        cerr << "Error al abrir los archivos necesarios.\n";
        return;
    }

    map<string, vector<string>> citasPorMedico;
    string linea;

    while (getline(citasFile, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() >= 2 && campos[0].substr(5, 2) == mes) { 
            citasPorMedico[campos[3]].push_back(campos[0]);
        }
    }
    citasFile.close();

    cout << "Disponibilidad de m�dicos en el mes " << mes << ":\n";
    cout << "----------------------------------------------\n";

    while (getline(medicosFile, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() == 7) {
            Medico medico(campos[0], campos[1], campos[2], campos[3], campos[4], stoi(campos[5]), campos[6]);
            string dni = medico.getDNI();

            if (citasPorMedico.find(dni) == citasPorMedico.end()) {
                cout << "Disponible todo el mes:\n";
                medico.MostrarMedico();
            }
            else {
                cout << "Citas en el mes:\n";
                medico.MostrarMedico();
                cout << "Fechas de citas:\n";
                for (const string& fecha : citasPorMedico[dni]) {
                    cout << " - " << fecha << "\n";
                }
            }
        }
    }

    medicosFile.close();
}
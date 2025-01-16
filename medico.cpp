#include "Medico.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>

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
        cerr << "Error al abrir el archivo para guardar el médico.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string nombre, dni, fechaNacimiento, correo, telefono, especialidad;
    cout << "Ingrese el nombre del médico: ";
    getline(cin, nombre);
    cout << "Ingrese el DNI del médico: ";
    getline(cin, dni);
    cout << "Ingrese la fecha de nacimiento del médico (YYYY-MM-DD): ";
    getline(cin, fechaNacimiento);
    cout << "Ingrese el correo del médico: ";
    getline(cin, correo);
    cout << "Ingrese el teléfono del médico: ";
    getline(cin, telefono);
    cout << "Ingrese la especialidad del médico: ";
    getline(cin, especialidad);

    int edad = Medico::CalcularEdad(fechaNacimiento);

    file << nombre << "," << dni << "," << fechaNacimiento << "," << correo << "," << telefono << "," << edad << "," << especialidad << "\n";
    file.close();

    cout << "Médico creado exitosamente:\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "DNI: " << dni << "\n";
    cout << "Fecha de nacimiento: " << fechaNacimiento << "\n";
    cout << "Edad: " << edad << "\n";
    cout << "Correo: " << correo << "\n";
    cout << "Teléfono: " << telefono << "\n";
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
        cout << "Lista de médicos:\n";
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
        cerr << "Archivo de médicos no encontrado.\n";
    }
}

int Medico::CalcularEdad(const string& fechaNacimiento) {
    if (fechaNacimiento.size() < 10) {
        return -1;
    }

    int añoNacimiento = stoi(fechaNacimiento.substr(0, 4));
    int mesNacimiento = stoi(fechaNacimiento.substr(5, 2));
    int diaNacimiento = stoi(fechaNacimiento.substr(8, 2));

    time_t t = time(0);
    struct tm now;
    localtime_s(&now, &t);

    int añoActual = now.tm_year + 1900;
    int mesActual = now.tm_mon + 1;
    int diaActual = now.tm_mday;

    int edad = añoActual - añoNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--;
    }

    return edad;
}

void Medico::EliminarMedico() {
    cout << "Ingrese el DNI del médico a eliminar: ";
    string dni;
    cin >> dni;

    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de médicos.\n";
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
        cout << "Médico no encontrado.\n";
        return;
    }

    ofstream fileOut("medicos.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de médicos para escribir.\n";
        return;
    }

    for (auto& l : lineas) {
        fileOut << l << "\n";
    }
    fileOut.close();

    cout << "Médico eliminado exitosamente.\n";
}

void Medico::ModificarMedico() {
    cout << "Ingrese el DNI del médico a modificar: ";
    string dniBuscado;
    cin >> dniBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de médicos.\n";
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
            cout << "Ingrese el nuevo nombre del médico (actual: " << medico.getNombre() << "): ";
            getline(cin, nombre);
            if (!nombre.empty()) medico.setNombre(nombre);

            cout << "Ingrese la nueva fecha de nacimiento (YYYY-MM-DD, actual: " << medico.getFechaNacimiento() << "): ";
            getline(cin, fechaNacimiento);
            if (!fechaNacimiento.empty()) medico.setFechaNacimiento(fechaNacimiento);

            cout << "Ingrese el nuevo correo (actual: " << medico.getCorreo() << "): ";
            getline(cin, correo);
            if (!correo.empty()) medico.setCorreo(correo);

            cout << "Ingrese el nuevo teléfono (actual: " << medico.getTelefono() << "): ";
            getline(cin, telefono);
            if (!telefono.empty()) medico.setTelefono(telefono);

            cout << "Ingrese la nueva especialidad (actual: " << medico.getEspecialidad() << "): ";
            getline(cin, especialidad);
            if (!especialidad.empty()) medico.setEspecialidad(especialidad);

            // Actualiza la edad si la fecha de nacimiento fue modificada
            if (!fechaNacimiento.empty()) {
                medico.setEdad(Medico::CalcularEdad(fechaNacimiento));
            }

            break;
        }
    }

    if (!encontrado) {
        cout << "Médico no encontrado.\n";
        return;
    }

    ofstream fileOut("medicos.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de médicos para escribir.\n";
        return;
    }

    for (const auto& medico : medicos) {
        fileOut << medico.getNombre() << "," << medico.getDNI() << "," << medico.getFechaNacimiento() << ","
            << medico.getCorreo() << "," << medico.getTelefono() << "," << medico.getEdad() << ","
            << medico.getEspecialidad() << "\n";
    }
    fileOut.close();

    cout << "Médico modificado exitosamente.\n";
}
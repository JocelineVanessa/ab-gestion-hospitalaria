#include "Paciente.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <limits>

using namespace std;

Paciente::Paciente(): Nombre(""), DNI(""), FechaNacimiento(""), Telefono(""), Correo(""), FechaIngreso(""), HistorialClinico("") {}
Paciente::Paciente(string nombre, string dni, string fechaNacimiento, string telefono, string correo, string fechaIngreso, string historialClinico)
    : Nombre(nombre), DNI(dni), FechaNacimiento(fechaNacimiento), Telefono(telefono), Correo(correo), FechaIngreso(fechaIngreso), HistorialClinico(historialClinico) {
}

string Paciente::getNombre() const { return Nombre; }
string Paciente::getDNI() const { return DNI; }
string Paciente::getFechaNacimiento() const { return FechaNacimiento; }
string Paciente::getTelefono() const { return Telefono; }
string Paciente::getCorreo() const { return Correo; }
string Paciente::getFechaIngreso() const { return FechaIngreso; }
string Paciente::getHistorialClinico() const { return HistorialClinico; }

void Paciente::setNombre(const string& nombre) { Nombre = nombre; }
void Paciente::setDNI(const string& dni) { DNI = dni; }
void Paciente::setFechaNacimiento(const string& fechaNacimiento) { FechaNacimiento = fechaNacimiento; }
void Paciente::setTelefono(const string& telefono) { Telefono = telefono; }
void Paciente::setCorreo(const string& correo) { Correo = correo; }
void Paciente::setFechaIngreso(const string& fechaIngreso) { FechaIngreso = fechaIngreso; }
void Paciente::setHistorialClinico(const string& historialClinico) { HistorialClinico = historialClinico; }

int Paciente::getEdad() const {
    if (FechaNacimiento.size() < 10) {
        return -1;
    }

    int añoNacimiento = stoi(FechaNacimiento.substr(0, 4));
    int mesNacimiento = stoi(FechaNacimiento.substr(5, 2));
    int diaNacimiento = stoi(FechaNacimiento.substr(8, 2));

    time_t t = time(0);
    tm* now = localtime(&t);
    int añoActual = now->tm_year + 1900;
    int mesActual = now->tm_mon + 1;
    int diaActual = now->tm_mday;

    int edad = añoActual - añoNacimiento;
    if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
        edad--;
    }

    return edad;
}

void Paciente::MostrarPaciente() const {
    cout << "Nombre: " << Nombre << endl;
    cout << "DNI: " << DNI << endl;
    cout << "Fecha de Nacimiento: " << FechaNacimiento << endl;
    cout << "Edad: " << getEdad() << endl;
    cout << "Telefono: " << Telefono << endl;
    cout << "Correo: " << Correo << endl;
    cout << "Fecha de Ingreso: " << FechaIngreso << endl;
    cout << "Historial Clinico: " << HistorialClinico << endl;
    cout << "----------------------------------------------" << endl;
}

void Paciente::ModificarPaciente() {
    cout << "Ingrese el DNI del paciente a modificar: ";
    string dniBuscado;
    cin >> dniBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ifstream file("pacientes.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de pacientes.\n";
        return;
    }

    vector<Paciente> pacientes;
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
            Paciente p(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6]);
            pacientes.push_back(p);
        }
    }
    file.close();

    bool encontrado = false;
    {
        string nombre, fechaNacimiento, telefono, correo, fechaIngreso, historialClinico;
        for (auto& p : pacientes) {
            if (p.getDNI() == dniBuscado) {
                encontrado = true;

                cout << "Ingrese el nuevo nombre del paciente (actual: " << p.getNombre() << "): ";
                getline(cin, nombre);
                if (!nombre.empty()) p.setNombre(nombre);

                cout << "Ingrese la nueva fecha de nacimiento (YYYY-MM-DD, actual: " << p.getFechaNacimiento() << "): ";
                getline(cin, fechaNacimiento);
                if (!fechaNacimiento.empty()) p.setFechaNacimiento(fechaNacimiento);

                cout << "Ingrese el nuevo telefono (actual: " << p.getTelefono() << "): ";
                getline(cin, telefono);
                if (!telefono.empty()) p.setTelefono(telefono);

                cout << "Ingrese el nuevo correo (actual: " << p.getCorreo() << "): ";
                getline(cin, correo);
                if (!correo.empty()) p.setCorreo(correo);

                cout << "Ingrese la nueva fecha de ingreso (YYYY-MM-DD, actual: " << p.getFechaIngreso() << "): ";
                getline(cin, fechaIngreso);
                if (!fechaIngreso.empty()) p.setFechaIngreso(fechaIngreso);

                cout << "Ingrese el nuevo historial clinico (actual: " << p.getHistorialClinico() << "): ";
                getline(cin, historialClinico);
                if (!historialClinico.empty()) p.setHistorialClinico(historialClinico);

                break;
            }
        }
    }

    if (!encontrado) {
        cout << "Paciente no encontrado.\n";
        return;
    }

    ofstream fileOut("pacientes.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo de pacientes para escribir.\n";
        return;
    }

    for (auto& p : pacientes) {
        fileOut << p.getNombre() << "," << p.getDNI() << "," << p.getFechaNacimiento() << "," << p.getTelefono()
            << "," << p.getCorreo() << "," << p.getFechaIngreso() << "," << p.getHistorialClinico() << "\n";
    }
    fileOut.close();

    cout << "Paciente modificado exitosamente.\n";
}

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

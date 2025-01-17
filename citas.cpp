#include "Citas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

Citas::Citas() : fecha(""), hora(""), pacienteID(""), medicoID(""){}
Citas::Citas(const string& fecha, const string& hora, const string& pacienteID, const string& medicoID)
    : fecha(fecha), hora(hora), pacienteID(pacienteID), medicoID(medicoID) {
}

string Citas::getFecha() const { return fecha; }
string Citas::getHora() const { return hora; }
string Citas::getPacienteID() const { return pacienteID; }
string Citas::getMedicoID() const { return medicoID; }

void Citas::setFecha(const string& fecha) { this->fecha = fecha; }
void Citas::setHora(const string& hora) { this->hora = hora; }
void Citas::setPacienteID(const string& pacienteID) { this->pacienteID = pacienteID; }
void Citas::setMedicoID(const string& medicoID) { this->medicoID = medicoID; }

void Citas::CrearCita() {
    ofstream file("citas.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para guardar la cita.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string fecha, hora, pacienteID, medicoID, motivo;
    cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    getline(cin, fecha);
    cout << "Ingrese la hora de la cita (HH:MM): ";
    getline(cin, hora);
    cout << "Ingrese el ID del paciente: ";
    getline(cin, pacienteID);
    cout << "Ingrese el ID del medico: ";
    getline(cin, medicoID);

    file << fecha << "," << hora << "," << pacienteID << "," << medicoID << "\n";
    file.close();

    cout << "Cita creada exitosamente.\n";
}


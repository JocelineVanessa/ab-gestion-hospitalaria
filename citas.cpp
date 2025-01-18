#include "Citas.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

Citas::Citas() : fecha(""), hora(""), pacienteID(""), medicoID(""), nivelDeUrgencia(""){}
Citas::Citas(const string& fecha, const string& hora, const string& pacienteID, const string& medicoID, const string& nivelDeUrgencia)
    : fecha(fecha), hora(hora), pacienteID(pacienteID), medicoID(medicoID), nivelDeUrgencia(nivelDeUrgencia){
}

string Citas::getFecha() const { return fecha; }
string Citas::getHora() const { return hora; }
string Citas::getPacienteID() const { return pacienteID; }
string Citas::getMedicoID() const { return medicoID; }
string Citas::getnivelDeUrgencia() const { return nivelDeUrgencia; }

void Citas::setFecha(const string& fecha) { this->fecha = fecha; }
void Citas::setHora(const string& hora) { this->hora = hora; }
void Citas::setPacienteID(const string& pacienteID) { this->pacienteID = pacienteID; }
void Citas::setMedicoID(const string& medicoID) { this->medicoID = medicoID; }
void Citas::setnivelDeUrgencia(const string& nivelDeUrgencia) { this->nivelDeUrgencia = nivelDeUrgencia; }

void Citas::CrearCita() {
    ofstream file("citas.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para guardar la cita.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string fecha, hora, pacienteID, medicoID, nivelDeUrgencia;
    cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
    getline(cin, fecha);
    cout << "Ingrese la hora de la cita (HH:MM): ";
    getline(cin, hora);
    cout << "Ingrese el ID del paciente: ";
    getline(cin, pacienteID);
    cout << "Ingrese el ID del medico: ";
    getline(cin, medicoID);
    cout << "Ingrese el nivel de urgencia (Bajo, medio, alto): ";
    getline(cin, nivelDeUrgencia);

    file << fecha << "," << hora << "," << pacienteID << "," << medicoID << "," << nivelDeUrgencia << "\n";
    file.close();

    cout << "Cita creada exitosamente.\n";
}

void Citas::MostrarCita() const {
    cout << "Fecha: " << fecha << endl;
    cout << "Hora: " << hora << endl;
    cout << "Paciente ID: " << pacienteID << endl;
    cout << "Medico ID: " << medicoID << endl;
    cout << "----------------------------------------------" << endl;
}

void Citas::MostrarCitas() {
    ifstream file("citas.csv");
    if (file.is_open()) {
        cout << "Lista de citas:\n";
        cout << "--------------------------------------------------\n";
        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string fecha, hora, pacienteID, medicoID, nivelDeUrgencia;

            getline(ss, fecha, ',');
            getline(ss, hora, ',');
            getline(ss, pacienteID, ',');
            getline(ss, medicoID, ',');
            getline(ss, nivelDeUrgencia, ',');

            Citas cita(fecha, hora, pacienteID, medicoID, nivelDeUrgencia);
            cita.MostrarCita();
        }
        file.close();
    }
    else {
        cerr << "Archivo de citas no encontrado.\n";
    }
}

void Citas::ModificarCita() {
    cout << "Ingrese el ID del paciente: ";
    string idPaciente;
    cin >> idPaciente;

    vector<string> lineas;
    ifstream file("citas.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        vector<string> campos;
        string campo;
        while (getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() > 1 && campos[1] == idPaciente) { 
            encontrado = true;
            cout << "Datos actuales de la cita:\n";
            cout << "ID Cita: " << campos[0] << "\n";
            cout << "ID Paciente: " << campos[1] << "\n";
            cout << "ID Medico: " << campos[2] << "\n";
            cout << "Fecha: " << campos[3] << "\n";
            cout << "Nivel de Urgencia: " << campos[4] << "\n";

            cout << "\nIngrese los nuevos datos de la cita:\n";
            cout << "Nuevo ID Medico: ";
            cin >> campos[2];
            cout << "Nueva Fecha (YYYY-MM-DD): ";
            cin >> campos[3];
            cout << "Nuevo nivel de Urgencia): ";
            cin >> campos[4];

            linea = campos[0] + "," + campos[1] + "," + campos[2] + "," + campos[3] + "," + campos [4];
        }
        lineas.push_back(linea);
    }

    file.close();

    if (!encontrado) {
        cout << "No se encontró una cita para el ID del paciente proporcionado.\n";
        return;
    }

    ofstream fileOut("citas.csv", ios::trunc);
    if (!fileOut.is_open()) {
        cerr << "Error al abrir el archivo para guardar las citas.\n";
        return;
    }

    for (const auto& l : lineas) {
        fileOut << l << "\n";
    }

    fileOut.close();
    cout << "Cita modificada exitosamente.\n";
}

void Citas::EliminarCita() {
    cout << "Ingrese la fecha de la cita a eliminar (YYYY-MM-DD): ";
    string fechaEliminar;
    cin >> fechaEliminar;

    ifstream file("citas.csv");
    if (!file.is_open()) {
        cerr << "Archivo de citas no encontrado.\n";
        return;
    }

    vector<string> lineas;
    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string fecha;
        getline(ss, fecha, ',');
        if (fecha == fechaEliminar) {
            encontrado = true;
            continue;
        }
        lineas.push_back(linea);
    }
    file.close();

    if (!encontrado) {
        cout << "Cita no encontrada.\n";
        return;
    }

    ofstream outFile("citas.csv", ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error al abrir el archivo para guardar las citas.\n";
        return;
    }

    for (const auto& l : lineas) {
        outFile << l << "\n";
    }
    outFile.close();

    cout << "Cita eliminada exitosamente.\n";
}
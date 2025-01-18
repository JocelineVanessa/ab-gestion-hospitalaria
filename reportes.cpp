#include "Reportes.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void Reportes::ReportePacientesAtendidos() {
    ifstream file("pacientes.csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de pacientes.\n";
        return;
    }

    cout << "Reporte de pacientes atendidos:\n";
    cout << "-----------------------------------------\n";

    string linea;
    int contador = 0;
    while (getline(file, linea)) {
        if (!linea.empty()) {
            ++contador;
        }
    }
    file.close();

    cout << "Pacientes atendidos: " << contador << "\n";
    cout << "-----------------------------------------\n";
}

void Reportes::ReporteMedicosDisponibles() {
    ifstream file("medicos.csv");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo de medicos.\n";
        return;
    }

    cout << "Reporte de medicos disponibles:\n";
    cout << "-----------------------------------------\n";

    string linea;
    int contador = 0;
    while (getline(file, linea)) {
        if (!linea.empty()) {
            ++contador;
        }
    }
    file.close();

    cout << "Medicos disponibles: " << contador << "\n";
    cout << "-----------------------------------------\n";
}

void Reportes::ReporteCitasPendientesPorDia() {
    cout << "Ingrese la fecha de consulta (YYYY-MM-DD): ";
    string fechaConsulta;
    cin >> fechaConsulta;

    ifstream file("citas.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    cout << "\nCitas programadas para la fecha " << fechaConsulta << ":\n";
    cout << "--------------------------------------------------\n";
    cout << "Fecha       | Hora   | ID Paciente | ID Medico\n";

    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')) {
            campo.erase(0, campo.find_first_not_of(" \t"));
            campo.erase(campo.find_last_not_of(" \t") + 1);
            campos.push_back(campo);
        }

        if (campos.size() == 4) {
            string fecha = campos[0];
            if (fecha == fechaConsulta) {
                encontrado = true;
                cout << campos[0] << " | " << campos[1] << " | " << campos[2] << " | " << campos[3] << "\n";
            }
        }
    }

    file.close();

    if (!encontrado) {
        cout << "No se encontraron citas para la fecha proporcionada.\n";
    }

    cout << "--------------------------------------------------\n";
}

void Reportes::ReporteCitasPendientesPorMes() {
    cout << "Ingrese el mes de consulta (YYYY-MM): ";
    string mesConsulta;
    cin >> mesConsulta;

    ifstream file("citas.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de citas.\n";
        return;
    }

    cout << "\nCitas programadas para el mes " << mesConsulta << ":\n";
    cout << "--------------------------------------------------\n";
    cout << "Fecha       | Hora   | ID Paciente | ID Medico\n";

    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        vector<string> campos;
        string campo;

        while (getline(ss, campo, ',')) {
            campo.erase(0, campo.find_first_not_of(" \t"));
            campo.erase(campo.find_last_not_of(" \t") + 1);
            campos.push_back(campo);
        }

        if (campos.size() == 4) {
            string fecha = campos[0];
            if (fecha.substr(0, 7) == mesConsulta) {
                encontrado = true;
                cout << campos[0] << " | " << campos[1] << " | " << campos[2] << " | " << campos[3] << "\n";
            }
        }
    }

    file.close();

    if (!encontrado) {
        cout << "No se encontraron citas para el mes proporcionado.\n";
    }

    cout << "--------------------------------------------------\n";
}
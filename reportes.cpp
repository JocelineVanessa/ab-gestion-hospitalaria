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
        cout << "Reporte de citas pendientes por dia no implementado.\n";
    }

void Reportes::ReporteCitasPendientesPorMes() {
        cout << "Reporte de citas pendientes por mes no implementado.\n";
    }

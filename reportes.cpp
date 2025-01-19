#include "Reportes.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

void Reportes::ReportePacientesAtendidos(const string& fecha) {
    ifstream citasFile("citas.csv");
    ifstream pacientesFile("pacientes.csv");
    ifstream medicosFile("medicos.csv");

    if (!citasFile.is_open() || !pacientesFile.is_open() || !medicosFile.is_open()) {
        cerr << "Error al abrir uno de los archivos necesarios (citas.csv, pacientes.csv, medicos.csv).\n";
        return;
    }
    map<string, vector<string>> pacientesData; 
    string linea;
    while (getline(pacientesFile, linea)) {
        stringstream ss(linea);
        string nombre, dni, fechaNacimiento, telefono, correo, fechaIngreso, historial;
        getline(ss, nombre, ',');
        getline(ss, dni, ',');
        getline(ss, fechaNacimiento, ',');
        getline(ss, telefono, ',');
        getline(ss, correo, ',');
        getline(ss, fechaIngreso, ',');
        getline(ss, historial, ',');

        pacientesData[dni] = { nombre, telefono, correo, historial };
    }
    pacientesFile.close();

    map<string, string> medicosData;
    while (getline(medicosFile, linea)) {
        stringstream ss(linea);
        string nombre, dni, fechaNacimiento, correo, telefono, edad, especialidad;
        getline(ss, nombre, ',');
        getline(ss, dni, ',');
        getline(ss, fechaNacimiento, ',');
        getline(ss, correo, ',');
        getline(ss, telefono, ',');
        getline(ss, edad, ',');
        getline(ss, especialidad, ',');

        medicosData[dni] = especialidad;
    }
    medicosFile.close();

    cout << "Reporte de Pacientes Atendidos para la fecha: " << fecha << "\n";
    cout << "------------------------------------------------------------\n";
    cout << left << setw(12) << "Fecha" << setw(8) << "Hora" << setw(20) << "Especialidad"
        << setw(20) << "Paciente" << setw(12) << "Teléfono" << setw(25) << "Correo"
        << "Historial Clínico\n";
    cout << "------------------------------------------------------------\n";

    bool hayCitas = false;
    while (getline(citasFile, linea)) {
        stringstream ss(linea);
        string fechaCita, hora, dniPaciente, dniMedico, nivelUrgencia;
        getline(ss, fechaCita, ',');
        getline(ss, hora, ',');
        getline(ss, dniPaciente, ',');
        getline(ss, dniMedico, ',');
        getline(ss, nivelUrgencia, ',');

        if (fechaCita == fecha) {
            hayCitas = true;

            if (pacientesData.find(dniPaciente) == pacientesData.end()) {
                cerr << "Paciente con DNI " << dniPaciente << " no encontrado en pacientes.csv.\n";
                continue;
            }
            vector<string> pacienteInfo = pacientesData[dniPaciente];

            string especialidad = "Desconocida";
            if (medicosData.find(dniMedico) != medicosData.end()) {
                especialidad = medicosData[dniMedico];
            }
            cout << left << setw(12) << fechaCita << setw(8) << hora << setw(20) << especialidad
                << setw(20) << pacienteInfo[0] << setw(12) << pacienteInfo[1]
                << setw(25) << pacienteInfo[2] << pacienteInfo[3] << "\n";
        }
    }

    if (!hayCitas) {
        cout << "No hay pacientes atendidos en la fecha indicada.\n";
    }

    cout << "------------------------------------------------------------\n";

    citasFile.close();
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
    cout << "------------------------------------------------------------\n";
    cout << left << setw(12) << "Fecha" << setw(8) << "Hora" << setw(15) << "Paciente DNI"
        << setw(15) << "Medico DNI" << setw(10) << "Urgencia\n";
    cout << "------------------------------------------------------------\n";

    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string fecha, hora, dniPaciente, dniMedico, nivelUrgencia;

        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, dniPaciente, ',');
        getline(ss, dniMedico, ',');
        getline(ss, nivelUrgencia, ',');

        if (fecha == fechaConsulta) {
            encontrado = true;
            cout << left << setw(12) << fecha << setw(8) << hora << setw(15) << dniPaciente
                << setw(15) << dniMedico << setw(10) << nivelUrgencia << "\n";
        }
    }

    if (!encontrado) {
        cout << "No se encontraron citas para la fecha proporcionada.\n";
    }

    cout << "------------------------------------------------------------\n";
    file.close();
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
    cout << "------------------------------------------------------------\n";
    cout << left << setw(12) << "Fecha" << setw(8) << "Hora" << setw(15) << "Paciente DNI"
        << setw(15) << "Medico DNI" << setw(10) << "Urgencia\n";
    cout << "------------------------------------------------------------\n";

    string linea;
    bool encontrado = false;

    while (getline(file, linea)) {
        stringstream ss(linea);
        string fecha, hora, dniPaciente, dniMedico, nivelUrgencia;

        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, dniPaciente, ',');
        getline(ss, dniMedico, ',');
        getline(ss, nivelUrgencia, ',');

        if (fecha.substr(0, 7) == mesConsulta) {
            encontrado = true;
            cout << left << setw(12) << fecha << setw(8) << hora << setw(15) << dniPaciente
                << setw(15) << dniMedico << setw(10) << nivelUrgencia << "\n";
        }
    }

    if (!encontrado) {
        cout << "No se encontraron citas para el mes proporcionado.\n";
    }

    cout << "------------------------------------------------------------\n";
    file.close();
}

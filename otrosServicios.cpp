#include "OtrosServicios.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

OtrosServicios::OtrosServicios() : nombreServicio(""), descripcion("") {}

OtrosServicios::OtrosServicios(const std::string& nombreServicio, const std::string& descripcion)
    : nombreServicio(nombreServicio), descripcion(descripcion) {
}

std::string OtrosServicios::getNombreServicio() const { return nombreServicio; }
std::string OtrosServicios::getDescripcion() const { return descripcion; }

void OtrosServicios::setNombreServicio(const std::string& nombreServicio) {
    this->nombreServicio = nombreServicio;
}

void OtrosServicios::setDescripcion(const std::string& descripcion) {
    this->descripcion = descripcion;
}

void OtrosServicios::AgregarServicio() {
    ofstream file("otros_servicios.csv", ios::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para guardar el servicio.\n";
        return;
    }

    string nombre, descripcion;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ingrese el nombre del servicio: ";
    getline(cin, nombre);
    cout << "Ingrese la descripcion del servicio: ";
    getline(cin, descripcion);

    file << nombre << "," << descripcion << "\n";
    file.close();

    cout << "Servicio agregado exitosamente.\n";
}

void OtrosServicios::MostrarServicios() {
    ifstream file("otros_servicios.csv");
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo de servicios.\n";
        return;
    }

    cout << "Lista de Otros Servicios:\n";
    cout << "--------------------------------------------------\n";
    string linea;
    while (getline(file, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string nombre, descripcion;
        getline(ss, nombre, ',');
        getline(ss, descripcion, ',');

        cout << "Nombre del Servicio: " << nombre << "\n";
        cout << "Descripcion: " << descripcion << "\n";
        cout << "--------------------------------------------------\n";
    }
    file.close();
}

#include "CopiaSeguridad.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void CopiaSeguridad::RealizarCopiaSeguridad() {
    cout << "Iniciando copia de seguridad...\n";

    vector<string> archivos = {
        "usuarios.csv",
        "pacientes.csv",
        "medicos.csv",
        "citas.csv",
        "otrosServicios.csv"
    };

    string carpetaRespaldo = "backup/";
    if (!fs::exists(carpetaRespaldo)) {
        fs::create_directory(carpetaRespaldo);
    }
    for (const string& archivo : archivos) {
        string destino = carpetaRespaldo + archivo;
        CopiarArchivo(archivo, destino);
    }

    cout << "Copia de seguridad completada.\n";
}

void CopiaSeguridad::CopiarArchivo(const string& origen, const string& destino) {
    ifstream archivoOrigen(origen, ios::binary);
    ofstream archivoDestino(destino, ios::binary);

    if (archivoOrigen.is_open() && archivoDestino.is_open()) {
        archivoDestino << archivoOrigen.rdbuf();
        cout << "Copia realizada: " << origen << " -> " << destino << "\n";
    }
    else {
        cerr << "Error al copiar el archivo: " << origen << "\n";
    }
}

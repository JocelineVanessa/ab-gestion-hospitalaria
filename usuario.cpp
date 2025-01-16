#include "Usuario.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

Usuario::Usuario(string nombreUsuario, string contrase�a, string rol)
    : nombreUsuario(nombreUsuario), contrase�a(contrase�a), rol(rol), permisos(TOTAL_PERMISOS, false) {
    AsignarPermisosPorRol();
}

void Usuario::AsignarPermisosPorRol() {
    permisos.assign(TOTAL_PERMISOS, false);
    if (rol == "ADMINISTRADOR") {
        permisos[CREAR_PACIENTE] = true;
        permisos[MODIFICAR_PACIENTE] = true;
        permisos[ELIMINAR_PACIENTE] = true;
        permisos[CREAR_MEDICO] = true;
        permisos[ELIMINAR_MEDICO] = true;
        permisos[MODIFICAR_MEDICO] = true;
        permisos[CREAR_CITA] = true;
        permisos[MODIFICAR_CITA] = true;
        permisos[ELIMINAR_CITA] = true;
    }
    else if (rol == "MEDICO") {
        permisos[VER_CITAS] = true;
        permisos[HISTORIAL_PACIENTE] = true;
        permisos[MODIFICAR_HISTORIAL_PACIENTE] = true;
    }
    else if (rol == "RECEPCIONISTA") {
        permisos[CREAR_PACIENTE] = true;
        permisos[MODIFICAR_PACIENTE] = true;
        permisos[CREAR_CITA] = true;
        permisos[MODIFICAR_CITA] = true;
        permisos[ELIMINAR_CITA] = true;
        permisos[VER_CITAS] = true;
    }
}

string Usuario::getNombreUsuario() const { return nombreUsuario; }
string Usuario::getRol() const { return rol; }
const vector<bool>& Usuario::getPermisos() const { return permisos; }

bool Usuario::VerificarPermiso(PermisoIndex permiso) const { return permiso < permisos.size() && permisos[permiso]; }
bool Usuario::ValidarContrase�a(const string& inputContrase�a) const { return inputContrase�a == contrase�a; }

void Usuario::MostrarUsuario() const {
    cout << "Nombre de Usuario: " << nombreUsuario << endl;
    cout << "Rol: " << rol << endl;
    cout << "Permisos: [ ";
    for (size_t i = 0; i < permisos.size(); ++i) {
        cout << (permisos[i] ? "Si" : "No") << (i < permisos.size() - 1 ? ", " : " ");
    }
    cout << "]" << endl;
    cout << "----------------------------------------------" << endl;
}

void Usuario::GuardarUsuarios(const vector<Usuario>& usuarios, const string& archivo) {
    ofstream file(archivo);
    if (file.is_open()) {
        for (const auto& usuario : usuarios) {
            file << usuario.nombreUsuario << "," << usuario.contrase�a << "," << usuario.rol << "\n";
        }
        file.close();
    }
    else {
        cerr << "Error al abrir el archivo para guardar.\n";
    }
}

void Usuario::CargarUsuarios(vector<Usuario>& usuarios, const string& archivo) {
    ifstream file(archivo);
    if (file.is_open()) {
        string linea;
        while (getline(file, linea)) {
            if (linea.empty()) continue;
            stringstream ss(linea);
            string nombreUsuario, contrase�a, rol;
            getline(ss, nombreUsuario, ',');
            getline(ss, contrase�a, ',');
            getline(ss, rol, ',');
            usuarios.push_back(Usuario(nombreUsuario, contrase�a, rol));
        }
        file.close();
    }
    else {
        cerr << "Archivo no encontrado, se creara uno nuevo al guardar.\n";
    }
}

bool Usuario::CrearUsuario(vector<Usuario>& usuarios) {
    string nombre, contrase�a, rol;
    cout << "Ingrese el nombre del nuevo usuario: ";
    cin >> nombre;
    cout << "Ingrese la contrase�a: ";
    cin >> contrase�a;
    cout << "Ingrese el rol (ADMINISTRADOR, RECEPCIONISTA, MEDICO): ";
    cin >> rol;

    if (rol != "ADMINISTRADOR" && rol != "RECEPCIONISTA" && rol != "MEDICO") {
        cout << "Rol no valido. Usuario no creado.\n";
        return false;
    }
    usuarios.push_back(Usuario(nombre, contrase�a, rol));
    return true;
}

void Usuario::MostrarUsuarios(const vector<Usuario>& usuarios) {
    cout << "Lista de usuarios:\n";
    cout << "--------------------------------------------------\n";
    for (const auto& u : usuarios) {
        u.MostrarUsuario();
    }
    cout << "--------------------------------------------------\n";
}
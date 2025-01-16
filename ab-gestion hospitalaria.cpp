#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <limits>
#include "Paciente.h"

using namespace std;

enum PermisoIndex {
    CREAR_PACIENTE = 0,
    MODIFICAR_PACIENTE,
    ELIMINAR_PACIENTE,
    CREAR_MEDICO,
    ELIMINAR_MEDICO,
    MODIFICAR_MEDICO,
    CREAR_CITA,
    MODIFICAR_CITA,
    ELIMINAR_CITA,
    VER_CITAS,
    HISTORIAL_PACIENTE,
    MODIFICAR_HISTORIAL_PACIENTE,
    TOTAL_PERMISOS
};


class Medico {
private:
    string nombre;
    string dni;
    string fechaNacimiento;
    string correo;
    string telefono;
    int edad;
    string especialidad;
public:
    Medico() : nombre(""), dni(""), fechaNacimiento(""), correo(""), telefono(""), edad(0), especialidad("") {}
    Medico(string n, string d, string f, string c, string t, int e, string esp)
        : nombre(n), dni(d), fechaNacimiento(f), correo(c), telefono(t), edad(e), especialidad(esp) {
    }

    void MostrarMedico() const {
        cout << "Nombre: " << nombre << endl;
        cout << "DNI: " << dni << endl;
        cout << "Fecha de Nacimiento: " << fechaNacimiento << endl;
        cout << "Edad: " << edad << endl;
        cout << "Correo: " << correo << endl;
        cout << "Telefono: " << telefono << endl;
        cout << "Especialidad: " << especialidad << endl;
        cout << "----------------------------------------------" << endl;
    }

    string getDNI() const { return dni; }

    static void MostrarMedicos() {
        ifstream file("medicos.csv");
        if (file.is_open()) {
            cout << "Lista de medicos:\n";
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
                    string n = campos[0];
                    string d = campos[1];
                    string f = campos[2];
                    string c = campos[3];
                    string t = campos[4];
                    int e = stoi(campos[5]);
                    string esp = campos[6];
                    Medico m(n, d, f, c, t, e, esp);
                    m.MostrarMedico();
                }
            }
            cout << "--------------------------------------------------\n";
            file.close();
        }
        else {
            cerr << "Archivo de medicos no encontrado.\n";
        }
    }

    static int CalcularEdad(const string& fechaNacimiento) {
        if (fechaNacimiento.size() < 10) {
            return -1;
        }

        int añoNacimiento = stoi(fechaNacimiento.substr(0, 4));
        int mesNacimiento = stoi(fechaNacimiento.substr(5, 2));
        int diaNacimiento = stoi(fechaNacimiento.substr(8, 2));

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
};

class Usuario {
private:
    string nombreUsuario;
    string contraseña;
    string rol;
    vector<bool> permisos;

    void AsignarPermisosPorRol() {
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

public:
    Usuario(string nombreUsuario, string contraseña, string rol)
        : nombreUsuario(nombreUsuario), contraseña(contraseña), rol(rol), permisos(TOTAL_PERMISOS, false) {
        AsignarPermisosPorRol();
    }

    string getNombreUsuario() const { return nombreUsuario; }
    string getRol() const { return rol; }
    const vector<bool>& getPermisos() const { return permisos; }

    bool VerificarPermiso(PermisoIndex permiso) const { return permiso < permisos.size() && permisos[permiso]; }
    bool ValidarContraseña(const string& inputContraseña) const { return inputContraseña == contraseña; }

    void MostrarUsuario() const {
        cout << "Nombre de Usuario: " << nombreUsuario << endl;
        cout << "Rol: " << rol << endl;
        cout << "Permisos: [ ";
        for (size_t i = 0; i < permisos.size(); ++i) {
            cout << (permisos[i] ? "Si" : "No") << (i < permisos.size() - 1 ? ", " : " ");
        }
        cout << "]" << endl;
        cout << "----------------------------------------------" << endl;
    }

    static void GuardarUsuarios(const vector<Usuario>& usuarios, const string& archivo) {
        ofstream file(archivo);
        if (file.is_open()) {
            for (const auto& usuario : usuarios) {
                file << usuario.nombreUsuario << "," << usuario.contraseña << "," << usuario.rol << "\n";
            }
            file.close();
        }
        else {
            cerr << "Error al abrir el archivo para guardar.\n";
        }
    }

    static void CargarUsuarios(vector<Usuario>& usuarios, const string& archivo) {
        ifstream file(archivo);
        if (file.is_open()) {
            string linea;
            while (getline(file, linea)) {
                if (linea.empty()) continue;
                stringstream ss(linea);
                string nombreUsuario, contraseña, rol;
                getline(ss, nombreUsuario, ',');
                getline(ss, contraseña, ',');
                getline(ss, rol, ',');
                usuarios.push_back(Usuario(nombreUsuario, contraseña, rol));
            }
            file.close();
        }
        else {
            cerr << "Archivo no encontrado, se creara uno nuevo al guardar.\n";
        }
    }

    static bool CrearUsuario(vector<Usuario>& usuarios) {
        string nombre, contraseña, rol;
        cout << "Ingrese el nombre del nuevo usuario: ";
        cin >> nombre;
        cout << "Ingrese la contraseña: ";
        cin >> contraseña;
        cout << "Ingrese el rol (ADMINISTRADOR, RECEPCIONISTA, MEDICO): ";
        cin >> rol;

        if (rol != "ADMINISTRADOR" && rol != "RECEPCIONISTA" && rol != "MEDICO") {
            cout << "Rol no valido. Usuario no creado.\n";
            return false;
        }
        usuarios.push_back(Usuario(nombre, contraseña, rol));
        return true;
    }

    static void CrearMedico() {
        ofstream file("medicos.csv", ios::app);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo para guardar el medico.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string nombre, dni, fechaNacimiento, correo, telefono, especialidad;
        cout << "Ingrese el nombre del medico: ";
        getline(cin, nombre);
        cout << "Ingrese el DNI del medico: ";
        getline(cin, dni);
        cout << "Ingrese la fecha de nacimiento del medico (YYYY-MM-DD): ";
        getline(cin, fechaNacimiento);
        cout << "Ingrese el correo del medico: ";
        getline(cin, correo);
        cout << "Ingrese el telefono del medico: ";
        getline(cin, telefono);
        cout << "Ingrese la especialidad del medico: ";
        getline(cin, especialidad);

        int edad = Medico::CalcularEdad(fechaNacimiento);

        file << nombre << "," << dni << "," << fechaNacimiento << "," << correo << "," << telefono << "," << edad << "," << especialidad << "\n";
        file.close();

        cout << "Medico creado exitosamente:\n";
        cout << "Nombre: " << nombre << "\n";
        cout << "DNI: " << dni << "\n";
        cout << "Fecha de nacimiento: " << fechaNacimiento << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Correo: " << correo << "\n";
        cout << "Telefono: " << telefono << "\n";
        cout << "Especialidad: " << especialidad << "\n";
    }

    static void EliminarMedico() {
        cout << "Ingrese el DNI del medico a eliminar: ";
        string dni;
        cin >> dni;

        fstream file("medicos.csv", ios::in | ios::out);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo.\n";
            return;
        }

        string linea;
        streampos lastPos = file.tellg();
        bool encontrado = false;

        while (getline(file, linea)) {
            if (linea.find(dni) != string::npos) {
                encontrado = true;
                break;
            }
            lastPos = file.tellg();
        }

        if (encontrado) {
            file.seekp(lastPos);
            file << string(linea.length(), ' ');
            cout << "Medico eliminado exitosamente.\n";
        }
        else {
            cout << "Medico no encontrado.\n";
        }

        file.close();
    }

    static void MostrarUsuarios(const vector<Usuario>& usuarios) {
        cout << "Lista de usuarios:\n";
        cout << "--------------------------------------------------\n";
        for (const auto& u : usuarios) {
            u.MostrarUsuario();
        }
        cout << "--------------------------------------------------\n";
    }

    static void CrearPaciente() {
        ofstream file("pacientes.csv", ios::app);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo para guardar el paciente.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string nombre, dni, fechaNacimiento, telefono, correo, fechaIngreso, historialClinico;
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, nombre);
        cout << "Ingrese el DNI del paciente: ";
        getline(cin, dni);
        cout << "Ingrese la fecha de nacimiento del paciente (YYYY-MM-DD): ";
        getline(cin, fechaNacimiento);
        cout << "Ingrese el telefono del paciente: ";
        getline(cin, telefono);
        cout << "Ingrese el correo del paciente: ";
        getline(cin, correo);
        cout << "Ingrese la fecha de ingreso del paciente (YYYY-MM-DD): ";
        getline(cin, fechaIngreso);
        cout << "Ingrese el historial clinico del paciente: ";
        getline(cin, historialClinico);

        file << nombre << "," << dni << "," << fechaNacimiento << "," << telefono << "," << correo << "," << fechaIngreso << "," << historialClinico << "\n";
        file.close();

        Paciente p(nombre, dni, fechaNacimiento, telefono, correo, fechaIngreso, historialClinico);
        cout << "Paciente creado exitosamente.\n";
        p.MostrarPaciente();
    }

    static void MostrarPacientes() {
        ifstream file("pacientes.csv");
        if (file.is_open()) {
            cout << "Lista de pacientes:\n";
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
                    Paciente p(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6]);
                    p.MostrarPaciente();
                }
            }
            cout << "--------------------------------------------------\n";
            file.close();
        }
        else {
            cerr << "Archivo de pacientes no encontrado.\n";
        }
    }

    static void EliminarPaciente() {
        cout << "Ingrese el DNI del paciente a eliminar: ";
        string dni;
        cin >> dni;

        ifstream file("pacientes.csv");
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo de pacientes.\n";
            return;
        }

        vector<string> lineas;
        string linea;
        bool encontrado = false;

        while (getline(file, linea)) {
            stringstream ss(linea);
            vector<string> campos;
            string campo;
            while (getline(ss, campo, ',')) {
                campos.push_back(campo);
            }
            if (campos.size() > 1 && campos[1] == dni) {
                encontrado = true;
                continue;
            }
            lineas.push_back(linea);
        }

        file.close();

        if (!encontrado) {
            cout << "Paciente no encontrado.\n";
            return;
        }

        ofstream fileOut("pacientes.csv", ios::trunc);
        if (!fileOut.is_open()) {
            cerr << "Error al abrir el archivo de pacientes para escribir.\n";
            return;
        }

        for (auto& l : lineas) {
            fileOut << l << "\n";
        }
        fileOut.close();

        cout << "Paciente eliminado exitosamente.\n";
    }

    static void ModificarMedico() {
        cout << "Funcionalidad de modificar medico no implementada.\n";
    }
};

class Reportes {
public:
    static void ReportePacientesAtendidos() {
        cout << "Reporte de pacientes atendidos no implementado.\n";
    }

    static void ReporteMedicosDisponibles() {
        cout << "Reporte de medicos disponibles no implementado.\n";
    }

    static void ReporteCitasPendientesPorDia() {
        cout << "Reporte de citas pendientes por dia no implementado.\n";
    }

    static void ReporteCitasPendientesPorMes() {
        cout << "Reporte de citas pendientes por mes no implementado.\n";
    }
};

bool IniciarSesion(const string& nombreUsuario, const string& contraseña, const vector<Usuario>& usuarios, Usuario& usuarioAutenticado) {
    for (const auto& usuario : usuarios) {
        if (usuario.getNombreUsuario() == nombreUsuario && usuario.ValidarContraseña(contraseña)) {
            usuarioAutenticado = usuario;
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Bienvenido\n";
    vector<Usuario> usuarios;
    const string archivoUsuarios = "usuarios.csv";

    Usuario::CargarUsuarios(usuarios, archivoUsuarios);

    if (usuarios.empty()) {
        cout << "No se encontraron usuarios. Creando usuario administrador...\n";
        usuarios.push_back(Usuario("JocelineRamirez", "1234", "ADMINISTRADOR"));
        Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
        cout << "Usuario administrador creado con exito\n";
    }

    string nombreUsuario, contraseña;
    cout << "Ingrese el nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese la contraseña: ";
    cin >> contraseña;

    Usuario usuarioAutenticado("", "", "");
    if (IniciarSesion(nombreUsuario, contraseña, usuarios, usuarioAutenticado)) {
        cout << "Inicio de sesion exitoso como " << usuarioAutenticado.getRol() << ".\n";

        if (usuarioAutenticado.getRol() == "ADMINISTRADOR") {
            bool salir = false;
            while (!salir) {
                cout << "\n--- Menu Principal ---\n";
                cout << "1. Usuarios\n";
                cout << "2. Medicos\n";
                cout << "3. Pacientes\n";
                cout << "4. Reportes\n";
                cout << "5. Guardar y salir\n";
                cout << "Ingrese su opcion: ";
                char opcionPrincipal;
                cin >> opcionPrincipal;

                if (opcionPrincipal == '1') {
                    bool salirUsuarios = false;
                    while (!salirUsuarios) {
                        cout << "\n--- Menu Usuarios ---\n";
                        cout << "1. Crear nuevo usuario\n";
                        cout << "2. Mostrar lista de usuarios\n";
                        cout << "3. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionUsuarios;
                        cin >> opcionUsuarios;

                        if (opcionUsuarios == '1') {
                            if (Usuario::CrearUsuario(usuarios)) {
                                cout << "Usuario creado exitosamente\n";
                            }
                        }
                        else if (opcionUsuarios == '2') {
                            Usuario::MostrarUsuarios(usuarios);
                        }
                        else if (opcionUsuarios == '3') {
                            salirUsuarios = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }

                }
                else if (opcionPrincipal == '2') {
                    bool salirMedicos = false;
                    while (!salirMedicos) {
                        cout << "\n--- Menu Medicos ---\n";
                        cout << "1. Crear medico\n";
                        cout << "2. Mostrar lista de medicos\n";
                        cout << "3. Modificar medico\n";
                        cout << "4. Eliminar medico\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionMedicos;
                        cin >> opcionMedicos;

                        if (opcionMedicos == '1') {
                            Usuario::CrearMedico();
                        }
                        else if (opcionMedicos == '2') {
                            Medico::MostrarMedicos();
                        }
                        else if (opcionMedicos == '3') {
                            if (usuarioAutenticado.VerificarPermiso(MODIFICAR_MEDICO)) {
                                Usuario::ModificarMedico();
                            }
                            else {
                                cout << "No tiene permiso para modificar medico.\n";
                            }
                        }
                        else if (opcionMedicos == '4') {
                            if (usuarioAutenticado.VerificarPermiso(ELIMINAR_MEDICO)) {
                                Usuario::EliminarMedico();
                            }
                            else {
                                cout << "No tiene permiso para eliminar medico.\n";
                            }
                        }
                        else if (opcionMedicos == '5') {
                            salirMedicos = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }

                }
                else if (opcionPrincipal == '3') {
                    bool salirPacientes = false;
                    while (!salirPacientes) {
                        cout << "\n--- Menu Pacientes ---\n";
                        cout << "1. Crear nuevo paciente\n";
                        cout << "2. Mostrar lista de pacientes\n";
                        cout << "3. Modificar paciente\n";
                        cout << "4. Eliminar paciente\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionPacientes;
                        cin >> opcionPacientes;

                        if (opcionPacientes == '1') {
                            if (usuarioAutenticado.VerificarPermiso(CREAR_PACIENTE)) {
                                Usuario::CrearPaciente();
                            }
                            else {
                                cout << "No tiene permiso para crear pacientes.\n";
                            }
                        }
                        else if (opcionPacientes == '2') {
                            Usuario::MostrarPacientes();
                        }
                        else if (opcionPacientes == '3') {
                            if (usuarioAutenticado.VerificarPermiso(MODIFICAR_PACIENTE)) {
                                Paciente::ModificarPaciente();
                            }
                            else {
                                cout << "No tiene permiso para modificar pacientes.\n";
                            }
                        }
                        else if (opcionPacientes == '4') {
                            if (usuarioAutenticado.VerificarPermiso(ELIMINAR_PACIENTE)) {
                                Usuario::EliminarPaciente();
                            }
                            else {
                                cout << "No tiene permiso para eliminar pacientes.\n";
                            }
                        }
                        else if (opcionPacientes == '5') {
                            salirPacientes = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }

                }
                else if (opcionPrincipal == '4') {
                    bool salirReportes = false;
                    while (!salirReportes) {
                        cout << "\n--- Menu Reportes ---\n";
                        cout << "1. Reporte de pacientes atendidos\n";
                        cout << "2. Reporte de medicos disponibles\n";
                        cout << "3. Reporte de citas pendientes por dia\n";
                        cout << "4. Reporte de citas pendientes por mes\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionReportes;
                        cin >> opcionReportes;

                        if (opcionReportes == '1') {
                            Reportes::ReportePacientesAtendidos();
                        }
                        else if (opcionReportes == '2') {
                            Reportes::ReporteMedicosDisponibles();
                        }
                        else if (opcionReportes == '3') {
                            Reportes::ReporteCitasPendientesPorDia();
                        }
                        else if (opcionReportes == '4') {
                            Reportes::ReporteCitasPendientesPorMes();
                        }
                        else if (opcionReportes == '5') {
                            salirReportes = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }

                }
                else if (opcionPrincipal == '5') {
                    Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
                    cout << "Usuarios guardados con exito\n";
                    salir = true;
                }
                else {
                    cout << "Opcion no valida.\n";
                }
            }

        }
        else {
            cout << "No tiene permisos para realizar esta accion.\n";
        }
    }
    else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>

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

class Paciente {
private:
    string Nombre;
    string DNI;
    string FechaNacimiento;
    string Telefono;
    string Correo;
    string FechaIngreso;
    string HistorialClinico;
public:
    Paciente() : Nombre(""), DNI(""), FechaNacimiento(""), Telefono(""), Correo(""), FechaIngreso(""), HistorialClinico("") {
    }
    Paciente(string nombre, string dni, string fechaNacimiento, string telefono, string correo, string fechaIngreso, string historialClinico)
        : Nombre(nombre), DNI(dni), FechaNacimiento(fechaNacimiento), Telefono(telefono), Correo(correo), FechaIngreso(fechaIngreso), HistorialClinico(historialClinico) {
    }
    string getNombre() const { return Nombre; }
    string getDNI() const { return DNI; }
    string getFechaNacimiento() const { return FechaNacimiento; }
    string getTelefono() const { return Telefono; }
    string getCorreo() const { return Correo; }
    string getFechaIngreso() const { return FechaIngreso; }
    string getHistorialClinico() const { return HistorialClinico; }
    void setNombre(const string& nombre) { Nombre = nombre; }
    void setDNI(const string& dni) { DNI = dni; }
    void setFechaNacimiento(const string& fechaNacimiento) { FechaNacimiento = fechaNacimiento; }
    void setTelefono(const string& telefono) { Telefono = telefono; }
    void setCorreo(const string& correo) { Correo = correo; }
    void setFechaIngreso(const string& fechaIngreso) { FechaIngreso = fechaIngreso; }
    void setHistorialClinico(const string& historialClinico) { HistorialClinico = historialClinico; }
    void MostrarPaciente() const {
        cout << "Nombre: " << Nombre << endl;
        cout << "DNI: " << DNI << endl;
        cout << "Fecha de Nacimiento: " << FechaNacimiento << endl;
        cout << "Telefono: " << Telefono << endl;
        cout << "Correo: " << Correo << endl;
        cout << "Fecha de Ingreso: " << FechaIngreso << endl;
        cout << "Historial Clinico: " << HistorialClinico << endl;
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

        string nombre, apellido, dni, correo, telefono, especialidad;
        int diaNacimiento, mesNacimiento, añoNacimiento;

        cout << "Ingrese el nombre del medico: ";
        cin >> nombre;
        cout << "Ingrese el apellido del medico: ";
        cin >> apellido;
        cout << "Ingrese el DNI del medico: ";
        cin >> dni;
        cout << "Ingrese el correo del medico: ";
        cin >> correo;
        cout << "Ingrese el telefono del medico: ";
        cin >> telefono;
        cout << "Ingrese el dia de nacimiento del medico: ";
        cin >> diaNacimiento;
        cout << "Ingrese el mes de nacimiento del medico: ";
        cin >> mesNacimiento;
        cout << "Ingrese el anio de nacimiento del medico: ";
        cin >> añoNacimiento;
        cout << "Ingrese la especialidad del medico: ";
        cin >> especialidad;

        time_t t = time(0);
        tm* now = localtime(&t);
        int añoActual = now->tm_year + 1900;
        int mesActual = now->tm_mon + 1;
        int diaActual = now->tm_mday;

        int edad = añoActual - añoNacimiento;
        if (mesActual < mesNacimiento || (mesActual == mesNacimiento && diaActual < diaNacimiento)) {
            edad--;
        }

        file << nombre << "," << apellido << "," << dni << "," << correo << "," << telefono << "," << añoNacimiento << "," << edad << "," << especialidad << "\n";
        file.close();

        cout << "Medico creado exitosamente:\n";
        cout << "Nombre: " << nombre << " " << apellido << "\n";
        cout << "DNI: " << dni << "\n";
        cout << "Correo: " << correo << "\n";
        cout << "Telefono: " << telefono << "\n";
        cout << "Fecha de nacimiento: " << diaNacimiento << "/" << mesNacimiento << "/" << añoNacimiento << "\n";
        cout << "Edad: " << edad << "\n";
        cout << "Especialidad: " << especialidad << "\n";
    }

    static void EliminarMedico() {
        string dni;
        cout << "Ingrese el DNI del medico a eliminar: ";
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

    static void MostrarMedicos() {
        ifstream file("medicos.csv");
        if (file.is_open()) {
            string linea;
            cout << "Lista de medicos:\n";
            cout << "--------------------------------------------------\n";
            while (getline(file, linea)) {
                if (!linea.empty()) {
                    cout << linea << "\n";
                }
            }
            cout << "--------------------------------------------------\n";
            file.close();
        }
        else {
            cerr << "Archivo de medicos no encontrado.\n";
        }
    }

    static void MostrarUsuarios(const vector<Usuario>& usuarios) {
        cout << "Lista de usuarios y permisos:\n";
        cout << "--------------------------------------------------\n";
        cout << "Nombre de Usuario\tRol\tPermisos\n";
        cout << "--------------------------------------------------\n";
        for (const auto& usuario : usuarios) {
            cout << usuario.getNombreUsuario() << "\t\t" << usuario.getRol() << "\t";

            const vector<bool>& permisos = usuario.getPermisos();
            cout << "[ ";
            for (size_t i = 0; i < permisos.size(); ++i) {
                cout << (permisos[i] ? "Si" : "No") << (i < permisos.size() - 1 ? ", " : " ");
            }
            cout << "]\n";
        }
        cout << "--------------------------------------------------\n";
    }

    // Métodos para manejo de pacientes:
    static void CrearPaciente() {
        ofstream file("pacientes.csv", ios::app);
        if (!file.is_open()) {
            cerr << "Error al abrir el archivo para guardar el paciente.\n";
            return;
        }

        cin.ignore();
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

        cout << "Paciente creado exitosamente.\n";
    }

    static void MostrarPacientes() {
        ifstream file("pacientes.csv");
        if (file.is_open()) {
            string linea;
            cout << "Lista de pacientes:\n";
            cout << "--------------------------------------------------\n";
            while (getline(file, linea)) {
                if (!linea.empty()) {
                    cout << linea << "\n";
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
        string dni;
        cout << "Ingrese el DNI del paciente a eliminar: ";
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
                continue; // omitimos esta línea (eliminamos el paciente)
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
            char opcion;
            bool salir = false;

            while (!salir) {
                cout << "Opciones:\n";
                cout << "1. Crear nuevo usuario\n";
                cout << "2. Mostrar lista de usuarios\n";
                cout << "3. Crear medico\n";
                cout << "4. Mostrar lista de medicos\n";
                cout << "5. Guardar y salir\n";
                cout << "6. Eliminar medico\n";
                cout << "7. Crear paciente\n";
                cout << "8. Mostrar pacientes\n";
                cout << "9. Eliminar paciente\n";
                cout << "Ingrese su opcion: ";
                cin >> opcion;

                if (opcion == '1') {
                    if (Usuario::CrearUsuario(usuarios)) {
                        cout << "Usuario creado exitosamente\n";
                    }
                }
                else if (opcion == '2') {
                    Usuario::MostrarUsuarios(usuarios);
                }
                else if (opcion == '3') {
                    Usuario::CrearMedico();
                }
                else if (opcion == '4') {
                    Usuario::MostrarMedicos();
                }
                else if (opcion == '5') {
                    Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
                    cout << "Usuarios guardados con exito\n";
                    salir = true;
                }
                else if (opcion == '6') {
                    Usuario::EliminarMedico();
                }
                else if (opcion == '7') {
                    if (usuarioAutenticado.VerificarPermiso(CREAR_PACIENTE)) {
                        Usuario::CrearPaciente();
                    }
                    else {
                        cout << "No tiene permiso para crear pacientes.\n";
                    }
                }
                else if (opcion == '8') {
                    Usuario::MostrarPacientes();
                }
                else if (opcion == '9') {
                    if (usuarioAutenticado.VerificarPermiso(ELIMINAR_PACIENTE)) {
                        Usuario::EliminarPaciente();
                    }
                    else {
                        cout << "No tiene permiso para eliminar pacientes.\n";
                    }
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

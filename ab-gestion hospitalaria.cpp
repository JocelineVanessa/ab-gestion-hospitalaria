#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

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
                cout << (permisos[i] ? "Sí" : "No") << (i < permisos.size() - 1 ? ", " : " ");
            }
            cout << "]\n";
        }
        cout << "--------------------------------------------------\n";
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
    vector<Usuario> usuarios;
    const string archivoUsuarios = "usuarios.csv";

    Usuario::CargarUsuarios(usuarios, archivoUsuarios);

    if (usuarios.empty()) {
        cout << "No se encontraron usuarios. Creando usuario administrador...\n";
        usuarios.push_back(Usuario("JocelineRamirez", "1234", "ADMINISTRADOR"));
        Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
        cout << "Usuario administrador creado.\n";
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
                cout << "3. Guardar y salir\n";
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
            cout << "Usted no tiene permisos para realizar esta accion.\n";
        }
    }

    return 0;

}
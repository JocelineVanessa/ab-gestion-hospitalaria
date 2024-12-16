#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum PermisoIndex {
    CREAR_PACIENTE = 0,
    MODIFICAR_PACIENTE,
    ELIMINAR_PACIENTE,
    CREAR_CITA,
    MODIFICAR_CITA,
    ELIMINAR_CITA,
    TOTAL_PERMISOS
};

class Usuario {
private:
    string nombreUsuario;
    string contraseña;
    string rol;
    vector<bool> permisos;

public:
    Usuario(string nombreUsuario, string contraseña, string rol)
        : nombreUsuario(nombreUsuario), contraseña(contraseña), rol(rol), permisos(TOTAL_PERMISOS, false) {
        if (rol == "ADMINISTRADOR") {
            permisos.assign(TOTAL_PERMISOS, true);
        }
    }

    string getNombreUsuario() const { return nombreUsuario; }
    string getRol() const { return rol; }
    bool VerificarPermiso(PermisoIndex permiso) const { return permiso < permisos.size() && permisos[permiso]; }
    void AsignarPermiso(PermisoIndex permiso) { if (permiso < permisos.size()) permisos[permiso] = true; }
    void QuitarPermiso(PermisoIndex permiso) { if (permiso < permisos.size()) permisos[permiso] = false; }
    bool ValidarContraseña(const string& inputContraseña) const { return inputContraseña == contraseña; }

    bool CrearUsuario(const string& adminContraseña, vector<Usuario>& usuarios, const string& nuevoNombre, const string& nuevaContraseña, const string& nuevoRol) {
        if (rol == "ADMINISTRADOR" && ValidarContraseña(adminContraseña)) {
            usuarios.push_back(Usuario(nuevoNombre, nuevaContraseña, nuevoRol));
            return true;
        }
        return false;
    }

    bool AsignarPermisoAUsuario(const string& adminContraseña, Usuario& usuario, PermisoIndex permiso) {
        if (rol == "ADMINISTRADOR" && ValidarContraseña(adminContraseña)) {
            usuario.AsignarPermiso(permiso);
            return true;
        }
        return false;
    }

    bool QuitarPermisoAUsuario(const string& adminContraseña, Usuario& usuario, PermisoIndex permiso) {
        if (rol == "ADMINISTRADOR" && ValidarContraseña(adminContraseña)) {
            usuario.QuitarPermiso(permiso);
            return true;
        }
        return false;
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
    Usuario admin("Administrador", "123", "ADMINISTRADOR");
    usuarios.push_back(admin);

    admin.CrearUsuario("admin123", usuarios, "LilianVelez", "123", "RECEPCIONISTA");
    admin.CrearUsuario("admin123", usuarios, "GabrielPerez", "456", "RECEPCIONISTA");
    admin.CrearUsuario("admin123", usuarios, "ClaudiaMuñoz", "789", "RECEPCIONISTA");
    admin.CrearUsuario("admin123", usuarios, "AndreaRamirez", "012", "RECEPCIONISTA");

    admin.CrearUsuario("admin123", usuarios, "JenniferMuñoz", "123", "MEDICO");
    admin.CrearUsuario("admin123", usuarios, "OmarQuiroga", "456", "MEDICO");
    admin.CrearUsuario("admin123", usuarios, "NaomiMontilla", "789", "MEDICO");
    admin.CrearUsuario("admin123", usuarios, "JuliethGonzalez", "012", "MEDICO");

    string nombreUsuario, contraseña;
    cout << "Ingrese el nombre de usuario: ";
    cin >> nombreUsuario;
    cout << "Ingrese la contraseña: ";
    cin >> contraseña;

    Usuario usuarioAutenticado("", "", "");
    if (IniciarSesion(nombreUsuario, contraseña, usuarios, usuarioAutenticado)) {
        cout << "Inicio de sesión exitoso como " << usuarioAutenticado.getRol() << ".\n";

        if (usuarioAutenticado.getRol() == "ADMINISTRADOR") {
            cout << "El usuario es un administrador.\n";
            admin.CrearUsuario("admin123", usuarios, "LilianVelez", "123", "RECEPCIONISTA");
        }
    }
    else {
        cout << "Credenciales incorrectas.\n";
    }

    return 0;
}
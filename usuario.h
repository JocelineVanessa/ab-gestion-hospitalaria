#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <vector>

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
    void AsignarPermisosPorRol();

public:
    Usuario(string nombreUsuario = "", string contraseña = "", string rol = "");

    string getNombreUsuario() const;
    string getRol() const;
    const vector<bool>& getPermisos() const;

    bool VerificarPermiso(PermisoIndex permiso) const;
    bool ValidarContraseña(const string& inputContraseña) const;
    void MostrarUsuario() const;

    static void GuardarUsuarios(const vector<Usuario>& usuarios, const string& archivo);
    static void CargarUsuarios(vector<Usuario>& usuarios, const string& archivo);
    static bool CrearUsuario(vector<Usuario>& usuarios);
};
#endif 

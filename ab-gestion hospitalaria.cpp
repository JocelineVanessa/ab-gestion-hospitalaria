#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <limits>
#include "Paciente.h"
#include "Medico.h"
#include "Usuario.h"

using namespace std;    

    static void MostrarUsuarios(const vector<Usuario>& usuarios) {
        cout << "Lista de usuarios:\n";
        cout << "--------------------------------------------------\n";
        for (const auto& u : usuarios) {
            u.MostrarUsuario();
        }
        cout << "--------------------------------------------------\n";
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
                            Medico::CrearMedico();
                        }
                        else if (opcionMedicos == '2') {
                            Medico::MostrarMedicos();
                        }
                        else if (opcionMedicos == '3') {
                            if (usuarioAutenticado.VerificarPermiso(MODIFICAR_MEDICO)) {
                                Medico::ModificarMedico();
                            }
                            else {
                                cout << "No tiene permiso para modificar medico.\n";
                            }
                        }
                        else if (opcionMedicos == '4') {
                            if (usuarioAutenticado.VerificarPermiso(ELIMINAR_MEDICO)) {
                                Medico::EliminarMedico();
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
                                Paciente::CrearPaciente();
                            }
                            else {
                                cout << "No tiene permiso para crear pacientes.\n";
                            }
                        }
                        else if (opcionPacientes == '2') {
                            Paciente::MostrarPacientes();
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
                                Paciente::EliminarPaciente();
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


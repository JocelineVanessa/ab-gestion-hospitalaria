#include "Paciente.h"
#include "Medico.h"
#include "Usuario.h"
#include "Reportes.h"
#include "Citas.h"

using namespace std;    

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
                cout << "4. Citas\n";
                cout << "5. Reportes\n";
                cout << "6. Guardar y salir\n";
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
                        cout << "5. Lista medicos por especialidad\n";
                        cout << "6. Lista medicos disponibles por mes\n";
                        cout << "7. Volver al menu principal\n";
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
                            string especialidad;
                            cout << "Ingrese la especialidad: ";
                            cin.ignore();
                            getline(cin, especialidad);
                            Medico::ListaMedicosPorEspecialidad(especialidad);
                        }
                        else if (opcionMedicos == '6') {
                            string mes;
                            cout << "Ingrese el mes (MM): ";
                            cin >> mes;
                            Medico::ListaMedicosDisponiblesPorMes(mes);
                        }
                        else if (opcionMedicos == '7') {
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
                        cout << "4. Buscar paciente por DNI\n";
                        cout << "5. Buscar paciente por Nombre\n";
                        cout << "6. Eliminar paciente\n";
                        cout << "7. Volver al menu principal\n";
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
                            Paciente::BuscarPacientePorDNI();
                        }
                        else if (opcionPacientes == '5') {
                            Paciente::BuscarPacientePorNombre();
                        }
                        else if (opcionPacientes == '6') {
                            if (usuarioAutenticado.VerificarPermiso(ELIMINAR_PACIENTE)) {
                                Paciente::EliminarPaciente();
                            }
                            else {
                                cout << "No tiene permiso para eliminar pacientes.\n";
                            }
                        }
                        else if (opcionPacientes == '7') {
                            salirPacientes = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }

                }
                else if (opcionPrincipal == '4') {
                    bool salirCitas = false;
                    while (!salirCitas) {
                        cout << "\n--- Menu Citas ---\n";
                        cout << "1. Crear nueva cita\n";
                        cout << "2. Mostrar citas\n";
                        cout << "3. Modificar una cita\n";
                        cout << "4. Eliminar una cita\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionCitas;
                        cin >> opcionCitas;

                        if (opcionCitas == '1') {
                            Citas::CrearCita();
                        }
                        else if (opcionCitas == '2') {
                            Citas::MostrarCitas();
                        }
                        else if (opcionCitas == '3') {
                            Citas::ModificarCita();
                        }
                        else if (opcionCitas == '4') {
                            Citas::EliminarCita();
                        }
                        else if (opcionCitas == '5') {
                            salirCitas = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                    }
                else if (opcionPrincipal == '5') {
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
                            cout << "Ingrese la fecha para el reporte (YYYY-MM-DD): ";
                            string fechaReporte;
                            cin >> fechaReporte;
                            Reportes::ReportePacientesAtendidos(fechaReporte);
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
                else if (opcionPrincipal == '6') {
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
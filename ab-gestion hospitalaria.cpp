#include "Paciente.h"
#include "Medico.h"
#include "Usuario.h"
#include "Reportes.h"
#include "Citas.h"
#include "OtrosServicios.h"
#include "CopiaSeguridad.h"

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
                cout << "\n--- Menu Principal (Administrador) ---\n";
                cout << "1. Usuarios\n";
                cout << "2. Medicos\n";
                cout << "3. Pacientes\n";
                cout << "4. Citas\n";
                cout << "5. Reportes\n";
                cout << "6. Otros servicios\n";
                cout << "7. Copia de seguridad\n";
                cout << "8. Guardar y salir\n";
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
                            Medico::ModificarMedico();
                        }
                        else if (opcionMedicos == '4') {
                            Medico::EliminarMedico();
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
                        cout << "5. Buscar paciente por nombre\n";
                        cout << "6. Eliminar paciente\n";
                        cout << "7. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionPacientes;
                        cin >> opcionPacientes;

                        if (opcionPacientes == '1') {
                            Paciente::CrearPaciente();
                        }
                        else if (opcionPacientes == '2') {
                            Paciente::MostrarPacientes();
                        }
                        else if (opcionPacientes == '3') {
                            Paciente::ModificarPaciente();
                        }
                        else if (opcionPacientes == '4') {
                            Paciente::BuscarPacientePorDNI();
                        }
                        else if (opcionPacientes == '5') {
                            Paciente::BuscarPacientePorNombre();
                        }
                        else if (opcionPacientes == '6') {
                            Paciente::EliminarPaciente();
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
                            string fechaReporte;
                            cout << "Ingrese la fecha para el reporte (YYYY-MM-DD): ";
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
                    bool salirServicios = false;
                    while (!salirServicios) {
                        cout << "\n--- Menu Otros Servicios ---\n";
                        cout << "1. Agregar servicio\n";
                        cout << "2. Mostrar lista de servicios\n";
                        cout << "3. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionServicios;
                        cin >> opcionServicios;

                        if (opcionServicios == '1') {
                            OtrosServicios::AgregarServicio();
                        }
                        else if (opcionServicios == '2') {
                            OtrosServicios::MostrarServicios();
                        }
                        else if (opcionServicios == '3') {
                            salirServicios = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipal == '7') {
                    char confirmar;
                    cout << "Desea realizar una copia de seguridad de los archivos? (s/n): ";
                    cin >> confirmar;
                    if (confirmar == 's' || confirmar == 'S') {
                        CopiaSeguridad::RealizarCopiaSeguridad();
                    }
                    else {
                        cout << "Copia de seguridad cancelada.\n";
                    }
                }
                else if (opcionPrincipal == '8') {
                    Usuario::GuardarUsuarios(usuarios, archivoUsuarios);
                    cout << "Usuarios guardados con exito\n";
                    salir = true;
                }
                else {
                    cout << "Opcion no valida.\n";
                }
            }
        }
        else if (usuarioAutenticado.getRol() == "MEDICO") {
            bool salir = false;
            while (!salir) {
                cout << "\n--- Menu Principal (Medico) ---\n";
                cout << "1. Citas\n";
                cout << "2. Pacientes\n";
                cout << "3. Otros servicios\n";
                cout << "4. Copia de seguridad\n";
                cout << "5. Guardar y salir\n";
                cout << "Ingrese su opcion: ";
                char opcionPrincipalMedico;
                cin >> opcionPrincipalMedico;

                if (opcionPrincipalMedico == '1') {
                    bool salirCitas = false;
                    while (!salirCitas) {
                        cout << "\n--- Menu Citas (Medico) ---\n";
                        cout << "1. Mostrar citas\n";
                        cout << "2. Modificar una cita\n";
                        cout << "3. Eliminar una cita\n";
                        cout << "4. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionCitas;
                        cin >> opcionCitas;

                        if (opcionCitas == '1') {
                            Citas::MostrarCitas();
                        }
                        else if (opcionCitas == '2') {
                            Citas::ModificarCita();
                        }
                        else if (opcionCitas == '3') {
                            Citas::EliminarCita();
                        }
                        else if (opcionCitas == '4') {
                            salirCitas = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipalMedico == '2') {
                    bool salirPacientes = false;
                    while (!salirPacientes) {
                        cout << "\n--- Menu Pacientes (Medico) ---\n";
                        cout << "1. Mostrar lista de pacientes\n";
                        cout << "2. Modificar paciente\n";
                        cout << "3. Buscar paciente por DNI\n";
                        cout << "4. Buscar paciente por nombre\n";
                        cout << "5. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionPacientesMedico;
                        cin >> opcionPacientesMedico;

                        if (opcionPacientesMedico == '1') {
                            Paciente::MostrarPacientes();
                        }
                        else if (opcionPacientesMedico == '2') {
                            if (usuarioAutenticado.VerificarPermiso(MODIFICAR_PACIENTE)) {
                                Paciente::ModificarPaciente();
                            }
                            else {
                                cout << "No tiene permiso para modificar pacientes.\n";
                            }
                        }
                        else if (opcionPacientesMedico == '3') {
                            Paciente::BuscarPacientePorDNI();
                        }
                        else if (opcionPacientesMedico == '4') {
                            Paciente::BuscarPacientePorNombre();
                        }
                        else if (opcionPacientesMedico == '5') {
                            salirPacientes = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipalMedico == '3') {
                    bool salirServicios = false;
                    while (!salirServicios) {
                        cout << "\n--- Menu Otros Servicios ---\n";
                        cout << "1. Agregar servicio\n";
                        cout << "2. Mostrar lista de servicios\n";
                        cout << "3. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionServiciosMedico;
                        cin >> opcionServiciosMedico;

                        if (opcionServiciosMedico == '1') {
                            OtrosServicios::AgregarServicio();
                        }
                        else if (opcionServiciosMedico == '2') {
                            OtrosServicios::MostrarServicios();
                        }
                        else if (opcionServiciosMedico == '3') {
                            salirServicios = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipalMedico == '4') {
                    char confirmar;
                    cout << "Desea realizar una copia de seguridad de los archivos? (s/n): ";
                    cin >> confirmar;
                    if (confirmar == 's' || confirmar == 'S') {
                        CopiaSeguridad::RealizarCopiaSeguridad();
                    }
                    else {
                        cout << "Copia de seguridad cancelada.\n";
                    }
                }
                else if (opcionPrincipalMedico == '5') {
                    salir = true;
                }
                else {
                    cout << "Opcion no valida.\n";
                }
            }
            }

        else if (usuarioAutenticado.getRol() == "RECEPCIONISTA") {
            bool salir = false;
            while (!salir) {
                cout << "\n--- Menu Principal (Recepcionista) ---\n";
                cout << "1. Citas\n";
                cout << "2. Pacientes\n";
                cout << "3. Reportes\n";
                cout << "4. Otros servicios\n";
                cout << "5. Copia de seguridad\n";
                cout << "6. Guardar y salir\n";
                cout << "Ingrese su opcion: ";
                char opcionPrincipalRecepcionista;
                cin >> opcionPrincipalRecepcionista;

                if (opcionPrincipalRecepcionista == '1') {
                    bool salirCitas = false;
                    while (!salirCitas) {
                        cout << "\n--- Menu Citas (Recepcionista) ---\n";
                        cout << "1. Crear cita\n";
                        cout << "2. Mostrar citas\n";
                        cout << "3. Modificar citas\n";
                        cout << "4. Eliminar citas\n";
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
                else if (opcionPrincipalRecepcionista == '2') {
                    bool salirPacientes = false;
                    while (!salirPacientes) {
                        cout << "\n--- Menu Pacientes (Recepcionista) ---\n";
                        cout << "1. Crear paciente\n";
                        cout << "2. Modificar pacientes\n";
                        cout << "3. Mostrar pacientes\n";
                        cout << "4. Buscar pacientes por DNI\n";
                        cout << "5. Buscar pacientes por nombre\n";
                        cout << "6. Eliminar pacientes\n";
                        cout << "7. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionPacientes;
                        cin >> opcionPacientes;

                        if (opcionPacientes == '1') {
                            Paciente::CrearPaciente();
                        }
                        else if (opcionPacientes == '2') {
                            Paciente::ModificarPaciente();
                        }
                        else if (opcionPacientes == '3') {
                            Paciente::MostrarPacientes();
                        }
                        else if (opcionPacientes == '4') {
                            Paciente::BuscarPacientePorDNI();
                        }
                        else if (opcionPacientes == '5') {
                            Paciente::BuscarPacientePorNombre();
                        }
                        else if (opcionPacientes == '6') {
                            Paciente::EliminarPaciente();
                        }
                        else if (opcionPacientes == '7') {
                            salirPacientes = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipalRecepcionista == '3') {
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
                            string fechaReporte;
                            cout << "Ingrese la fecha para el reporte (YYYY-MM-DD): ";
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
                else if (opcionPrincipalRecepcionista == '4') {
                    bool salirServicios = false;
                    while (!salirServicios) {
                        cout << "\n--- Menu Otros Servicios ---\n";
                        cout << "1. Agregar servicio\n";
                        cout << "2. Mostrar lista de servicios\n";
                        cout << "3. Volver al menu principal\n";
                        cout << "Ingrese su opcion: ";
                        char opcionServicios;
                        cin >> opcionServicios;

                        if (opcionServicios == '1') {
                            OtrosServicios::AgregarServicio();
                        }
                        else if (opcionServicios == '2') {
                            OtrosServicios::MostrarServicios();
                        }
                        else if (opcionServicios == '3') {
                            salirServicios = true;
                        }
                        else {
                            cout << "Opcion no valida.\n";
                        }
                    }
                }
                else if (opcionPrincipalRecepcionista == '5') {
                    char confirmar;
                    cout << "Desea realizar una copia de seguridad de los archivos? (s/n): ";
                    cin >> confirmar;
                    if (confirmar == 's' || confirmar == 'S') {
                        CopiaSeguridad::RealizarCopiaSeguridad();
                    }
                    else {
                        cout << "Copia de seguridad cancelada.\n";
                    }
                }
                else if (opcionPrincipalRecepcionista == '6') {
                    salir = true;
                }
                else {
                    cout << "Opcion no valida.\n";
                }
            }
            }

    }
    else {
        cout << "Usuario o contraseña incorrectos.\n";
    }

    return 0;
}


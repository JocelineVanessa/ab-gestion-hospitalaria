#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>
using namespace std;

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
    Paciente();
    Paciente(string nombre, string dni, string fechaNacimiento, string telefono, string correo, string fechaIngreso, string historialClinico);
     

    string getNombre() const;
    string getDNI() const;
    string getFechaNacimiento() const;
    string getTelefono() const;
    string getCorreo() const;
    string getFechaIngreso() const;
    string getHistorialClinico() const;

    void setNombre(const string& nombre);
    void setDNI(const string& dni);
    void setFechaNacimiento(const string& fechaNacimiento);
    void setTelefono(const string& telefono);
    void setCorreo(const string& correo) { Correo = correo; }
    void setFechaIngreso(const string& fechaIngreso);
    void setHistorialClinico(const string& historialClinico);

    int getEdad() const;
    void MostrarPaciente() const;
    static void ModificarPaciente();
};

#endif 


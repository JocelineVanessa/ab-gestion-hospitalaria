#ifndef MEDICO_H
#define MEDICO_H

#include <string>
using namespace std;

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
    Medico();
    Medico(string nombre, string dni, string fechaNacimiento, string correo, string telefono, int edad, string especialidad);

    string getNombre() const;
    string getDNI() const;
    string getFechaNacimiento() const;
    string getCorreo() const;
    string getTelefono() const;
    int getEdad() const;
    string getEspecialidad() const;

    void setNombre(const string& nombre);
    void setDNI(const string& dni);
    void setFechaNacimiento(const string& fechaNacimiento);
    void setCorreo(const string& correo);
    void setTelefono(const string& telefono);
    void setEdad(int edad);
    void setEspecialidad(const string& especialidad);

    void MostrarMedico() const;
    static void MostrarMedicos();
    static int CalcularEdad(const string& fechaNacimiento);
};

#endif


   
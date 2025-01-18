#ifndef CITAS_H
#define CITAS_H

#include <string>
#include <vector>

using namespace std;

class Citas {
private:
    string fecha;        
    string hora;         
    string pacienteID;   
    string medicoID;  
    string nivelDeUrgencia;

public:
    Citas();
    Citas(const string& fecha, const string& hora, const string& pacienteID, const string& medicoID, const string& nivelDeUrgencia);

    string getFecha() const;
    string getHora() const;
    string getPacienteID() const;
    string getMedicoID() const;
    string getnivelDeUrgencia()const;

    void setFecha(const string& fecha);
    void setHora(const string& hora);
    void setPacienteID(const string& pacienteID);
    void setMedicoID(const string& medicoID);
    void setnivelDeUrgencia(const string& nivelDeUrgencia);

    static void CrearCita(); 
    void MostrarCita() const;
    static void MostrarCitas();
    static void ModificarCita();
    static void EliminarCita();
};

#endif
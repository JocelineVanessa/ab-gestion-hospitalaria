#ifndef CITAS_H
#define CITAS_H

#include <string>
using namespace std;

class Citas {
private:
    string fecha;        
    string hora;         
    string pacienteID;   
    string medicoID;     

public:
    Citas();
    Citas(const string& fecha, const string& hora, const string& pacienteID, const string& medicoID);

    string getFecha() const;
    string getHora() const;
    string getPacienteID() const;
    string getMedicoID() const;

    void setFecha(const string& fecha);
    void setHora(const string& hora);
    void setPacienteID(const string& pacienteID);
    void setMedicoID(const string& medicoID);

    static void CrearCita();        
};

#endif
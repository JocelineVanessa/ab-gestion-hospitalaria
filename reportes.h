#ifndef REPORTES_H
#define REPORTES_H

#include <iostream>
#include <string>
#include <vector>
#include "Paciente.h"
#include "Medico.h"

using namespace std;

class Reportes {
public:
    static void ReportePacientesAtendidos();
    static void ReporteMedicosDisponibles();
    static void ReporteCitasPendientesPorDia();
    static void ReporteCitasPendientesPorMes();
};

#endif
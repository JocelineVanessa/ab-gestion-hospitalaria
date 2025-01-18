#ifndef OTROSSERVICIOS_H
#define OTROSSERVICIOS_H

#include <string>
#include <vector>

class OtrosServicios {
private:
    std::string nombreServicio;
    std::string descripcion;

public:
    OtrosServicios();
    OtrosServicios(const std::string& nombreServicio, const std::string& descripcion);

    std::string getNombreServicio() const;
    std::string getDescripcion() const;

    void setNombreServicio(const std::string& nombreServicio);
    void setDescripcion(const std::string& descripcion);

    static void AgregarServicio();
    static void MostrarServicios();
};

#endif

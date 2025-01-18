#ifndef COPIASEGURIDAD_H
#define COPIASEGURIDAD_H

#include <string>

class CopiaSeguridad {
public:
    static void RealizarCopiaSeguridad();

private:
    static void CopiarArchivo(const std::string& origen, const std::string& destino);
};

#endif

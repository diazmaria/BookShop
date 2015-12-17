#ifndef AUTOR_H_
#define AUTOR_H_
#include "cadena.h"

class Autor
{
    public:

        Autor(const Cadena& nom, const Cadena& ap, const Cadena& dir):nombre_(nom), apellidos_(ap), direccion_(dir){}

        Cadena nombre() const { return nombre_; }
        Cadena apellidos() const { return apellidos_; }
        Cadena direccion() const { return direccion_; }

    private:

        Cadena nombre_, apellidos_, direccion_;
};

#endif

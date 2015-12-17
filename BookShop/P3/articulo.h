#ifndef ARTICULO_H_
#define ARTICULO_H_
#include "fecha.h"
#include "cadena.h"

class Articulo{

    public:

        Articulo(const Cadena& cr, const Cadena& tit, const Fecha& fp, double prec, unsigned int exis);

        Cadena referencia() const {return referencia_;}
        Cadena titulo() const {return titulo_;}
        Fecha f_publi() const {return f_publi_;}
        double precio() const {return precio_;}
        double& precio() {return precio_;}
        unsigned int stock() const {return stock_;}
        unsigned int& stock() {return stock_;}

        friend ostream& operator <<(ostream& os, const Articulo& a);

    private:

        Cadena referencia_, titulo_;
        Fecha f_publi_;
        double precio_;
        unsigned int stock_;
};

#endif

#include "articulo.h"
#include <iomanip>
#include <iostream>
#include <set>

using namespace std;

 Articulo::Articulo(const Autores& a, const Cadena& cr, const Cadena& tit, const Fecha& fp, double prec) : autores_(a), referencia_(cr), titulo_(tit), f_publi_(fp), precio_(prec){
		if (a.empty()) throw Articulo::Autores_vacios();
}

void imp_prologo(ostream& os, const Articulo& a)
{
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", ";
}

void imp_epilogo(ostream& os, const Articulo& a)
{
    os << a.f_publi().anno() << ". " << fixed
       << setprecision(2) << a.precio() << " €";
}

void imp_autores(ostream& os, const Articulo& a)
{
    os << "de ";

    Articulo::Autores::const_iterator i;

    for(i = a.autores().begin(); i != a.autores().end(); i++)
    {
        os << (*i)->apellidos();

        if  (i != --(a.autores().end()))
            os << ", ";
    }

    os << ". ";
}

ostream& operator <<(ostream& os, const Articulo& a)
{

    imp_prologo(os, a);
    imp_autores(os, a);
    imp_epilogo(os, a);

    os << "\n\t";

    a.imp_esp(os);

    return os;
}


void Libro::imp_esp(ostream& os) const
{
    os << n_pag() << " págs., " << stock() << " unidades.";
}


void Cederron::imp_esp(ostream& os) const
{
    os << tam() << " MB, " << stock() << " unidades.";
}


void LibroDigital::imp_esp(ostream& os) const
{
    os << "A la venta hasta el " << f_expir() << ".";
}

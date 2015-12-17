#include "articulo.h"
#include <iomanip>

using namespace std;


Articulo::Articulo(const Cadena& cr, const Cadena& tit, const Fecha& fp, double prec, unsigned int exis) : referencia_(cr), titulo_(tit), f_publi_(fp), precio_(prec), stock_(exis) {}


ostream& operator <<(ostream& os, const Articulo& a)
{
    os << "[" << a.referencia() << "] \"" << a.titulo() << "\", "<< a.f_publi().anno() << ". " << fixed << setprecision(2) << a.precio() << " €";

    return os;
}

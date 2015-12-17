#include "pedido.h"
#include "tarjeta.h"
#include "pedido-articulo.h"
#include <iomanip>
#include "articulo.h"
#include "usuario.h"

using namespace std;

int Pedido::N_pedidos(0);

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f) : tarjeta_(&t), fecha_(f)
{
    if (tarjeta_->caducidad() <f ) throw Tarjeta::Caducada(tarjeta_->caducidad());
    if ( t.titular() != &u) throw Pedido::Impostor(u);

    numero_=Pedido::N_pedidos+1;

    double tot=0;

    Fecha hoy;
    bool vacio = true;
    typename Usuario::Articulos::iterator i = u.compra().begin();
    if (i== u.compra().end()) throw Pedido::Vacio(u);

    while ( i!= u.compra().end()) {
      if (LibroDigital *lb = dynamic_cast<LibroDigital *>(i->first)) {
	if (hoy < lb->f_expir ())  {
	  pa.pedir(*this, *(i->first), (i->first)->precio(), i->second);
	  tot += ((i->first)->precio())*(i->second);
	  vacio=false;
	}
      }
      else {
	ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable *>(i->first);
	if (i->second > aa->stock() ) {
	    Articulo *a = aa; 
	    u.compra().clear();
	    throw Pedido::SinStock(*a);
	}

	aa->stock() -= i->second;
	pa.pedir(*this, *aa, aa->precio(), i->second);
	tot += (aa->precio())*(i->second);
	vacio=false;
	aa=0;
      }
      ++i;
    }

  if (vacio) throw Pedido::Vacio(u);
  u.compra().clear();
  Pedido::N_pedidos++;
  total_=tot;
  up.asocia(u,*this);
  
}


ostream& operator <<(ostream& os, const Pedido& p)
{
    os << CIAN "   Núm. pedido: " << p.numero() << endl
    << NORMAL "   Fecha: \t" << p.fecha() << endl
    << "   Pagado con: \t" << p.tarjeta()->numero() << endl
    << "   Importe: \t" << p.total() << " €" << endl;

    return os;
}

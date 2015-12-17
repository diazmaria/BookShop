#include "pedido.h"
#include "tarjeta.h"
#include "pedido-articulo.h"
#include <iomanip>

int Pedido::N_pedidos(0);

using namespace std;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f) : numero_(N_pedidos+1), tarjeta_(&t), fecha_(f), total_(0.0)
{
    	if(u.n_articulos() == 0) throw Vacio(u);

	if(t.titular() != &u) throw Impostor(u);

	if(t.caducidad() < f) throw Tarjeta::Caducada(t.caducidad());

	Usuario::Articulos::const_iterator i;

	for (i = u.compra().begin(); i != u.compra().end(); i++)
	{
       		total_ += (i->first->precio()) * (i->second);

		if (i->second > (i->first->stock()))
		{
            		u.compra(*i->first, 0);
			throw SinStock (*(i->first));
		}

		i->first->stock() -= i->second;

		pa.pedir(*this, *i->first, i->first->precio(), i->second);

		u.compra(*i->first, 0);
	}

	N_pedidos++;
	up.asocia(u, *this);
}


ostream& operator <<(ostream& os, const Pedido& p)
{
    os << "   Núm. pedido: " << p.numero() << endl
    << "   Fecha: \t" << p.fecha() << endl
    << "   Pagado con: \t" << p.tarjeta()->numero() << endl
    << "   Importe: \t" << p.total() << " €" << endl;

    return os;
}

#include "pedido-articulo.h"
#include <iomanip>


ostream& operator <<(ostream& os, const LineaPedido& lp)
{
    os << fixed << setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();

	return os;
}


bool OrdenaPedidos::operator()(Pedido* p1, Pedido* p2) const
{
    return (p1->numero() < p2->numero());
}


bool OrdenaArticulos::operator()(Articulo* a1, Articulo* a2) const
{
    return (a1->referencia() < a2->referencia());
}


void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double prec, unsigned int cant)
{
	LineaPedido lp(prec, cant);

	directa[&p].insert(make_pair(&a,lp));
	inversa[&a].insert(make_pair(&p,lp));
}


void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double prec, unsigned int cant)
{
	pedir(p, a, prec, cant);
}


void Pedido_Articulo::mostrarDetallePedidos(ostream& os) const
{
    double aux = 0.0, total = 0.0;

    for(map<Pedido*, Pedido_Articulo::ItemsPedido>::const_iterator i = directa.begin(); i != directa.end(); i++)
    {
        os << "Pedido núm. " << i->first->numero() << endl
        << "Cliente: " << i->first->tarjeta()->titular()->id()
        << "\t\tFecha: " << i->first->fecha() << endl
        << setfill('=') << setw(66) << "" << endl
        << "  PVP\tCantidad\tArtículo" << endl
        << setfill('=') << setw(66) << "" << endl;

        for(Pedido_Articulo::ItemsPedido::const_iterator j = i->second.begin(); j != i->second.end(); j++)
        {
            os << j->second << "\t\t[" << j->first->referencia() << "] \"" << j->first->titulo() << "\"" << endl;

            aux += (j->second.precio_venta()) * (j->second.cantidad());
        }

        os << setfill('=') << setw(66) << "" << endl
        << "Total\t" << aux << " €\n\n\n";

        total += aux;
        aux = 0.0;
    }

    os << "TOTAL VENTAS\t" << total << " €\n\n" << endl;
}


void Pedido_Articulo::mostrarVentasArticulos(ostream& os) const
{
	double aux = 0.0;
	int total = 0;

	for(map<Articulo*, Pedido_Articulo::Pedidos>::const_iterator i = inversa.begin(); i != inversa.end(); i++)
	{
        os << "Ventas de [" << i->first->referencia() << "] \"" << i->first->titulo()
        << "\" [Pedidos: "<< i->second.size() << "]" << endl
        << setfill('=') << setw(66) << "" << endl
        << "  PVP\t\tCantidad\tFecha venta" << endl
        << setfill('=') << setw(66) << "" << endl;

  	for(Pedido_Articulo::Pedidos::const_iterator j = i->second.begin(); j != i->second.end(); j++)
  	{
  		os << " " << j->second << "\t\t" << j->first->fecha() << endl;

  		aux += (j->second.precio_venta()) * (j->second.cantidad());
  		total += j->second.cantidad();
  	}

  	os << setfill('=') << setw(66) << "" << endl
  	<< aux << " €\t" << total << "\n\n" << endl;

  	total = 0;
  	aux = 0.0;
  }
}


ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& ip)
{
	double total = 0.0;

	for(Pedido_Articulo::ItemsPedido::const_iterator i = ip.begin(); i != ip.end(); i++)
	{
		os << i->second << endl;

		total += (i->second.precio_venta()) * (i->second.cantidad());
	}

	os << "Importe Total: " << total << " €" << endl;

	return os;
}

ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& p)
{
	double total = 0.0;

	for(Pedido_Articulo::Pedidos::const_iterator i = p.begin(); i != p.end(); i++)
	{
        	os << i->second << "\t" << i->first->fecha() << endl;

		total += (i->second.precio_venta()) * (i->second.cantidad());
	}

	os << "Importe Total: " << total << " €" << endl;

	return os;
}

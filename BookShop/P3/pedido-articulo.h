#ifndef PEDIDO_ARTICULO_H_
#define PEDIDO_ARTICULO_H_
#include "fecha.h"
#include "articulo.h"
#include "pedido.h"

class Pedido_Articulo;

class LineaPedido
{
    public:

	explicit LineaPedido(double pv, unsigned int cant = 1):precio_venta_(pv), cantidad_(cant) {}
	double precio_venta() const {return precio_venta_;}
	unsigned int cantidad() const {return cantidad_;}

    private:

	double precio_venta_;
	unsigned int cantidad_;
};

ostream& operator <<(ostream& os, const LineaPedido& lp);


class OrdenaPedidos
{
    public:
        bool operator()(Pedido* p1, Pedido* p2) const;
};

class OrdenaArticulos
{
    public:
        bool operator()(Articulo* a1, Articulo* a2) const;
};


class Pedido_Articulo
{
	public:

		typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
		typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        	typedef map<Pedido*, ItemsPedido, OrdenaPedidos> AD;
        	typedef map<Articulo*,Pedidos, OrdenaArticulos> AI;

		void pedir(Pedido& p, Articulo& a, double prec, unsigned int cant = 1);
		void pedir(Articulo& a, Pedido& p, double prec, unsigned int cant = 1);

		ItemsPedido& detalle(Pedido& p) {return directa[&p];}
		Pedidos& ventas(Articulo& a) {return inversa[&a];}

		void mostrarDetallePedidos(ostream& os) const;
		void mostrarVentasArticulos(ostream& os) const;

	private:

		AD directa;
		AI inversa;
};

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& ip);
ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& p);

#endif

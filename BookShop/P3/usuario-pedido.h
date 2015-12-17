#ifndef USUARIO_PEDIDO_H_
#define USUARIO_PEDIDO_H_
#include "usuario.h"
#include <iostream>
#include <map>
#include <set>

using namespace std;

class Pedido;

class Usuario_Pedido
{
    public:

	typedef set<Pedido*> Pedidos;

    void asocia(Usuario& u, Pedido& p);

    void asocia(Pedido& p, Usuario& u);

    Pedidos& pedidos(Usuario& u) {return Up[&u];}

    Usuario* cliente(Pedido& p) {return Pu[&p];}

    private:

    map<Usuario*, Pedidos> Up;
    map<Pedido*, Usuario*> Pu;
};


inline void Usuario_Pedido::asocia(Usuario& u, Pedido& p)
{
    Up[&u].insert(&p);
    Pu[&p] = &u;
}

inline void Usuario_Pedido::asocia(Pedido& p, Usuario& u)
{
    asocia(u,p);
}

#endif

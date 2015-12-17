#ifndef PEDIDO_H_
#define PEDIDO_H_
#include "fecha.h"
#include "articulo.h"
#include "tarjeta.h"
#include "usuario.h"
#include "usuario-pedido.h"
#include <iostream>

using namespace std;

class Pedido_Articulo;

class Pedido
{
    public:

        class Vacio
        {
            public:
                Vacio(const Usuario& u):usuario_(&u) {}
                const Usuario& usuario() const {return *usuario_;}

            private:
               const Usuario* usuario_;
        };

        class Impostor
        {
            public:
                Impostor(const Usuario& u):usuario_(&u) {}
                const Usuario& usuario() const {return *usuario_;}

            private:
                const Usuario* usuario_;
        };

        class SinStock
        {
            public:
                SinStock(const Articulo& a):articulo_(&a) {}
                const Articulo& articulo() const {return *articulo_;}

            private:
                const Articulo* articulo_;
        };

        Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());

        int numero() const {return numero_;}
        const Tarjeta* tarjeta() const {return tarjeta_;}
        Fecha fecha() const {return fecha_;}
        double total() const {return total_;}
        static int n_total_pedidos() {return N_pedidos;}

    private:

        static int N_pedidos;
        int numero_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
};

ostream& operator <<(ostream& os, const Pedido& p);

#endif

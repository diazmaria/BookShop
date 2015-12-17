#ifndef USUARIO_H_
#define USUARIO_H_
#include "cadena.h"
#include "articulo.h"
#include "tarjeta.h"
#include <iostream>
#include <set>
#include <map>

class Articulo;
class Tarjeta;
class Numero;

using namespace std;


class Clave
{
	public:

		enum Razon {CORTA, ERROR_CRYPT};

		Clave(const char* c);

		Cadena clave() const {return contrasena;}

		bool verifica(const char* c) const;

		class Incorrecta
		{
			public:
				Incorrecta(Razon r):razon_(r) {}
				Razon razon() const {return razon_;}

			private:
				Razon razon_;
		};

	private:

		Cadena contrasena;
};


class Usuario
{
    public:

        typedef map<Numero, Tarjeta*> Tarjetas;
        typedef map<Articulo*, unsigned int> Articulos;

        Usuario(const Cadena& id, const Cadena& nom, const Cadena& ap, const Cadena& dir, const Clave& clav);

        void es_titular_de(Tarjeta& t);
        void no_es_titular_de(Tarjeta& t);

        Cadena id() const {return id_;}
        Cadena nombre() const {return nombre_;}
        Cadena apellidos() const {return apellidos_;}
        Cadena direccion() const {return direccion_;}

        const Tarjetas& tarjetas() const {return tarjetas_;}
        const Articulos& compra() const {return compra_;}

        void compra(Articulo& a, unsigned int cant = 1);

        size_t n_articulos() const {return compra_.size();}

        friend ostream& operator <<(ostream& os, const Usuario& u);

        ~Usuario();

        class Id_duplicado
        {
            public:
                Id_duplicado(const Cadena& c):ide(c) {}
                Cadena idd() const {return ide;}

            private:
                Cadena ide;
        };

    private:

        Cadena id_, nombre_, apellidos_, direccion_;
        Clave clave_;
        Tarjetas tarjetas_;
        Articulos compra_;

        static set<Cadena> IDs;

        Usuario(const Usuario& u);
        Usuario& operator =(const Usuario& u);
}; 

void mostrar_carro(ostream& os, Usuario& u) ;

#endif

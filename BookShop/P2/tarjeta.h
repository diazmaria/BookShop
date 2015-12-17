#ifndef TARJETA_H_
#define TARJETA_H_
#include "fecha.h"
#include "cadena.h"
#include "usuario.h"
#include <iostream>

using namespace std;

class Usuario;


class Numero
{
    public:

        enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

	struct EsDigito
        {
            bool operator()(char c) const {return isdigit(c);}
            typedef char argument_type;
        };

        struct EsBlanco
        {
            bool operator()(char c) const {return isspace(c);}
	    typedef char argument_type;
        };

        class Incorrecto
        {
            public:
                Incorrecto(Razon r):razon_(r) {}
                Razon razon() const {return razon_;}

            private:
                Razon razon_;
        };

        Numero(const Cadena& no);
	
	Numero();

        operator const char*() const {return num_.c_str();};

        friend bool operator <(const Numero& n1, const Numero& n2);

    private:

        Cadena num_;
};



class Tarjeta
{
    public:

        class Caducada
        {
            public:
                Caducada(const Fecha& f):fech(f) {}
                Fecha cuando() const {return fech;}

            private:
                Fecha fech;
        };

        Tarjeta(const Numero& n, Usuario& usu, const Fecha& fech);

        Numero numero() const {return numero_;}
        Fecha caducidad() const {return caducidad_;};
        Cadena titular_facial() const {return titular_facial_;};
        const Usuario* titular() const {return titular_;};

        void anula_titular() {titular_ = 0;};
	
	friend ostream& operator <<(ostream& os, const Tarjeta& t);

        ~Tarjeta();

    private:

        Numero numero_;
        const Usuario* titular_;
        Fecha caducidad_;
        Cadena titular_facial_;

        Tarjeta(const Tarjeta& t);
        Tarjeta& operator =(const Tarjeta& t);
};

bool operator <(const Tarjeta& t1, const Tarjeta& t2);

#endif

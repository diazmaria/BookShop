#include "tarjeta.h"
#include <cctype>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>

bool luhn(const Cadena& numero, size_t n);

Numero::Numero(const Cadena& no)
{
    char* numero = new char[no.length()+1];

    strcpy(numero, no.c_str());

    char* fin = remove_if(numero, numero + no.length(), EsBlanco());

    *fin = '\0';

    int l = strlen(numero);

    if(l < 13 || l > 19)
        throw Incorrecto(LONGITUD);

    if (fin != find_if(numero, fin, not1(EsDigito())))
        throw Incorrecto(DIGITOS);

    num_ = numero;

    if(!luhn(num_, num_.length()))
        throw Incorrecto(NO_VALIDO);
}


bool operator <(const Numero& n1, const Numero& n2)
{
     return (strcmp(n1, n2) < 0);
}


Tarjeta::Tarjeta(const Numero& n, Usuario& usu, const Fecha& fech) : numero_(n), titular_(&usu), caducidad_(fech)
{
    if (fech < Fecha())
        throw Caducada(fech);

    caducidad_ = fech;

    Cadena cad = usu.nombre()+ " " + usu.apellidos();

    for(unsigned int i = 0; i < cad.length(); i++)
        cad[i] = toupper(cad[i]);

    titular_facial_ = cad.c_str();

    usu.es_titular_de(*this);
}


Tarjeta::~Tarjeta()
{
    if (titular_ != 0)
    {
        Usuario* u = const_cast<Usuario*>(titular_);

        u->no_es_titular_de(*this);
    }
}


ostream& operator <<(ostream& os, const Tarjeta& t)
{
    os << " " << t.numero() << endl << " " << t.titular_facial() << endl << " "
    << "Caduca: "<< setfill('0') << setw(2) << t.caducidad().mes() << "/" << setw(2) << (t.caducidad().anno() % 100) << endl;

    return os;
}


bool operator <(const Tarjeta& t1, const Tarjeta& t2)
{
    return t1.numero() < t2.numero();
}

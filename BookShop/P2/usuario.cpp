#include "usuario.h"
#include <iomanip>
#include <unistd.h>
#include <cstring>

using namespace std;


Clave::Clave(const char* c)
{
    if (strlen(c) < 5)
        throw Incorrecta(CORTA);

    const char saltkey[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    const char salt[2] = {saltkey[rand()%64], saltkey[rand()%64]};

    if(!crypt(c, salt))
        throw Incorrecta(ERROR_CRYPT);

    else
        contrasena = crypt(c, salt);
}


bool Clave::verifica(const char* c) const
{
    const char* clave = contrasena.c_str();

    return !strcmp(crypt(c, clave), clave);
}


set<Cadena> Usuario::IDs;


Usuario::Usuario(const Cadena& id, const Cadena& nom, const Cadena& ap, const Cadena& dir, const Clave& clav):
id_(id), nombre_(nom), apellidos_(ap), direccion_(dir), clave_(clav)
{
    pair<set<Cadena>::iterator, bool> aux = IDs.insert(id);

    if(!aux.second)
        throw Id_duplicado(id_);
}


void Usuario::es_titular_de(Tarjeta& t)
{
    if(t.titular() == this)
        tarjetas_[t.numero()] = &t;
}


void Usuario::no_es_titular_de(Tarjeta& t)
{
    tarjetas_.erase(t.numero());
}


void Usuario::compra(Articulo& a, unsigned int cant)
{
    if(cant == 0)
        compra_.erase(&a);

    else
        compra_[&a] = cant;
}


ostream& operator <<(ostream& os, const Usuario& u)
{
    os << u.id_ << " [" << u.clave_.clave() << "] " << u.nombre_ << " " << u.apellidos_ << endl << u.direccion_ << endl << "Tarjetas: "
    << endl << endl;

	for (Usuario::Tarjetas::const_iterator i = u.tarjetas_.begin(); i != u.tarjetas_.end(); i++)
        os << *i->second << endl;

	return os;
}


Usuario::~Usuario()
{
    for(Tarjetas::iterator i = tarjetas_.begin(); i != tarjetas_.end(); i++)
        i->second->anula_titular();

    IDs.erase(id_);
}


void mostrar_carro(ostream& os, Usuario& u)
{
    os << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]"<< endl << " Cant." << '\t'
    << "Artículo" << endl << setfill('=') << setw(66) << "" << endl;

    for (Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); i++)
        os << "   " << i->second << '\t' << *i->first << endl << endl;
}

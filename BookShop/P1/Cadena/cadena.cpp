#include <cstring>
#include <stdexcept>
#include "cadena.h"

Cadena::Cadena(unsigned int t, char c):tam(t), cad(new char[t+1])
{
    unsigned int i;

    for (i=0; i<tam; i++)

        cad[i] = c;

    cad[i] = '\0';
}


Cadena::Cadena(Cadena&& c)
{
    cad = c.cad;
    tam = c.tam;

    c.cad = new char[1];
    c.cad[0] = '\0';
    c.tam = 0;
}


Cadena& Cadena::operator =(Cadena&& c)
{
    delete[] cad;

    cad = c.cad;
    tam = c.tam;

    c.cad = new char[1];
    c.cad[0] = '\0';
    c.tam = 0;

    return *this;
}


Cadena::Cadena(const Cadena& c):tam(c.tam), cad(new char[tam+1])
{
    strcpy(cad, c.cad);
}


Cadena::Cadena(const char* c):tam(strlen(c)), cad(new char[tam+1])
{
    strcpy(cad, c);
}


Cadena& Cadena::operator =(const Cadena& c)
{
    if(this != &c)
    {
        if(tam != c.tam)
        {
            this -> ~Cadena();
            tam = c.tam;
            cad = new char[tam+1];
        }

        strcpy(cad, c.cad);
    }

    return *this;
}


Cadena& Cadena::operator =(const char* c)
{
    if (tam != strlen(c))
    {
        this -> ~Cadena();

        tam = strlen(c);

        cad = new char [tam+1];
    }

    strcpy(cad, c);

    return *this;
}


Cadena Cadena::substr(int i, int t) const
{
    if(i<0 || t<0 || i+t>=(int)tam)
    {
        throw out_of_range("Límites inválidos");
    }

    char *cadena = new char[t+1];

    for(int aux=0; aux<t; aux++)
    {
        cadena[aux]=cad[i];
        i++;
    }

    cadena[t]='\0';

    Cadena aux2(cadena);

    delete[] cadena;

    return aux2;
}


Cadena& Cadena::operator +=(const Cadena& c)
{
    Cadena aux(*this);

    tam = tam + c.tam;

    delete[] cad;

    cad = new char[tam+1];

    strcpy(cad, aux.cad);
    strcat(cad, c.cad);

    return *this;
}


char& Cadena::at(unsigned int i)
{
    if (i>=0 && i<tam)
        return cad[i];
    else
        throw out_of_range("Posición inválida");
}


char Cadena::at(unsigned int i) const
{

    if (i>=0 && i<tam)
        return cad[i];
    else
        throw out_of_range("Posición inválida");
}


Cadena::~Cadena()
{
    delete[] cad;

    cad = 0;
}


Cadena operator +(const Cadena& c1, const Cadena& c2)
{
    Cadena c3(c1);

    c3+=c2;
   
    return c3;
}

bool operator ==(const Cadena& c1, const Cadena& c2)
{
    return (strcmp(c1.c_str(), c2.c_str()) == 0 && c1.length() == c2.length());
}


bool operator !=(const Cadena& c1, const Cadena& c2)
{
    return !(c1 == c2);
}


bool operator >(const Cadena& c1, const Cadena& c2)
{
    return (strcmp(c1.c_str(), c2.c_str()) > 0);
}


bool operator <(const Cadena& c1, const Cadena& c2)
{
    return (strcmp(c1.c_str(), c2.c_str()) < 0);
}


bool operator >=(const Cadena& c1, const Cadena& c2)
{
    return !(c1 < c2);
}


bool operator <=(const Cadena& c1, const Cadena& c2)
{
    return !(c2 < c1);
}


ostream& operator <<(ostream& os, const Cadena& c)
{
    os << c.cad;

    return os;
}


istream& operator >>(istream& is, Cadena& c)
{
    strcpy(c.cad, "");

    c.tam = 0;

    while (is.peek() == ' ')
        is.get();

    is >> c.cad;

    c.tam = strlen(c.cad);

    return is;
}


Cadena::iterator Cadena::begin() noexcept
{
    return cad;
}


Cadena::iterator Cadena::end() noexcept
{
    return cad+tam;
}


Cadena::const_iterator Cadena::begin() const noexcept
{
    return cad;
}


Cadena::const_iterator Cadena::end() const noexcept
{

    return cad+tam;
}


Cadena::const_iterator Cadena::cbegin() const noexcept
{
    return cad;
}


Cadena::const_iterator Cadena::cend() const noexcept
{
    return cad+tam;
}


Cadena::reverse_iterator Cadena::rbegin() noexcept
{
    return reverse_iterator(end());
}


Cadena::reverse_iterator Cadena::rend() noexcept
{
    return reverse_iterator(begin());
}


Cadena::const_reverse_iterator Cadena::rbegin() const noexcept
{
    return const_reverse_iterator(end());
}


Cadena::const_reverse_iterator Cadena::rend() const noexcept
{
    return const_reverse_iterator(begin());
}


Cadena::const_reverse_iterator Cadena::crbegin() const noexcept
{
    return const_reverse_iterator(end());
}


Cadena::const_reverse_iterator Cadena::crend() const noexcept
{
    return const_reverse_iterator(begin());
}

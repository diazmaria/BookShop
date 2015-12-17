#include <cstdio>
#include <iostream>
#include <ctime>
#include "fecha.h"

const int Fecha::AnnoMinimo(1903);
const int Fecha::AnnoMaximo(2037);


Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    std::time_t tiempo_calendario = std::time(0);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if(dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;

    if(mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon + 1;

    if(anno_ == 0)
        anno_ = tiempo_descompuesto->tm_year + 1900;

    if(!fechaValida())
    {
        throw Invalida("Fecha incorrecta");
    }
}


Fecha::Fecha(const char* cad)
{
    if (sscanf(cad, "%2d/%2d/%4d", &dia_, &mes_, &anno_)<3) throw Invalida("Fecha incorrecta");

    std::time_t tiempo_calendario = std::time(0);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);

    if(dia_ == 0)
        dia_ = tiempo_descompuesto->tm_mday;

    if(mes_ == 0)
        mes_ = tiempo_descompuesto->tm_mon + 1;

    if(anno_ == 0)
        anno_ = tiempo_descompuesto->tm_year + 1900;

    if(!fechaValida())
    {
        throw Invalida("Fecha incorrecta");
    }
}


const char* Fecha::cadena() const
{
    std::tm tiempo_desc = {0, 0, 0, dia_, mes_-1, anno_-1900, 0, 0, 0};

    std::mktime(&tiempo_desc);

    static char cadena[36];

    const char* dias[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};

    const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre",
                          "octubre", "noviembre", "diciembre"};

    sprintf(cadena, "%s %i de %s de %i", dias[tiempo_desc.tm_wday], tiempo_desc.tm_mday, meses[tiempo_desc.tm_mon], (tiempo_desc.tm_year+1900));

    return cadena;
}


Fecha& Fecha::operator+=(int d)
{
    dia_+=d;

    std::tm tiempo_descompuesto = {0, 0, 0, dia_, mes_-1, anno_-1900, 0, 0, 0};
    std::mktime(&tiempo_descompuesto);

    dia_ = tiempo_descompuesto.tm_mday;
    mes_ = tiempo_descompuesto.tm_mon + 1;
    anno_ = tiempo_descompuesto.tm_year + 1900;

    if(!fechaValida())
    {
        throw Invalida("Fecha incorrecta");
    }

    return *this;
}


Fecha& Fecha::operator-=(int d)
{
    *this+=(-d);

    return *this;
}


Fecha& Fecha::operator++()
{
    *this+=1;

    return *this;
}


Fecha& Fecha::operator--()
{
    *this+=(-1);

    return *this;
}


Fecha Fecha::operator ++(int)
{
    Fecha result(*this);

    *this+=1;

    return result;
}


Fecha Fecha::operator --(int)
{
    Fecha result(*this);

    *this+=(-1);

    return result;
}


Fecha Fecha::operator +(int d) const
{
    Fecha result(*this);

    result+=d;

    return result;
}


Fecha Fecha::operator -(int d) const
{
    Fecha result(*this);

    result+=(-d);

    return result;
}


bool Fecha::fechaValida()
{
    if (anno_ >= AnnoMinimo && anno_ <= AnnoMaximo)
    {
        if (mes_ >= 1 && mes_ <= 12)
        {
            if (dia_ > 0 && dia_ < 29)
                return true;

            else if (dia_ == 29)
            {
                if (mes_ == 2 && !(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)))
                    return false;

                else
                    return true;
            }

            else if (dia_ == 31)
            {
                if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
                    return true;

                else
                    return false;
            }

            else if (dia_ == 30)
            {
                if (mes_ == 2)
                    return false;

                else
                    return true;
            }

            else return false;
        }

        else return false;
    }
    else return false;
}



bool operator ==(const Fecha& f1, const Fecha& f2)
{
    return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}


bool operator !=(const Fecha& f1, const Fecha& f2)
{
      return !(f1 == f2);
}


bool operator <(const Fecha& f1, const Fecha& f2)
{
    if (f1.anno() < f2.anno())
        return true;

    else if (f1.anno() == f2.anno())
    {
        if(f1.mes() < f2.mes())
            return true;

        else if(f1.mes() == f2.mes())
        {
            if (f1.dia() < f2.dia())
                return true;
            else
                return false;
        }

         else
            return false;
    }

    else
        return false;
}


bool operator <=(const Fecha& f1, const Fecha& f2)
{
    return !(f2<f1);
}


bool operator >(const Fecha& f1, const Fecha& f2)
{
    return f2<f1;
}


bool operator >=(const Fecha& f1, const Fecha& f2)
{
    return !(f1<f2);
}


ostream& operator <<(ostream& os, const Fecha& f)
{
	os<<f.cadena();
	return os;
}


istream& operator >> (istream& is, Fecha& f)
{
	char* c = new char[11];

	is.width(11);

	is >> c;

	is.ignore();

	f = c;

	return is;
}

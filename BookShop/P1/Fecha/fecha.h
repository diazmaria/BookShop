#ifndef FECHA_H_
#define FECHA_H_
#include <iostream>

using namespace std;

class Fecha
{
    public:

        static const int AnnoMinimo, AnnoMaximo;

        explicit Fecha(int d=0, int m=0, int a=0);
        Fecha(const char* cad);

        const char* cadena() const;

        int dia() const;
        int mes() const;
        int anno() const;

        Fecha& operator +=(int d);
        Fecha& operator -=(int d);
        Fecha& operator ++();
        Fecha operator ++(int);
        Fecha& operator --();
        Fecha operator --(int);
        Fecha operator +(int d) const;
        Fecha operator -(int d) const;

        class Invalida
        {
            public:
                Invalida(const char* cad):error(cad) {}
                const char* por_que() const;

            private:
                const char* error;
        };

        friend ostream& operator << (ostream& os, const Fecha& f);
        friend istream& operator >> (istream& is, Fecha& f);

    private:

        int dia_, mes_, anno_;
        bool fechaValida();
};

inline int Fecha::dia() const {return dia_;}
inline int Fecha::mes() const {return mes_;}
inline int Fecha::anno() const {return anno_;}
inline const char* Fecha::Invalida::por_que() const {return error;}

bool operator ==(const Fecha& f1, const Fecha& f2);
bool operator !=(const Fecha& f1, const Fecha& f2);
bool operator <(const Fecha& f1, const Fecha& f2);
bool operator <=(const Fecha& f1, const Fecha& f2);
bool operator >(const Fecha& f1, const Fecha& f2);
bool operator >=(const Fecha& f1, const Fecha& f2);

#endif

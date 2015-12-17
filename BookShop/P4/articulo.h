#ifndef ARTICULO_H_
#define ARTICULO_H_
#include "fecha.h"
#include "cadena.h"
#include "autor.h"
#include <set>

using namespace std;

class Autor;

class Articulo{

    public:

        typedef set<Autor*> Autores;

        class Autores_vacios{};

       Articulo(const Autores& a, const Cadena& cr, const Cadena& tit, const Fecha& fp, double prec);

        Cadena referencia() const {return referencia_;}
        Cadena titulo() const {return titulo_;}
        Fecha f_publi() const {return f_publi_;}
        double precio() const {return precio_;}
        double& precio() {return precio_;}
        const Autores& autores() const {return autores_;}

        virtual void imp_esp(ostream& os) const = 0;

        virtual ~Articulo() {}

    private:

        Autores autores_;
        Cadena referencia_, titulo_;
        Fecha f_publi_;
        double precio_;
};

ostream& operator <<(ostream& os, const Articulo& a);

void imp_prologo(ostream& os, const Articulo& a);
void imp_epilogo(ostream& os, const Articulo& a);
void imp_autores(ostream& os, const Articulo& a);

class ArticuloAlmacenable : public Articulo
{
    public:

    ArticuloAlmacenable(const Autores& a, const Cadena& r, const Cadena& t, const Fecha& f, double p, unsigned int s) : Articulo(a, r, t, f, p), stock_(s) {}

        unsigned int stock() const {return stock_;}
        unsigned int& stock() {return stock_;}

    protected:

        unsigned int stock_;
};


class Libro : public ArticuloAlmacenable
{
    public:

       Libro(const Autores& aut, const Cadena& refe, const Cadena& titu, const Fecha& f_pub, double prec, unsigned int npag, unsigned int sto) : ArticuloAlmacenable(aut, refe, titu, f_pub, prec, sto), n_pag_(npag) {}

        unsigned int n_pag() const {return n_pag_;}

        void imp_esp(ostream& os) const;

    private:

        unsigned int n_pag_;
};


class Cederron : public ArticuloAlmacenable
{
    public:

        Cederron(const Autores& aut, const Cadena& refe, const Cadena& titu, const Fecha& f_pub, double prec, unsigned int tama, unsigned int sto) : ArticuloAlmacenable(aut, refe, titu, f_pub, prec, sto), tam_(tama) {}


        unsigned int tam() const {return tam_;}

        void imp_esp(ostream& os) const;

    private:

         unsigned int tam_;
};


class LibroDigital : public Articulo
{
    public:

       LibroDigital(const Autores& aut, const Cadena& refe, const Cadena& titu, const Fecha& f_pub, double prec, Fecha fexp) : Articulo(aut, refe, titu, f_pub, prec), f_expir_(fexp) {}


        Fecha f_expir() const {return f_expir_;}

        void imp_esp(ostream& os) const;

    private:

        Fecha f_expir_;
};


#endif

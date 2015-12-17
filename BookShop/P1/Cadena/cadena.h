#ifndef CADENA_H_
#define CADENA_H_
#include <iostream>
#include <iterator>

using namespace std;

class Cadena
{
    public:

        explicit Cadena(unsigned int t=0, char c=' ');

        Cadena(Cadena&& c);
        Cadena& operator =(Cadena&& c);

        Cadena(const Cadena& c);
        Cadena(const char* c);

        Cadena& operator =(const Cadena& c);
        Cadena& operator =(const char* c);

        const char* c_str() const;
        unsigned int length() const;

        Cadena substr(int i, int t) const;

        Cadena& operator +=(const Cadena& c);

        char& operator [](unsigned int i);
        char operator [](unsigned int i) const;

        char& at(unsigned int i);
        char at(unsigned int i) const;

        ~Cadena();

        friend ostream & operator << (ostream& os, const Cadena& c);
        friend istream & operator >> (istream& is,  Cadena& c);

        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        iterator begin() noexcept;
        iterator end() noexcept;

        const_iterator begin() const noexcept;
        const_iterator end() const noexcept;

        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;

        reverse_iterator rbegin() noexcept;
        reverse_iterator rend() noexcept;

        const_reverse_iterator rbegin() const noexcept;
        const_reverse_iterator rend() const noexcept;

        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

    private:

        unsigned int tam;
        char* cad;
};

inline const char* Cadena::c_str() const {return cad;}
inline unsigned int Cadena::length() const {return tam;}

inline char& Cadena::operator [](unsigned int i) {return cad[i];}
inline char Cadena::operator [](unsigned int i) const {return cad[i];}

Cadena operator +(const Cadena& c1, const Cadena& c2);
bool operator ==(const Cadena& c1, const Cadena& c2);
bool operator !=(const Cadena& c1, const Cadena& c2);
bool operator >(const Cadena& c1, const Cadena& c2);
bool operator <(const Cadena& c1, const Cadena& c2);
bool operator >=(const Cadena& c1, const Cadena& c2);
bool operator <=(const Cadena& c1, const Cadena& c2);

#endif

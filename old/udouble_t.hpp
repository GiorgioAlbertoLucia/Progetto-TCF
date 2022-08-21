#ifndef UDOUBLE_H
#define UDOUBLE_H

#include <iostream>
#include <math.h>

#include "../include_t/partder_t.hpp"

template <class T> 
class Udouble
{
    friend  std::ostream&   operator<<(std::ostream&, const Udouble<T>&);
    
    friend  Udouble<T>         tan(const Udouble<T>&);
    friend  Udouble<T>         sinh(const Udouble<T>&);
    friend  Udouble<T>         cosh(const Udouble<T>&);
    friend  Udouble<T>         tanh(const Udouble<T>&);
    friend  Udouble<T>         asin(const Udouble<T>&);
    friend  Udouble<T>         acos(const Udouble<T>&);
    friend  Udouble<T>         atan(const Udouble<T>&);
    friend  Udouble<T>         asinh(const Udouble<T>&);
    friend  Udouble<T>         acosh(const Udouble<T>&);
    friend  Udouble<T>         atanh(const Udouble<T>&);
    friend  Udouble<T>         exp(const Udouble<T>&);
    friend  Udouble<T>         pow(const Udouble<T>&, const double);
    friend  Udouble<T>         pow(const Udouble<T>&, const int);
    friend  Udouble<T>         pow(const Udouble<T>&, const Udouble<T>&);
    friend  Udouble<T>         log(const Udouble<T>&);
    friend  Udouble<T>         log10(const Udouble<T>&);

public:
                                                Udouble();
                                                Udouble(const T&, const T&);
                                                Udouble(const PartDer<T>&, const T&);
                                                Udouble(const Udouble<T>&);
                                                ~Udouble(){};

                Udouble<T>&                     set_value(const T&);
                Udouble<T>&                     set_value(const PartDer<T>& value)                      {Udouble::value = value; return *this;};
                Udouble<T>&                     set_error(const T& error)                               {Udouble::error = error; return *this;};
                Udouble<T>&                     insert_errors(const std::string var, const T& err)      {Udouble::errors.insert(std::make_pair(var, err)); return *this;};
                Udouble<T>&                     autoset_label();

        const   T&                              get_value()     const                                   {return Udouble::value.get_f();};
        const   PartDer<T>                      get_partder()   const                                   {return Udouble::value;};
        const   T&                              get_error()     const                                   {return Udouble::error;};
        const   std::map<std::string, T&>       get_errorsmap() const                                   {return Udouble::errors;};  
        const   std::string                     get_label()     const                                   {return Udouble::label;};
        static  int                             get_count()                                             {return count;};

                Udouble<T>                      operator+(const Udouble<T>&);
                Udouble<T>                      operator-(const Udouble<T>&);
                Udouble<T>                      operator*(const Udouble<T>&); 
                Udouble<T>                      operator/(const Udouble<T>&);
                Udouble<T>                      operator^(const int n)                                  {return pow(*this, n);};
                Udouble<T>                      operator^(const double n)                               {return pow(*this, n);};
                Udouble<T>                      operator^(const Udouble<T>& n)                          {return pow(*this, n);};

                Udouble<T>&                     operator=(const Udouble<T>&) noexcept; 

        friend  Udouble<T>                      sin(const Udouble<T>&);
        friend  Udouble<T>                      cos(const Udouble<T>&);

        friend  Udouble<T>                      operator*(const double, const Udouble<T>&);                                 // multiply by a scalar
        friend  Udouble<T>                      operator/(const double, const Udouble<T>&);
        friend  Udouble<T>                      operator/(const Udouble<T>&, const double);

                bool                            operator==(const Udouble<T>&);
                bool                            operator!=(const Udouble<T>& other)                     {return !(*this == other);};

private:
        static int count;                       // how many Udouble are created (delete does not reset nor reduce count)

        PartDer<T> value;
        T error;
        std::map<std::string, T> errors;        // errors associated with variables in PartDer map

        std::string label;
};

#endif
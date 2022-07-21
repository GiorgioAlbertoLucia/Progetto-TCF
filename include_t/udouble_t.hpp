#ifndef UDOUBLE_H
#define UDOUBLE_H

#include <iostream>
#include <math.h>

#include "../include_t/partder_t.hpp"
 
template <class T>
class Udouble
{
    friend  std::ostream&   operator<<(std::ostream&, const Udouble&);
    
    friend  Udouble         tan(const Udouble&);
    friend  Udouble         sinh(const Udouble&);
    friend  Udouble         cosh(const Udouble&);
    friend  Udouble         tanh(const Udouble&);
    friend  Udouble         asin(const Udouble&);
    friend  Udouble         acos(const Udouble&);
    friend  Udouble         atan(const Udouble&);
    friend  Udouble         asinh(const Udouble&);
    friend  Udouble         acosh(const Udouble&);
    friend  Udouble         atanh(const Udouble&);
    friend  Udouble         exp(const Udouble&);
    friend  Udouble         pow(const Udouble&, const double);
    friend  Udouble         pow(const Udouble&, const int);
    friend  Udouble         pow(const Udouble&, const Udouble&);
    friend  Udouble         log(const Udouble&);
    friend  Udouble         log10(const Udouble&);

public:
                                                Udouble();
                                                Udouble(const PartDer<T>&, const T, const bool = false);
                                                Udouble(const Udouble&);
                                                ~Udouble(){};

                Udouble&                        set_value(const PartDer& value)                         {Udouble::value = value; return *this;};
                Udouble&                        set_error(const T error)                                {Udouble::error = error; return *this;};
                Udouble&                        insert_errors(const std::string var, const T err)       {Udouble::errors.insert(std::make_pair(var, err)); return *this;};
                Udouble&                        set_format(const bool format)                           {Udouble::format = format; return *this;};
                Udouble&                        autoset_label();

        const   T                               get_value()     const                                   {return Udouble::value.get_f();};
        const   PartDer                         get_partder()   const                                   {return Udouble::value;};
        const   T                               get_error()     const                                   {return Udouble::error;};
        const   std::map<std::string, T>        get_errorsmap() const                                   {return Udouble::errors;};  
        const   std::string                     get_label()     const                                   {return Udouble::label;};
        const   bool                            get_format()    const                                   {return Udouble::format;};
        static  int                             get_count()                                             {return count;};

                Udouble                         operator+(const Udouble&);
                Udouble                         operator-(const Udouble&);
                Udouble                         operator*(const Udouble&); 
                Udouble                         operator/(const Udouble&);
                Udouble                         operator^(const int n)                                  {return pow(*this, n);};
                Udouble                         operator^(const double n)                               {return pow(*this, n);};
                Udouble                         operator^(const Udouble& n)                             {return pow(*this, n);};

                Udouble&                        operator=(const Udouble&) noexcept; 

        friend  Udouble                         sin(const Udouble&);
        friend  Udouble                         cos(const Udouble&);

        friend  Udouble                         operator*(const double, const Udouble&);                                 // multiply by a scalar
        friend  Udouble                         operator/(const double, const Udouble&);
        friend  Udouble                         operator/(const Udouble&, const double);

                bool                            operator==(const Udouble&);
                bool                            operator!=(const Udouble& other)                        {return !(*this == other);};

private:
    static int count;                               // how many Udouble are created (delete does not reset nor reduce count)

            PartDer<T> value;
            T error;
            std::map<std::string, T> errors;        // errors associated with variables in PartDer map

            std::string label;
            bool format;
};

#endif
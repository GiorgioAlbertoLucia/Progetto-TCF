#ifndef UDOUBLE_H
#define UDOUBLE_H

#include <iostream>
#include <math.h>

#include "../include/partder.hpp"
 
class Udouble: public PartDer
{
    friend  std::ostream&   operator<<(std::ostream&, const Udouble&);
    friend  Udouble         sin(const Udouble&);
    friend  Udouble         cos(const Udouble&);
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
                            Udouble(){count++;};
                            Udouble(const double, const std::map<std::string, double>, const double, const char * = 0, const bool = 0);
                            Udouble(const Udouble&);
                            ~Udouble();

            void            set_value(const PartDer& value)                             {Udouble::value = value;};
            void            set_error(const double error)                               {Udouble::error = error;};
            void            insert_errors(const std::string var, const double err)      {Udouble::errors.insert(std::make_pair(var, err));};
            void            set_format(const bool format)                               {Udouble::format = format;};

            double          get_value()     const                                       {return Udouble::value.get_f();};
            PartDer         get_partder()   const                                       {return Udouble::value;};
            double          get_error()     const                                       {return Udouble::error;};
            std::string     get_label()     const                                       {return Udouble::label;};
            double          get_format()    const                                       {return Udouble::format;};

            Udouble&        operator+(const Udouble&);
            Udouble&        operator-(const Udouble&);
            Udouble&        operator*(const double);                                 // multiply by a scalar
            Udouble&        operator*(const int);
            Udouble&        operator*(const Udouble&); 
            Udouble&        operator/(const double);
            Udouble&        operator/(const int);
            Udouble&        operator/(const Udouble&);
            Udouble&        operator=(const Udouble&); 
            bool            operator==(const Udouble&);
            bool            operator!=(const Udouble& itself)    {return !(*this == itself);};

private:
            static int count;

            PartDer value;
            double error;
            std::map<std::string, double> errors;   // errors associated with variables in PartDer map

            std::string label;
            bool format;
};

#endif
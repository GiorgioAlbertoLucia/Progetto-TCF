#ifndef UDOUBLE_H
#define UDOUBLE_H

#include <iostream>
#include <math.h>
 
class Udouble
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
                            Udouble(){};
                            Udouble(const double, const double, const bool=0);
                            Udouble(const Udouble&);
                            ~Udouble();

            void            set_value(const double value)   {Udouble::value = value;};
            void            set_error(const double error)   {Udouble::error = error;};
            void            set_format(const bool format)   {Udouble::format = format;};

            double          get_value()     const           {return Udouble::value;};
            double          get_error()     const           {return Udouble::error;};
            double          get_format()    const           {return Udouble::format;};

            Udouble&        operator+(const Udouble&);
            Udouble&        operator-(const Udouble&);
            Udouble&        operator*(const double);                                 // multiply by a scalar
            Udouble&        operator*(const int);
            Udouble&        operator*(const Udouble&); 
            Udouble&        operator/(const double);
            Udouble&        operator/(const int);
            Udouble&        operator/(const Udouble&);
            Udouble&        operator=(const double[2]); 
            bool            operator==(const Udouble&);
            bool            operator!=(const Udouble& itself)    {return !(*this == itself);};

private:
            double value;
            double error;
            bool format;
};

#endif
#ifndef UDOUBLE_H
#define UDOUBLE_H

#include <iostream>
#include <math.h>

class Udouble
{
    friend  std::ostream&   operator<<(std::ostream&, const Udouble&);
    friend  Udouble&        sin(Udouble&);
    friend  Udouble&        cos(Udouble&);
    friend  Udouble&        tan(Udouble&);
    friend  Udouble&        sinh(Udouble&);
    friend  Udouble&        cosh(Udouble&);
    friend  Udouble&        tanh(Udouble&);
    friend  Udouble&        asin(Udouble&);
    friend  Udouble&        acos(Udouble&);
    friend  Udouble&        atan(Udouble&);
    friend  Udouble&        asinh(Udouble&);
    friend  Udouble&        acosh(Udouble&);
    friend  Udouble&        atanh(Udouble&);
    friend  Udouble&        exp(Udouble&);
    friend  Udouble&        pow(Udouble&, const double);
    friend  Udouble&        pow(Udouble&, const int);
    friend  Udouble&        pow(Udouble&, const Udouble&);
    friend  Udouble&        log(Udouble&);
    friend  Udouble&        log10(Udouble&);

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
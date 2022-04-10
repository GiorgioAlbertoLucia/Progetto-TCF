#include <iostream>
#include <math.h>

#include "../include/udouble.h"

std::ostream&    operator<<(std::ostream& out, const Udouble& udouble)
{
    if(udouble.get_format()){;}
    else                            return out << udouble.get_value() << " +/- " << udouble.get_error();
}

Udouble&         sin(Udouble&  udouble)
{
    double error = udouble.get_error() * cos(udouble.get_value());
    udouble.set_value(sin(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         cos(Udouble& udouble)
{
    double error = udouble.get_error() * sin(udouble.get_value());
    udouble.set_value(cos(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         tan(Udouble& udouble)
{
    double error = udouble.get_error() / pow(cos(udouble.get_value()), 2);
    udouble.set_value(tan(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         sinh(Udouble& udouble)
{
    double error = udouble.get_error() * cosh(udouble.get_value());
    udouble.set_value(sinh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         cosh(Udouble& udouble)
{
    double error = udouble.get_error() * sinh(udouble.get_value());
    udouble.set_value(cosh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         tanh(Udouble& udouble)
{
    double error = udouble.get_error() / pow(cosh(udouble.get_value()), 2);
    udouble.set_value(tanh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         asin(Udouble& udouble)
{
    double error = udouble.get_error() / sqrt(1 - udouble.get_value()*udouble.get_value());
    udouble.set_value(asin(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         acos(Udouble& udouble)
{
    double error = udouble.get_error() / sqrt(1 - udouble.get_value()*udouble.get_value());
    udouble.set_value(acos(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         atan(Udouble& udouble)
{
    double error = udouble.get_error() / sqrt(1 + udouble.get_value()*udouble.get_value());
    udouble.set_value(atan(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         asinh(Udouble& udouble)
{
    double error = udouble.get_error() / sqrt(1 + udouble.get_value()*udouble.get_value());
    udouble.set_value(asinh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         acosh(Udouble& udouble)
{
    double error = udouble.get_error() / (sqrt(1 - udouble.get_value())*sqrt(1 + udouble.get_value()));
    udouble.set_value(acosh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         atanh(Udouble& udouble)
{
    double error = udouble.get_error() / (1 - udouble.get_value()*udouble.get_value());
    udouble.set_value(atanh(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         exp(Udouble& udouble)
{
    double error = udouble.get_error() * exp(udouble.get_value());
    udouble.set_value(exp(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         pow(Udouble& udouble, const double n)
{
    double error = udouble.get_error() * n * pow(udouble.get_value(), n-1);
    udouble.set_value(pow(udouble.get_value(), n));
    udouble.set_error(error);
    return udouble;
}
Udouble&         pow(Udouble& udouble, const int n)
{
    double error = udouble.get_error() * n * pow(udouble.get_value(), n-1);
    udouble.set_value(pow(udouble.get_value(), n));
    udouble.set_error(error);
    return udouble;
}
Udouble&         pow(Udouble& udouble, const Udouble& n)
{
    double error = sqrt(pow(udouble.get_error() * n.get_value() * pow(udouble.get_value(), n.get_value()-1), 2)
                    + pow(n.get_error() * pow(udouble.get_value(), n.get_value()) * log(udouble.get_value()), 2));
    udouble.set_value(pow(udouble.get_value(), n.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         log(Udouble& udouble)
{
    double error = udouble.get_error() / udouble.get_value();
    udouble.set_value(log(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}
Udouble&         log10(Udouble& udouble)
{
    double error = udouble.get_error() / (udouble.get_value()*log(10));
    udouble.set_value(log10(udouble.get_value()));
    udouble.set_error(error);
    return udouble;
}

Udouble::Udouble(const double value, const double error, const bool format)
{
    Udouble::set_value(value);
    Udouble::set_error(error);
    Udouble::set_format(format);
}
/**
 * @brief Copy Constructor.
 * Construct a new Udouble:: Udouble object 
 * @param udouble 
 */
Udouble::Udouble(const Udouble& udouble)
{
    Udouble::value = udouble.get_value();
    Udouble::error = udouble.get_error();
    Udouble::format = udouble.get_format();
}
/**
 * @brief Destroy the Udouble:: Udouble object
 * 
 */
Udouble::~Udouble()
{

}

Udouble&    Udouble::operator+(const Udouble& udouble)
{
    Udouble::value += udouble.get_value();
    Udouble::error = sqrt(pow(Udouble::error, 2) + pow(udouble.get_error(), 2));
    return *this;
}
Udouble&    Udouble::operator-(const Udouble& udouble)
{
    Udouble::value -= udouble.get_value();
    Udouble::error = sqrt(pow(Udouble::error, 2) + pow(udouble.get_error(), 2));
    return *this;
}
Udouble&    Udouble::operator*(const double scalar)                                 // multiply by a scalar
{
    Udouble::value *= scalar;
    Udouble::error *= scalar;
    return *this;
}
Udouble&    Udouble::operator*(const int scalar)
{
    Udouble::value *= scalar;
    Udouble::error *= scalar;
    return *this;
}
Udouble&    Udouble::operator*(const Udouble& udouble)
{
    Udouble::value *= udouble.get_value();
    Udouble::error = sqrt(pow(Udouble::error * udouble.get_value(), 2) + pow(Udouble::value * udouble.get_error(), 2));
    return *this;
} 
Udouble&    Udouble::operator/(const double scalar)
{
    Udouble::value /= scalar;
    Udouble::error /= scalar;
    return *this;
}
Udouble&    Udouble::operator/(const int scalar)
{
    Udouble::value /= scalar;
    Udouble::error /= scalar;
    return *this;
}
Udouble&    Udouble::operator/(const Udouble& udouble)
{
    Udouble::value /= udouble.get_value();
    Udouble::error = sqrt(pow(Udouble::error / udouble.get_value(), 2) + pow(Udouble::value * udouble.get_error() / (udouble.get_value()*udouble.get_value()), 2));
    return *this;
}
Udouble&    Udouble::operator=(const double array[2])
{
    Udouble::value = array[0];
    Udouble::error = array[1];
    return *this;
} 
bool        Udouble::operator==(const Udouble& udouble)
{
    if(Udouble::value == udouble.get_value() && Udouble::error == udouble.get_error())  return true;
    else                                                                                return false;
}

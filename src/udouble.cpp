#include <iostream>
#include <math.h>

#include "../include/udouble.hpp"

std::ostream&    operator<<(std::ostream& out, const Udouble& udouble)
{
    if(udouble.get_format()){return out;}
    else                            return out << udouble.get_value() << " +/- " << udouble.get_error();
}

Udouble         sin(const Udouble& udouble)
{
    Udouble result;
    /*
    std::cout << "check: value = " << udouble.get_value() << ", error = " << udouble.get_error() << std::endl;
    std::cout << "check: sin(value) = " << sin(udouble.get_value()) << ", error_p = " << udouble.get_error() * cos(udouble.get_value()) << std::endl;
    */
    result.set_value(sin(udouble.get_value()));
    result.set_error(udouble.get_error() * cos(udouble.get_value()));
    return result;
}
Udouble         cos(const Udouble& udouble)
{
    Udouble result;
    result.set_value(cos(udouble.get_value()));
    result.set_error(udouble.get_error() * sin(udouble.get_value()));
    return result;
}
Udouble         tan(const Udouble& udouble)
{
    Udouble result;
    result.set_value(tan(udouble.get_value()));
    double error = udouble.get_error() / pow(cos(udouble.get_value()), 2);
    result.set_error(error);
    return result;
}
Udouble         sinh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(sinh(udouble.get_value()));
    double error = udouble.get_error() * cosh(udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         cosh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(cosh(udouble.get_value()));
    double error = udouble.get_error() * sinh(udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         tanh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(tanh(udouble.get_value()));
    double error = udouble.get_error() / pow(cosh(udouble.get_value()), 2);
    result.set_error(error);
    return result;
}
Udouble         asin(const Udouble& udouble)
{
    Udouble result;
    result.set_value(asin(udouble.get_value()));
    double error = udouble.get_error() / sqrt(1 - udouble.get_value()*udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         acos(const Udouble& udouble)
{
    Udouble result;
    result.set_value(acos(udouble.get_value()));
    double error = udouble.get_error() / sqrt(1 - udouble.get_value()*udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         atan(const Udouble& udouble)
{
    Udouble result;
    result.set_value(atan(udouble.get_value()));
    double error = udouble.get_error() / sqrt(1 + udouble.get_value()*udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         asinh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(asinh(udouble.get_value()));
    double error = udouble.get_error() / sqrt(1 + udouble.get_value()*udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         acosh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(acosh(udouble.get_value()));
    double error = udouble.get_error() / (sqrt(1 - udouble.get_value())*sqrt(1 + udouble.get_value()));
    result.set_error(error);
    return result;
}
Udouble         atanh(const Udouble& udouble)
{
    Udouble result;
    result.set_value(atanh(udouble.get_value()));
    double error = udouble.get_error() / (1 - udouble.get_value()*udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         exp(const Udouble& udouble)
{
    Udouble result;
    result.set_value(exp(udouble.get_value()));
    double error = udouble.get_error() * exp(udouble.get_value());
    result.set_error(error);
    return result;
}
Udouble         pow(const Udouble& udouble, const double n)
{
    Udouble result;
    result.set_value(pow(udouble.get_value(), n));
    double error = udouble.get_error() * n * pow(udouble.get_value(), n-1);
    result.set_error(error);
    return result;
}
Udouble         pow(const Udouble& udouble, const int n)
{
    Udouble result;
    result.set_value(pow(udouble.get_value(), n));
    double error = udouble.get_error() * n * pow(udouble.get_value(), n-1);
    result.set_error(error);
    return result;
}
Udouble         pow(const Udouble& udouble, const Udouble& n)
{
    Udouble result;
    result.set_value(pow(udouble.get_value(), n.get_value()));
    double error = sqrt(pow(udouble.get_error() * n.get_value() * pow(udouble.get_value(), n.get_value()-1), 2)
                    + pow(n.get_error() * pow(udouble.get_value(), n.get_value()) * log(udouble.get_value()), 2));
    result.set_error(error);
    return result;
}
Udouble         log(const Udouble& udouble)
{
    Udouble result;
    result.set_value(log(udouble.get_value()));
    double error = udouble.get_error() / udouble.get_value();
    result.set_error(error);
    return result;
}
Udouble         log10(const Udouble& udouble)
{
    Udouble result;
    result.set_value(log10(udouble.get_value()));
    double error = udouble.get_error() / (udouble.get_value()*log(10));
    result.set_error(error);
    return result;
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

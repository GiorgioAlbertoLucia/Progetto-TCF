#include <iostream>
#include <math.h>

#include "../include/udouble.hpp"
#include "../include/partder.hpp"

int Udouble::count = 0;

std::ostream&    operator<<(std::ostream& out, const Udouble& udouble)
{
    //if(udouble.get_format()){return out;}
    //else                            
    return out << udouble.get_label() << " " << udouble.get_value() << " ± " << udouble.get_error();
}

Udouble         sin(const Udouble& udouble)
{
    Udouble result;
    /*
    std::cout << "check: value = " << udouble.get_value() << ", error = " << udouble.get_error() << std::endl;
    std::cout << "check: sin(value) = " << sin(udouble.get_value()) << ", error_p = " << udouble.get_error() * cos(udouble.get_value()) << std::endl;
    */
    result.set_value( sin(udouble.value) );
    /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    */
    return result;
}
Udouble         cos(const Udouble& udouble)
{
    Udouble result;
    result.set_value( cos(udouble.value) );
    
    /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    */
    
    return result;
}
/*
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
*/

Udouble::Udouble(const PartDer& value, const double error, const char * label, const bool format)
{
    count++;

    Udouble::set_value(value);
    Udouble::set_error(error);

    /*
    Udouble::label = std::string(label);
    if(Udouble::label == "")    Udouble::label += value.get_label();
    if(Udouble::label == "")    for(int i = 0; i < count; i++)  Udouble::label += "u";
    Udouble::set_format(format);
    */
}
/**
 * @brief Copy Constructor.
 * Construct a new Udouble:: Udouble object 
 * @param udouble 
 */
Udouble::Udouble(const Udouble& udouble)
{
    count++;
    Udouble::value = udouble.get_partder();
    /*
    double err = 0;
    for (std::map<std::string, double>::const_iterator i = Udouble::errors.begin(); i != Udouble::errors.end(); i++)
    {
        std::map<std::string, double> m = udouble.value.get_df();
        if(m.find(i->first) != m.end())     err += pow(i->second * m.at(i->first), 2);
    }
    Udouble::error = sqrt(err);
    */

    /*
    std::string s_label("");
    for(int i = 0; i < count; i++)  s_label+="u";
    Udouble::label = s_label;
    Udouble::format = udouble.get_format();
    */
}

/**
 * @brief General functioning of overloaded operators (and math functions). Operation is performed on the PartDer object, so that the 
 * partial derivatives are correctly stored in the new Udouble. Propagation of errors is performed in copy constructor and overload of 
 * operator= only. To do that, errors associated with the variables must be stored in the errors std::map.
 * In the map errors of the "fundamental" variables are stored in the for loop, as well as error of the object performing the operation.
 * While this is crucial in the first step, it adds unwanted terms in the map. Those are ignored via a double-checking loop when 
 * errors are propagated.
 * 
 * @param udouble 
 * @return Udouble& 
 */
Udouble&    Udouble::operator+(const Udouble& udouble)
{
    Udouble::value = Udouble::value + udouble.value;

    /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    Udouble::errors.insert(std::make_pair(i->first, i->second));
    Udouble::errors.insert(std::make_pair(udouble.label, udouble.error));
    Udouble::errors.insert(std::make_pair(Udouble::label, Udouble::error));
    */

    return *this;
}
Udouble&    Udouble::operator-(const Udouble& udouble)
{
    Udouble::value = Udouble::value - udouble.value;

    /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    Udouble::errors.insert(std::make_pair(i->first, i->second));
    Udouble::errors.insert(std::make_pair(udouble.label, udouble.error));
    Udouble::errors.insert(std::make_pair(Udouble::label, Udouble::error));
    */

    return *this;
}



Udouble&    Udouble::operator*(const Udouble& udouble)
{
    Udouble::value = Udouble::value * udouble.value;
   
   /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    Udouble::errors.insert(std::make_pair(i->first, i->second));
    Udouble::errors.insert(std::make_pair(udouble.label, udouble.error));
    Udouble::errors.insert(std::make_pair(Udouble::label, Udouble::error));
    */

    return *this;
} 
Udouble&    Udouble::operator/(const Udouble& udouble)
{
    Udouble::value = Udouble::value / udouble.value;

    /*
    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    Udouble::errors.insert(std::make_pair(i->first, i->second));
    Udouble::errors.insert(std::make_pair(udouble.label, udouble.error));
    Udouble::errors.insert(std::make_pair(Udouble::label, Udouble::error));
    */

    return *this;
}

/*
Udouble&    Udouble::operator*(const double scalar)                                 // multiply by a scalar
{
    Udouble::value = Udouble::value * scalar;

    std::map<std::string, double> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    Udouble::errors.insert(std::make_pair(i->first, i->second));
    Udouble::errors.insert(std::make_pair(udouble.label, udouble.error));
    Udouble::errors.insert(std::make_pair(Udouble::label, Udouble::error));

    return *this;
}
Udouble&    Udouble::operator*(const int scalar)
{
    Udouble::value *= scalar;
    Udouble::error *= scalar;
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
*/

Udouble&    Udouble::operator=(const Udouble& udouble) noexcept
{
    if(this == &udouble)    return *this;

    Udouble::value = udouble.get_partder();
    
    /*
    double err = 0;
    for (std::map<std::string, double>::const_iterator i = Udouble::errors.begin(); i != Udouble::errors.end(); i++)
    {
        std::map<std::string, double> m = udouble.value.get_df();
        if(m.find(i->first) != m.end())     err += pow(i->second * m.at(i->first), 2);
    }
    Udouble::error = sqrt(err);
    */

    /*
    std::string s_label("");
    for(int i = 0; i < count; i++)  s_label+="u";
    Udouble::label = s_label;
    */

    std::map<std::string, double> m {{Udouble::label, 1},};
    Udouble::value.set_df(m);

    Udouble::format = udouble.get_format();

    return *this;
} 
bool        Udouble::operator==(const Udouble& udouble)
{
    if(Udouble::value.get_f() == udouble.get_value() && Udouble::error == udouble.get_error())  return true;
    else                                                                                        return false;
}

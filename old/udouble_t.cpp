#include <iostream>
#include <math.h>

#include "../include_t/udouble_t.hpp"
#include "../include_t/partder_t.hpp"


template <class T>
int Udouble<T>::count = 0;

template <class T>
std::ostream&    operator<<(std::ostream& out, const Udouble<T>& udouble)
{
    //if(udouble<T>.get_format()){return out;}
    //else                            
    return out << udouble.get_label() << " = " << udouble.get_value() << " ± " << udouble.get_error();
}

template <class T>
Udouble<T>        sin(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = sin(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        cos(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = cos(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        tan(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = tan(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        sinh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = sinh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        cosh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = cosh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        tanh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = tanh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        asin(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = asin(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        acos(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = acos(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        atan(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = atan(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        asinh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = asinh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        acosh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = acosh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        atanh(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = atanh(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        exp(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = exp(udouble<T>.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        pow(const Udouble<T>& udouble, const double n)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = pow(udouble.value, n);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        pow(const Udouble<T>& udouble, const int n)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = pow(udouble.value, n);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        pow(const Udouble<T>& udouble, const Udouble<T>& n)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = pow(udouble.value, n.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    m = n.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(n.label, n.error);
    
    return result;
}
template <class T>
Udouble<T>        log(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = log(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>        log10(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = log10(udouble.value);
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}


template <class T>
Udouble<T>::Udouble()
{
    count++;
    Udouble<T>::set_format(false);
}
template <class T>
Udouble<T>::Udouble(const T& value, const T& error)
{
    count++;

    Udouble<T>::set_value(value);
    Udouble<T>::set_error(error);

    Udouble<T>::label += Udouble<T>::value.get_label();
}
template <class T>
Udouble<T>::Udouble(const PartDer<T>& value, const T& error)
{
    count++;

    Udouble<T>::set_value(value);
    Udouble<T>::set_error(error);

    Udouble<T>::label += value.get_label();
}
/**
 * @brief Copy Constructor.
 * Construct a new Udouble<T>:: Udouble<T> object 
 * @param udouble<T> 
 */
template <class T>
Udouble<T>::Udouble(const Udouble<T>& udouble)
{
    count++;
    Udouble<T>::value = udouble.get_partder();
    
    T err = 0;
    std::cout << std::endl << std::endl << "Setting error..." << std::endl;
    for (std::map<std::string, T>::const_iterator i = Udouble<T>::errors.begin(); i != Udouble<T>::errors.end(); i++)
    {
        std::cout << "error: " << err << std::endl;
        std::cout << "error in map: " << i->second << std::endl;
        std::map<std::string, T> m = udouble.value.get_df();
        if(m.find(i->first) != m.end()) {    err += pow(i->second * m.at(i->first), 2);
        std::cout << "part der in map: " << m.at(i->first) << std::endl; }
    }
    std::cout << std::endl << std::endl;
    Udouble<T>::error = sqrt(err);

    Udouble<T>::label = std::string("");
    for(int i = 0; i < count; i++)  Udouble<T>::label += "u";

    std::map<std::string, T> m {{Udouble<T>::label, 1},};
    Udouble<T>::value.set_df(m);

    Udouble<T>::format = udouble.get_format();
}




template <class T>
Udouble<T>&    Udouble<T>::set_value(const T& value)
{
    PartDer<T> partder(value); 
    Udouble<T>::value = partder; 
    return *this;
}
template <class T>
Udouble<T>&    Udouble<T>::autoset_label()
{
    std::map<std::string, T> m = Udouble<T>::value.get_df();
    if(m.size() == 1)   for(std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++) Udouble<T>::label = i->first;
    return *this;
}




/**
 * @brief General functioning of overloaded operators (and math functions). Operation is performed on the PartDer object, so that the 
 * partial derivatives are correctly stored in the new Udouble<T>. Propagation of errors is performed in copy constructor and overload of 
 * operator= only. To do that, errors associated with the variables must be stored in the errors std::map.
 * In the map errors of the "fundamental" variables are stored in the for loop, as well as error of the object performing the operation.
 * While this is crucial in the first step, it adds unwanted terms in the map. Those are ignored via a double-checking loop when 
 * errors are propagated.
 * 
 * @param udouble<T> 
 * @return Udouble<T>& 
 */
template <class T>
Udouble<T>     Udouble<T>::operator+(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = Udouble<T>::value + udouble.value;

    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    m = Udouble<T>::errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    result.insert_errors(Udouble<T>::label, Udouble<T>::error);

    return result;
}
template <class T>
Udouble<T>     Udouble<T>::operator-(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = Udouble<T>::value - udouble.value;

    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    m = Udouble<T>::errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    result.insert_errors(Udouble<T>::label, Udouble<T>::error);

    return result;
}
template <class T>
Udouble<T>     Udouble<T>::operator*(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = Udouble<T>::value * udouble.value;

    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    m = Udouble<T>::errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    result.insert_errors(Udouble<T>::label, Udouble<T>::error);

    return result;
} 
template <class T>
Udouble<T>     Udouble<T>::operator/(const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = Udouble<T>::value / udouble.value;

    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    m = Udouble<T>::errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    result.insert_errors(Udouble<T>::label, Udouble<T>::error);

    return result;
}


template <class T>
Udouble<T>     operator*(const double c, const Udouble<T>& udouble)                                 // multiply by a scalar
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = c * udouble<T>.value;
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>     operator/(const double c, const Udouble<T>& udouble)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = c / udouble.value;
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}
template <class T>
Udouble<T>     operator/(const Udouble<T>& udouble, const double c)
{
    Udouble<T> result;
    Udouble<T>::count--;
    result.value = udouble.value / c;
    
    std::map<std::string, T> m = udouble.errors;
    for (std::map<std::string, T>::const_iterator i = m.begin(); i != m.end(); i++)    result.insert_errors(i->first, i->second);
    result.insert_errors(udouble.label, udouble.error);
    
    return result;
}

template <class T>
Udouble<T>&    Udouble<T>::operator=(const Udouble<T>& udouble) noexcept
{
    if(this == &udouble)    return *this;

    Udouble<T>::value = udouble.get_partder();
    
    T err = 0;
    std::cout << std::endl << std::endl << "Setting error..." << std::endl;
    for (std::map<std::string, T>::const_iterator i = udouble.errors.begin(); i != udouble.errors.end(); i++)
    {
        std::cout << "error: " << err << std::endl;
        std::cout << "error in map: " << i->second << std::endl;
        std::map<std::string, T> m = udouble.value.get_df();
        if(m.find(i->first) != m.end())   {  err += pow(i->second * m.at(i->first), 2);
        std::cout << "part der in map: " << m.at(i->first) << std::endl; }
    }
    Udouble<T>::error = sqrt(err);

    Udouble<T>::label = std::string("");
    for(int i = 0; i < count; i++)  Udouble<T>::label += "u";

    std::map<std::string, T> m {{Udouble<T>::label, 1},};
    Udouble<T>::value.set_df(m);

    Udouble<T>::format = udouble.get_format();

    return *this;
} 
template <class T>
bool        Udouble<T>::operator==(const Udouble<T>& udouble)
{
    if(Udouble<T>::value.get_f() == udouble.get_value() && Udouble<T>::error == udouble.get_error())    return true;
    else                                                                                                return false;
}

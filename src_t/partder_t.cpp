#include <iostream>
#include <cmath>
#include <map>

#include "../include_t/partder_t.hpp"

template <class T>
int PartDer<T>::count = 0;


template <class T>
PartDer<T>::PartDer()
{
    count++; 
    PartDer<T>::label = std::string("");
    for(int i = 0; i < count; i++)  PartDer<T>::label+="p";
}
template <class T>
PartDer<T>::PartDer(const T& x)
{
    count++;
    PartDer<T>::f = x;
    for(int i = 0; i < count; i++)  PartDer<T>::label += "p";
    PartDer<T>::df = {{PartDer<T>::label, 1.},};
}
template <class T>
PartDer<T>::PartDer(const T& x, const std::map<std::string, T&>, const char * label)
{
    count++;
    PartDer<T>::f = x;
    PartDer<T>::df = df;
    
    std::map<std::string, T&> m = PartDer<T>::df;
    if(m.size() == 1)   for(std::map<std::string, T&>::const_iterator i = m.begin(); i != m.end(); i++) PartDer<T>::label = i->first;
    else PartDer<T>::label = std::string(label);
    if(PartDer<T>::label == "")  for(int i = 0; i < count; i++)  PartDer<T>::label += "p";
}
template <class T>
PartDer<T>::PartDer(const PartDer<T>& derivative)
{
    count++;
    PartDer<T>::f = derivative.f;
    PartDer<T>::df = derivative.df;
    
    std::string label("");
    for(int i = 0; i < count; i++)  label+="p";
    set_label(label);
    
}

template <class T>
PartDer<T> PartDer<T>::operator+(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = PartDer<T>::f + g.f;
    
    // checks if the two functions are functions of the same variable. If they are, the partial derivative is
    // determined via standard rules of differentiation, if not the partial derivative of the function of that 
    // variable is set 
    
    for(std::map<std::string, T&>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            T diff = i->second + g.df.at(i->first);
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            h.df.insert(std::make_pair(i->first, i->second));
        }
    }
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}
template <class T>
PartDer<T> PartDer<T>::operator-(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = PartDer<T>::f - g.f;                              
    
    
    for(std::map<std::string, T&>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            T diff = i->second - g.df.at(i->first);    
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            h.df.insert(std::make_pair(i->first, i->second));
        }
    }
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}
template <class T>
PartDer<T> PartDer<T>::operator*(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = PartDer<T>::f * g.f;                       
    
    
    for(std::map<std::string, T&>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            T diff = i->second * g.f + f * g.df.at(i->first);    
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            T diff = i->second * g.f;
            h.df.insert(std::make_pair(i->first, diff));
        }
    }
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * f;
        h.df.insert(std::make_pair(i->first, diff));
    }
    

    return h;
}
template <class T>
PartDer<T> PartDer<T>::operator/(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = PartDer<T>::f / g.f;                              
    
    
    for(std::map<std::string, T&>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            T diff = i->second * g.f - f * g.df.at(i->first) / pow(g.f, 2);    
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            T diff = i->second / g.f;
            h.df.insert(std::make_pair(i->first, diff));
        }
    }
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * f / pow(g.f, 2);
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}


template <class T>
PartDer<T> sin(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::sin(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = cos(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> cos(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::cos(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = - sin(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> tan(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::tan(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / pow(cos(g.f),2);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> sinh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::sinh(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = cosh(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> cosh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::cosh(g.f);                              
    
    for(std::map<std::string, dT&::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = sinh(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> tanh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::tanh(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / pow(cosh(g.f),2);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> asin(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::asin(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / sqrt(1 - pow(g.f,2));
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> acos(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::acos(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / sqrt(1 - pow(g.f,2));
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> atan(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::atan(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / sqrt(1 + pow(g.f,2));
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> asinh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::asinh(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / sqrt(1 + pow(g.f,2));
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> acosh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::acosh(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / (sqrt(1 - g.f) * sqrt(1 + g.f));
        h.df.insert(std::make_pair(i->first, diff));
    }

    return h;
}
template <class T>
PartDer<T> atanh(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = std::atanh(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / sqrt(1 - pow(g.f,2));
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> exp(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = exp(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * h.f;
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> pow(const PartDer<T>& g, const double n)
{
    PartDer<T> h;
    h.f = pow(g.f, n);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * n * pow(g.f, n-1);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> pow(const PartDer<T>& g, const int n)
{
    PartDer<T> h;
    h.f = pow(g.f, n);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * n * pow(g.f, n-1);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> pow(const PartDer<T>& g, const PartDer<T>& n)
{
    PartDer<T> h;
    h.f = pow(g.f, n.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second * n.f * pow(g.f, n.f-1);
        h.df.insert(std::make_pair(i->first, diff));
    }
    for(std::map<std::string, T&>::const_iterator i = n.df.begin(); i != n.df.end(); i++)
    {
        T diff = i->second * pow(g.f, n.f) * log(g.f);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> log(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = log(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / g.f;
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> log10(const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = log10(g.f);                              
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        T diff = i->second / (g.f * log(10));
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}




template <class T>
PartDer<T> operator+(const double c, const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = c + g.f;
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    
    return h;
}
template <class T>
PartDer<T> operator-(const double c, const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = c - g.f;
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    
    return h;
}
template <class T>
PartDer<T> operator*(const double c, const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = c * g.f;
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    
    return h;
}
template <class T>
PartDer<T> operator/(const double c, const PartDer<T>& g)
{
    PartDer<T> h;
    h.f = c / g.f;
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        double diff = - c / pow(g.f, 2);
        h.df.insert(std::make_pair(i->first, diff));
    }
    
    return h;
}
template <class T>
PartDer<T> operator/(const PartDer<T>& g, const double c)
{
    PartDer<T> h;
    h.f = g.f / c;
    
    for(std::map<std::string, T&>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    
    return h;
}




template <class T>
void PartDer<T>::print()
{
    std::cout << "f = " << PartDer<T>::f << std::endl;
    std::cout << "Partial derivatives: " << std::endl;
    
    for (std::map<std::string, T&>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        std::cout << "df/d" << i->first << " = " << i->second << std::endl;
    }
    
}

#include <iostream>
#include <math.h>

#include "../include/partder.hpp"

PartDer::PartDer(){}

PartDer::PartDer(const double x, const std::vector<double> df){
    PartDer::f = x;
    PartDer::df = df;
}

PartDer::PartDer(const PartDer& derivative)
{
    PartDer::f = derivative.f;
    PartDer::df = derivative.df;
}

PartDer::~PartDer()
{

}

PartDer PartDer::operator+(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f + g.f;
    for(int i = 0; i < PartDer::df.size(); i++) h.df.push_back(PartDer::df.at(i) + g.df.at(i));
    return h;
}
PartDer PartDer::operator-(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f - g.f;
    for(int i = 0; i < PartDer::df.size(); i++) h.df.push_back(PartDer::df.at(i) - g.df.at(i));
    return h;
}
PartDer PartDer::operator*(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f * g.f;
    for(int i = 0; i < PartDer::df.size(); i++) h.df.push_back(PartDer::df.at(i)*g.f + PartDer::f*g.df.at(i));
    return h;
}
PartDer PartDer::operator/(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f / g.f;
    for(int i = 0; i < PartDer::df.size(); i++) h.df.push_back((PartDer::df.at(i)*g.f - PartDer::f*g.df.at(i))/pow(g.f, 2));
    return h;
}

PartDer sin(const PartDer& g)
{
    PartDer h;
    h.set_f(sin(g.get_f()));
    for(int i = 0; i < g.get_df().size(); i++) h.add_df(cos(g.get_f()) * g.get_dfi(i));
    return h;
}
PartDer cos(const PartDer& g)
{
    PartDer h;
    h.set_f(cos(g.get_f()));
    for(int i = 0; i < g.get_df().size(); i++) h.add_df(-sin(g.get_f()) * g.get_dfi(i));
    return h;
}

void PartDer::print()
{
    std::cout << "Function has value " << PartDer::f << std::endl;
    std::cout << "Its " << PartDer::df.size() << " partial derivatives are: ";
    for (std::vector<double>::const_iterator i = PartDer::df.begin(); i != PartDer::df.end(); i++)
    {
        std::cout << *i;
        if(i==df.end()-1)   std::cout << std::endl;
        else                std::cout << ", ";
    }
}

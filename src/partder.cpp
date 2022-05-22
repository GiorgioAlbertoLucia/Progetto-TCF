#include <iostream>
#include <cmath>
#include <map>

#include "../include/partder.hpp"

int PartDer::count = 0;

PartDer::PartDer()
{
    //count++;
}
PartDer::PartDer(const double x, const std::map<std::string, double> df, const char * label){
    count++;
    PartDer::f = x;
    PartDer::df = df;
    
    std::string str(label);
    if(str == "")  for(int i = 0; i < count; i++)  str+="p";
    set_label(str);
    
    
}
PartDer::PartDer(const PartDer& derivative)
{
    count++;
    PartDer::f = derivative.f;
    PartDer::df = derivative.df;
    
    std::string label("");
    for(int i = 0; i < count; i++)  label+="p";
    set_label(label);
    
}
PartDer::~PartDer()
{
    count--;
}

PartDer PartDer::operator+(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f + g.f;
    
    // checks if the two functions are functions of the same variable. If they are, the partial derivative is
    // determined via standard rules of differentiation, if not the partial derivative of the function of that 
    // variable is set 
    
    for(std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            double diff = i->second + g.df.at(i->first);
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            h.df.insert(std::make_pair(i->first, i->second));
        }
    }
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}
PartDer PartDer::operator-(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f - g.f;                              // -----
    
    
    for(std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            double diff = i->second - g.df.at(i->first);    // -----
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            h.df.insert(std::make_pair(i->first, i->second));
        }
    }
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}
PartDer PartDer::operator*(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f * g.f;                       
    
    
    for(std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            double diff = i->second * g.f + f * g.df.at(i->first);    
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            double diff = i->second * g.f;
            h.df.insert(std::make_pair(i->first, diff));
        }
    }
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        double diff = i->second * f;
        h.df.insert(std::make_pair(i->first, diff));
    }
    

    return h;
}
PartDer PartDer::operator/(const PartDer& g)
{
    PartDer h;
    h.f = PartDer::f / g.f;                              
    
    
    for(std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        if(g.df.find(i->first) != g.df.end())
        {
            double diff = i->second * g.f - f * g.df.at(i->first) / pow(g.f, 2);    
            h.df.insert(std::make_pair(i->first, diff));
        }
        else if(g.df.find(i->first) == g.df.end())
        {
            double diff = i->second / g.f;
            h.df.insert(std::make_pair(i->first, diff));
        }
    }
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        double diff = i->second * f / pow(g.f, 2);
        h.df.insert(std::make_pair(i->first, i->second));
    }
    

    return h;
}

PartDer sin(const PartDer& g)
{
    PartDer h;
    h.set_f( std::sin(g.f) );                              
    
    
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        double diff = cos(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }
    

    return h;
}
PartDer cos(const PartDer& g)
{
    PartDer h;
    h.set_f( std::cos(g.f) );                              
    
    
    for(std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++)
    {
        double diff = - sin(g.f) * i->second;
        h.df.insert(std::make_pair(i->first, diff));
    }
    

    return h;
}

void PartDer::print()
{
    std::cout << "f = " << PartDer::f << std::endl;
    std::cout << "Partial derivatives: " << std::endl;
    
    for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++)
    {
        std::cout << "df/d" << i->first << " = " << i->second << std::endl;
    }
    
}

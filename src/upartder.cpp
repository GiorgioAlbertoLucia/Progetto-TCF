#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <map>
#include <utility>

#include "../include/upartder.hpp"

/*  PROBLEM: THE FOLLOWING IMPLEMENTATION ONLY WORKS FOR FUNCTIONS SUCH THAT f=f(x0,x1,...,xn) with xi comparing in the 
    f(...) expression only if x0,...,xi-1 have already appeared. xi is such that UPartDer xi(xi, 0, 0, ..., 1, ..., 0)

    eg  f = f(x0, x1) = x0 + x1 ok
        f = f(x0, x1) = x1 + x0 not ok
*/

UPartDer::UPartDer(){}

UPartDer::UPartDer(const double x, const double err, const std::vector<double> df, const char * label): Udouble(x, err)
{
    UPartDer::df = df;
    UPartDer::label = std::string(label);
}
UPartDer::UPartDer(const double x, const double err, const std::vector<double> df, const std::string label): Udouble(x, err)
{
    UPartDer::df = df;
    UPartDer::label = label;
}

UPartDer::UPartDer(const Udouble& u, const std::vector<double> df, const char * label)
{
    UPartDer::f = u;
    UPartDer::df = df;
    UPartDer::label = std::string(label);
}
UPartDer::UPartDer(const Udouble& u, const std::vector<double> df, const std::string label)
{
    UPartDer::f = u;
    UPartDer::df = df;
    UPartDer::label = label;
}

UPartDer::UPartDer(const UPartDer& func)
{
    UPartDer::df = func.df;
    UPartDer::dict.insert(func.dict.begin(), func.dict.end());
    // check
    for(std::map<std::string, double>::const_iterator i=func.dict.begin(); i!=func.dict.end(); i++)
        std::cout << "check copy constructor" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    double sqrd_error = 0;
    int j = 0;
    for (std::map<std::string, double>::const_iterator i = UPartDer::dict.begin(); i != UPartDer::dict.end(); i++)
    {
        sqrd_error += pow(df.at(j)*i->second, 2);
        j++;
    }
    Udouble u(func.f.get_value(), sqrt(sqrd_error));
    UPartDer::f = u;
}

UPartDer::~UPartDer()
{

}

UPartDer UPartDer::operator=(const UPartDer& g)
{
    UPartDer::df = g.df;
    UPartDer::dict.insert(std::map<std::string, double>::value_type(g.label, g.f.get_error()));

    // check
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    double sqrd_error = 0;
    int j = 0;
    for (std::map<std::string, double>::const_iterator i = UPartDer::dict.begin(); i != UPartDer::dict.end(); i++)
    {
        sqrd_error += pow(df.at(j)*i->second, 2);
        j++;
    }
    Udouble u(g.f.get_value(), sqrt(sqrd_error));
    UPartDer::f = u;
    
    return *this;
}

/**
 * @brief NOTE: operator overloading does not define the error of the new UPartDer::f. In order to correctly evaluate this value,
 * that will be done in the copy constructor and in the operator=
 * 
 * @param g 
 * @return UPartDer 
 */
UPartDer UPartDer::operator+(const UPartDer& g)
{
    UPartDer h;
    h.f.set_value(UPartDer::f.get_value() + g.f.get_value());
    for(int i = 0; i < UPartDer::df.size(); i++) h.df.push_back(UPartDer::df.at(i) + g.df.at(i));
    h.dict.insert(std::map<std::string, double>::value_type(UPartDer::label, UPartDer::f.get_error()));
    h.dict.insert(std::map<std::string, double>::value_type(g.label, g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=UPartDer::dict.begin(); i!=UPartDer::dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;
    
    return h;
}
UPartDer UPartDer::operator-(const UPartDer& g)
{
    UPartDer h;
    h.f.set_value(UPartDer::f.get_value() - g.f.get_value());
    for(int i = 0; i < UPartDer::df.size(); i++) h.df.push_back(UPartDer::df.at(i) - g.df.at(i));
    h.dict.insert(std::map<std::string, double>::value_type(UPartDer::label, UPartDer::f.get_error()));
    h.dict.insert(std::map<std::string, double>::value_type(g.label, g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=UPartDer::dict.begin(); i!=UPartDer::dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    return h;
}
UPartDer UPartDer::operator*(const UPartDer& g)
{
    UPartDer h;
    h.f.set_value(UPartDer::f.get_value() * g.f.get_value());
    for(int i = 0; i < UPartDer::df.size(); i++) 
        h.df.push_back(UPartDer::df.at(i)*g.f.get_value() + UPartDer::f.get_value()*g.df.at(i));
    h.dict.insert(std::map<std::string, double>::value_type(UPartDer::label, UPartDer::f.get_error()));
    h.dict.insert(std::map<std::string, double>::value_type(g.label, g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=UPartDer::dict.begin(); i!=UPartDer::dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    return h;
}
UPartDer UPartDer::operator/(const UPartDer& g)
{
    UPartDer h;
    h.f.set_value(UPartDer::f.get_value() / g.f.get_value());
    for(int i = 0; i < UPartDer::df.size(); i++) 
        h.df.push_back((UPartDer::df.at(i)*g.f.get_value() - UPartDer::f.get_value()*g.df.at(i))/pow(g.f.get_value(), 2));
    h.dict.insert(std::map<std::string, double>::value_type(UPartDer::label, UPartDer::f.get_error()));
    h.dict.insert(std::map<std::string, double>::value_type(g.label, g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=UPartDer::dict.begin(); i!=UPartDer::dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    return h;
}

UPartDer sin(const UPartDer& g)
{
    UPartDer h;
    h.get_f().set_value( sin( g.get_f().get_value()) );
    for(int i = 0; i < g.get_df().size(); i++) h.add_df(cos(g.get_f().get_value()) * g.get_dfi(i));
    h.dict.insert(std::map<std::string, double>::value_type(g.get_label(), g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    return h;
}
UPartDer cos(const UPartDer& g)
{
    UPartDer h;
    h.get_f().set_value( cos( g.get_f().get_value()) );
    for(int i = 0; i < g.get_df().size(); i++) h.add_df(-sin(g.get_f().get_value()) * g.get_dfi(i));
    h.dict.insert(std::map<std::string, double>::value_type(g.get_label(), g.f.get_error()));
    // check
    for(std::map<std::string, double>::const_iterator i=g.dict.begin(); i!=g.dict.end(); i++)
        std::cout << "check operator" << std::endl << i->first << " " << i->second << std::endl;
    std::cout << std::endl;

    return h;
}

void UPartDer::print()
{
    std::cout << "Function has value " << UPartDer::f << std::endl;
    std::cout << "Its " << UPartDer::df.size() << " partial funcs are: ";
    for (std::vector<double>::const_iterator i = UPartDer::df.begin(); i != UPartDer::df.end(); i++)
    {
        std::cout << *i;
        if(i==df.end()-1)   std::cout << std::endl;
        else                std::cout << ", ";
    }
}
void UPartDer::print_dict()
{
    std::cout << "Function " << UPartDer::label << " dictionary: " << std::endl;
    for (std::map<std::string, double>::const_iterator i = UPartDer::dict.begin(); i != UPartDer::dict.end(); i++)
    {
        std::cout << i->first << " " << i->second << std::endl;
    }
    
}
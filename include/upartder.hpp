#ifndef UPARTDER_H
#define UPARTDER_H

#include <vector>
#include <string>
#include <map>

#include "udouble.hpp"

/**
 * @brief I believe this is a little counterintuitive and a detailed explaination is needed. The class data memebers are
 * the value of the function at a given (x0, x1, ..., xn) and its derivative at the same (x0, x1, ..., xn). In order to 
 * make the class understand how to operatate on the function, you should create constant function x0(value of x0) etc 
 * for all the xi parameters, then create a function f as a composition of those function object (that is, using a copy 
 * constructor). 
 * 
 * Each of the xi parameters is conveniently written as an object xi(xi, vector_df) where the vector contains 0 for each value
 * except for the i-th value that is 1 (essencially, the vector is dxi/dxj) for j=0,...,n 
 * 
 * If you, instead, define e.g. UPartDer f = sin(1), the class will not know that there is a sine in there, and f will be 
 * treated as a constant function of value sin(1)!
 * 
 */
class UPartDer: public Udouble
{

    friend  UPartDer            sin(const UPartDer&);
    friend  UPartDer            cos(const UPartDer&);
    friend  UPartDer            tan(const UPartDer&);
    friend  UPartDer            sinh(const UPartDer&);
    friend  UPartDer            cosh(const UPartDer&);
    friend  UPartDer            tanh(const UPartDer&);
    friend  UPartDer            asin(const UPartDer&);
    friend  UPartDer            acos(const UPartDer&);
    friend  UPartDer            atan(const UPartDer&);
    friend  UPartDer            asinh(const UPartDer&);
    friend  UPartDer            acosh(const UPartDer&);
    friend  UPartDer            atanh(const UPartDer&);
    friend  UPartDer            exp(const UPartDer&);
    friend  UPartDer            pow(const UPartDer&, const double);
    friend  UPartDer            pow(const UPartDer&, const int);
    friend  UPartDer            pow(const UPartDer&, const UPartDer&);
    friend  UPartDer            log(const UPartDer&);
    friend  UPartDer            log10(const UPartDer&);

public:
    UPartDer();
    UPartDer(const double, const double, const std::vector<double>, const char * = 0);
    UPartDer(const double, const double, const std::vector<double>, const std::string);
    UPartDer(const Udouble&, const std::vector<double>, const char * = 0);
    UPartDer(const Udouble&, const std::vector<double>, const std::string);
    UPartDer(const UPartDer&);
    ~UPartDer();

    const   UPartDer&           set_f(const Udouble f)                      {UPartDer::f=f; return *this;};
    const   UPartDer&           set_dfi(const double dfi, const int i)      {UPartDer::df.at(i)=dfi; return *this;};
    const   UPartDer&           add_df(const double dfi)                    {UPartDer::df.push_back(dfi); return *this;};
    const   UPartDer&           set_label(const char * label)               {UPartDer::label=std::string(label); return *this;};
    const   UPartDer&           set_label(const std::string label)          {UPartDer::label=label; return *this;};

            Udouble             get_f() const                               {return UPartDer::f;};
    const   std::vector<double> get_df() const                              {return UPartDer::df;}
    const   double              get_dfi(int xi) const                       {return UPartDer::df.at(xi);};
    const   std::string         get_label() const                           {return UPartDer::label;};

            UPartDer            operator=(const UPartDer&); 

            UPartDer            operator+(const UPartDer&); // f + g
            UPartDer            operator-(const UPartDer&); // f - g
            UPartDer            operator*(const UPartDer&); // f * g
            UPartDer            operator/(const UPartDer&); // f / g
       
    friend  UPartDer            operator+(const double, const UPartDer&); //c+f
    friend  UPartDer            operator-(const double, const UPartDer&); //c-f
    friend  UPartDer            operator*(const double, const UPartDer&); //c*f
    friend  UPartDer            operator/(const double, const UPartDer&); //c/f
            UPartDer            operator^(double); // f^c,  Where c is constant
    
            void                print();
            void                print_dict();

private:
    Udouble f;                                  // function value at (x1, x2, ..., xn)
    std::vector<double> df;                     // vector containing partial derivatives df/dxi
    std::string label;                          // name of the function
    std::map<std::string, double> dict;         // dictionary variable name-error for any variable involved in composition
};


#endif
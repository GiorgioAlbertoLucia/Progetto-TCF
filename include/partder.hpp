#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
#include <string>

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
 * If you, instead, define e.g. PartDer f = sin(1), the class will not know that there is a sine in there, and f will be 
 * treated as a constant function of value sin(1)!
 * 
 */
class PartDer
{
    friend  PartDer         sin(const PartDer&);
    friend  PartDer         cos(const PartDer&);
    friend  PartDer         tan(const PartDer&);
    friend  PartDer         sinh(const PartDer&);
    friend  PartDer         cosh(const PartDer&);
    friend  PartDer         tanh(const PartDer&);
    friend  PartDer         asin(const PartDer&);
    friend  PartDer         acos(const PartDer&);
    friend  PartDer         atan(const PartDer&);
    friend  PartDer         asinh(const PartDer&);
    friend  PartDer         acosh(const PartDer&);
    friend  PartDer         atanh(const PartDer&);
    friend  PartDer         exp(const PartDer&);
    friend  PartDer         pow(const PartDer&, const double);
    friend  PartDer         pow(const PartDer&, const int);
    friend  PartDer         pow(const PartDer&, const PartDer&);
    friend  PartDer         log(const PartDer&);
    friend  PartDer         log10(const PartDer&);

public:
    PartDer();
    PartDer(const double, const std::vector<double>);
    PartDer(const PartDer&);
    ~PartDer();

    const   PartDer& set_f(const double f)                    {PartDer::f=f; return *this;};
    const   PartDer& set_dfi(const double dfi, const int i)   {PartDer::df.at(i)=dfi; return *this;};
    const   PartDer& add_df(const double dfi)                 {PartDer::df.push_back(dfi); return *this;};

    const double get_f() const                              {return PartDer::f;};
    const std::vector<double> get_df() const                {return PartDer::df;}
    const double get_dfi(int xi) const                      {return PartDer::df.at(xi);};

            PartDer operator+(const PartDer&); // f + g
            PartDer operator-(const PartDer&); // f - g
            PartDer operator*(const PartDer&); // f * g
            PartDer operator/(const PartDer&); // f / g
       
    friend  PartDer operator+(const double, const PartDer&); //c+f
    friend  PartDer operator-(const double, const PartDer&); //c-f
    friend  PartDer operator*(const double, const PartDer&); //c*f
    friend  PartDer operator/(const double, const PartDer&); //c/f
            PartDer operator^(double); // f^c,  Where c is constant
    
    void print();

private:
    double f;                   // function value at (x1, x2, ..., xn)
    std::vector<double> df;     // vector containing partial derivatives df/dxi
    std::string label;          // name of the function
};


#endif
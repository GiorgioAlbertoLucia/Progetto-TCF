#ifndef PARTDER_H
#define PARTDER_H

#include <vector>
#include <string>
#include <map>

/**
 * @brief I believe this is a little counterintuitive and a detailed explaination is needed. The class data memebers are
 * the value of the function at a given (x0, x1, ..., xn) and its derivative at the same (x0, x1, ..., xn). In order to 
 * make the class understand how to operatate on the function, you should create constant function x0(value of x0) etc 
 * for all the xi parameters, then create a function f as a composition of those function object (that is, using a copy 
 * constructor). 
 * 
 * Each of the xi parameters is conveniently written as an object xi(xi, map_df) where the map contains a label for the
 * i-th parameter and the value 1
 * 
 * If you, instead, define e.g. PartDer f = sin(1), the class will not know that there is a sine in there, and f will be 
 * treated as a constant function of value sin(1).
 * 
 */
template <class T>
class PartDer
{
    
public:
                        PartDer();
                        PartDer(const T, const std::map<std::string, T>, const char * = "");
                        PartDer(const PartDer&);
                        ~PartDer(){count--;};

            PartDer&    set_f(const T f)                                {PartDer::f=f; return *this;};
            PartDer&    set_dfi(const char *, const T);
            PartDer&    add_df(const char *, const T dfi);
    
            void        set_df(const std::map<std::string, T> df)       {PartDer::df=df;};
            void        set_label(const char * label)                   {PartDer::label = std::string(label);};
            void        set_label(std::string label)                    {PartDer::label = label;};
    
    const   double      get_f()                     const               {return PartDer::f;};
    const   std::map<std::string, T> get_df()       const               {return PartDer::df;};
    const   std::string get_label()                 const               {return PartDer::label;};

    static  int         get_count()                                     {return PartDer::count;};

            PartDer     operator+(const PartDer&); // f + g
            PartDer     operator-(const PartDer&); // f - g
            PartDer     operator*(const PartDer&); // f * g
            PartDer     operator/(const PartDer&); // f / g
            PartDer     operator^(const double n)                       {return pow(*this, n);}; // f^c,  Where c is constant
            PartDer     operator^(const int n)                          {return pow(*this, n);};
            PartDer     operator^(const PartDer& n)                     {return pow(*this, n);};
    

    friend  PartDer     sin(const PartDer&);
    friend  PartDer     cos(const PartDer&);
    friend  PartDer     tan(const PartDer&);
    friend  PartDer     sinh(const PartDer&);
    friend  PartDer     cosh(const PartDer&);
    friend  PartDer     tanh(const PartDer&);
    friend  PartDer     asin(const PartDer&);
    friend  PartDer     acos(const PartDer&);
    friend  PartDer     atan(const PartDer&);
    friend  PartDer     asinh(const PartDer&);
    friend  PartDer     acosh(const PartDer&);
    friend  PartDer     atanh(const PartDer&);
    friend  PartDer     exp(const PartDer&);
    friend  PartDer     pow(const PartDer&, const double);
    friend  PartDer     pow(const PartDer&, const int);
    friend  PartDer     pow(const PartDer&, const PartDer&);
    friend  PartDer     log(const PartDer&);
    friend  PartDer     log10(const PartDer&);
    

    friend  PartDer     operator+(const double, const PartDer&); //c+f
    friend  PartDer     operator-(const double, const PartDer&); //c-f
    friend  PartDer     operator*(const double, const PartDer&); //c*f
    friend  PartDer     operator/(const double, const PartDer&); //c/f
    friend  PartDer     operator/(const PartDer&, const double); //f/c
            
    void                print();

private:
    static int count;                       // how many number of PartDer objects are created in the main

    T f;                                    // function value at (x1, x2, ..., xn)
    std::map<std::string, T> df;            // map containing "variable of diff" - "derivative in that variable at (x1,...,xn)"
    std::string label;                      // name of the function
};


#endif
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
 * @tparam T int, double, float or any type that is essentially a number
 */
template <class T>
class PartDer
{
    
public:
                                        PartDer();
                                        PartDer(const T&);
                                        PartDer(const T&, const std::map<std::string, T&>, const char * = "");
                                        PartDer(const PartDer&);
                                        ~PartDer(){count--;};

            PartDer<T>                  set_f(const T& f)                               {PartDer::f=f; return *this;};
            PartDer<T>                  set_dfi(const char *, const T&);
            PartDer<T>                  add_df(const char *, const T& dfi);

            void                        set_df(const std::map<std::string, T&> df)      {PartDer::df=df;};
            void                        set_label(const char * label)                   {PartDer::label = std::string(label);};
            void                        set_label(std::string label)                    {PartDer::label = label;};

    const   T&                          get_f()                     const               {return PartDer::f;};
    const   std::map<std::string, T&>   get_df()                    const               {return PartDer::df;};
    const   std::string                 get_label()                 const               {return PartDer::label;};

    static  int                         get_count()                                     {return PartDer::count;};

            PartDer<T>                  operator+(const PartDer<T>&); // f + g
            PartDer<T>                  operator-(const PartDer<T>&); // f - g
            PartDer<T>                  operator*(const PartDer<T>&); // f * g
            PartDer<T>                  operator/(const PartDer<T>&); // f / g
            PartDer<T>                  operator^(const double n)                       {return pow(*this, n);}; // f^c,  Where c is constant
            PartDer<T>                  operator^(const int n)                          {return pow(*this, n);};
            PartDer<T>                  operator^(const PartDer<T>& n)                     {return pow(*this, n);};


    friend  PartDer<T>                  sin(const PartDer<T>&);
    friend  PartDer<T>                  cos(const PartDer<T>&);
    friend  PartDer<T>                  tan(const PartDer<T>&);
    friend  PartDer<T>                  sinh(const PartDer<T>&);
    friend  PartDer<T>                  cosh(const PartDer<T>&);
    friend  PartDer<T>                  tanh(const PartDer<T>&);
    friend  PartDer<T>                  asin(const PartDer<T>&);
    friend  PartDer<T>                  acos(const PartDer<T>&);
    friend  PartDer<T>                  atan(const PartDer<T>&);
    friend  PartDer<T>                  asinh(const PartDer<T>&);
    friend  PartDer<T>                  acosh(const PartDer<T>&);
    friend  PartDer<T>                  atanh(const PartDer<T>&);
    friend  PartDer<T>                  exp(const PartDer<T>&);
    friend  PartDer<T>                  pow(const PartDer<T>&, const double);
    friend  PartDer<T>                  pow(const PartDer<T>&, const int);
    friend  PartDer<T>                  pow(const PartDer<T>&, const PartDer<T>&);
    friend  PartDer<T>                  log(const PartDer<T>&);
    friend  PartDer<T>                  log10(const PartDer<T>&);

    
    friend  PartDer<T>                  operator+(const double, const PartDer<T>&); //c+f
    friend  PartDer<T>                  operator-(const double, const PartDer<T>&); //c-f
    friend  PartDer<T>                  operator*(const double, const PartDer<T>&); //c*f
    friend  PartDer<T>                  operator/(const double, const PartDer<T>&); //c/f
    friend  PartDer<T>                  operator/(const PartDer<T>&, const double); //f/c

    void                                print();

private:
    static int count;                   // how many number of PartDer objects are created in the main

    T f;                                // function value at (x1, x2, ..., xn)
    std::map<std::string, T> df;        // map containing "variable of diff" - "derivative in that variable at (x1,...,xn)"
    std::string label;                  // name of the function
};


#endif
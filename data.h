#ifndef DATA_H
#define DATA_H

#include "file.h"
#include <iostream>
#include <vector>
#include <string>

// Abstract class for opening data from files and working with it.
// This one is for doubles, the final one will be a template class

class Data
{
public:
    virtual                 ~Data(){};

    // setter / getter
    virtual void                set_name(const char *)                            = 0;
    virtual const char          get_name()                                  const = 0;
    virtual void                set_data(const char *)                            = 0;
    virtual std::vector<double> get_data()                                  const = 0;
    virtual void                add_element(const double)                         = 0;
    virtual void                replace_element(const double, const int)          = 0;

    // operators

    virtual double              mean        ()                              const = 0;
    virtual double              std         ()                              const = 0;
    virtual void                rnd_dist    (const double, const double)    const = 0;      // inputs are min and max of the uniform distribution
    virtual double              get_min     ()                              const = 0;
    virtual double              get_max     ()                              const = 0;
    virtual double              get         (const int)                     const = 0;       // returns the nth element


};

#endif
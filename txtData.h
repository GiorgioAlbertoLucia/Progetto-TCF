#ifndef TXTDATA_H
#define TXTDATA_H

#include "txtFile.h"
#include "data.h"
#include <iostream>
#include <vector>
#include <string>

// This one is for doubles, the final one will be a template class

/**
 * @brief 
 * 
 */
class TxtData: public TxtFile, public Data
{
    friend  std::ostream&       operator<<  (std::ostream&, const TxtData&);

public:
                                TxtData(const char *, const int, const char *);             // file_path, file_column and data_name
                                TxtData(const TxtData&);                                    // copy constructor
                                ~TxtData();

    // setter / getter
            TxtData&            set_file(const char *);
            TxtFile             get_file()                                  const;
    virtual void                set_data(const char *, const int);
    virtual std::vector<double> get_data()                                  const;
    virtual void                set_name(const char *);
    virtual std::string         get_name()                                  const;

    virtual void                add_element(const double);
    virtual void                replace_element(const double, const int);
    

    // operators
            TxtData&            operator+   (const TxtData&);
            TxtData&            operator-   (const TxtData&);
            TxtData&            operator*   (const double);                                 // multiply by a scalar
            TxtData&            operator*   (const int); 
            bool                operator==  (const TxtData&);
            bool                operator!=  (const TxtData& itself)    {return !(*this == itself);};

    // statistical functions
            double              mean        ()                              const;
            double              std         ()                              const;
            void                rnd_dist    (const double, const double)    const;           // inputs are min and max of the uniform distribution
            double              get_min     ()                              const;
            double              get_max     ()                              const;
            double              get         (const int)                     const;           // returns the nth element


private:
            std::vector<double>         data_vector;
            std::string                 name;
};

#endif
#ifndef TXTDATA_H
#define TXTDATA_H

#include "txtFile.h"
#include "data.h"
#include <iostream>
#include <vector>
#include <string>

// This one is for doubles, the final one will be a template class

class TxtData: public TxtFile
{
    friend  std::ostream&   operator<<  (std::ostream&, const TxtData&);

public:
                            TxtData(const char *, int, const char *);                   // file_path, file_column and data_name
                            ~TxtData();
                            TxtData(const TxtData&);                                    // copy constructor

    // setter / getter
            void            set_file(const TxtFile);
            TxtFile         get_file()                                  const;
    virtual void            set_name(const char *);
    virtual std::string     get_name()                                  const;

    virtual void            add_element();
    virtual void            replace_element(const double, const int);
    

    // operators
            TxtData&        operator+   (const TxtData&);
            TxtData&        operator-   (const TxtData&);
            TxtData&        operator*   (const double);
            TxtData&        operator*   (const int); 
            bool            operator==  (const TxtData&);
            bool            operator!=  (const TxtData& right)    {return !(*this == right);};

            double          mean        ()                              const;
            double          std         ()                              const;
            void            rnd_dist    (const double, const double)    const;           // inputs are min and max of the uniform distribution
            double          get_min     ()                              const;
            double          get_max     ()                              const;
            double          get         (const int)                     const;           // returns the nth element


private:
            std::vector<double>         Txtdata_vector;
            TxtFile                     Txtdata_file_txt;
            std::string                 name;



};




#endif
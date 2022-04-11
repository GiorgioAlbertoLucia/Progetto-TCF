#ifndef DATA_H
#define DATA_H

#include "file.hpp"


#include <iostream>
#include <vector>
#include <string>

// Abstract class for opening data from files and working with it.
// This one is for doubles, the final one will be a template class

class Data
{
        friend  std::ostream&           operator<<(std::ostream&, const Data&);  

public:
                                        Data(const char *, const int, const char * = 0);   // file_path, file_column and data_name
                                        Data(const Data&);                                 // copy constructor
                                        ~Data();

    // setter / getter
                Data&                   set_data(const char *, const int);
                std::vector<double>     get_data()                                  const;
                Data&                   set_name(const char *);
                std::string             get_name()                                  const;
                Data&                   set_file(const char *);
                std::string             get_file()                                  const;
                //
                int                     get_entries()                               const;

                Data&                   add_element(const double);
                Data&                   replace_element(const double, const int);

    // operators
                Data&                   operator+   (const Data&);
                Data&                   operator-   (const Data&);
                Data&                   operator*   (const double);                                 // multiply by a scalar
                Data&                   operator*   (const int); 
                bool                    operator==  (const Data&);
                bool                    operator!=  (const Data& itself)    {return !(*this == itself);};

    // statistical functions

                double                  mean        ()                              const;
                double                  std         ()                              const;
                void                    rnd_dist    (const double, const double)    const;      // inputs are min and max of the uniform distribution
                double                  get_min     ()                              const;
                double                  get_max     ()                              const;
                double                  get         (const int)                     const;       // returns the nth element
private:
                std::vector<double>     data_vector;
                std::string             name;
                std::string             file_path;
                int                     entries;

};

#endif
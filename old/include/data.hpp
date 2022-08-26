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
                                        Data(const char *, const int, const char * = "");   // file_path, file_column and data_name
                                        Data(const Data&);                                 // copy constructor
                                        ~Data();

    // setter / getter
                Data&                   set_data(const char *, const int);
                Data&                   set_name(const char * name = "")                        {Data::name = std::string(name); return *this;};
                Data&                   set_file(const char * filepath)                         {Data::file_path = std::string(file_path); return *this;};
                
                
        const   std::vector<double>     get_data()                                  const       {return Data::data_vector;};        
        const   std::string             get_name()                                  const       {return Data::name;};        
        const   std::string             get_file()                                  const       {return Data::file_path;};
                /**
                * @brief Returns the number of entries in the data vector
                * 
                * @return int 
                */
        const   int                     get_entries()                               const       {return Data::entries;};
        const   double                  get_element(const int i)                    const       {return Data::data_vector.at(i);};

                /**
                 * @brief Add a single element to the data vector
                 * 
                 * @param element 
                 * @return Data& 
                 */
                Data&                   add_element(const double element)                       {Data::data_vector.push_back(element); return *this;};
                /**
                * @brief Replaces an element of data vectpr with given value.
                * @param new_element new replacing value.
                * @param position position of the element you want to swap new_element with.
                */
                Data&                   replace_element(const double value, const int i)        {Data::data_vector.at(i) = value; return *this;};

    // operators
                Data&                   operator+   (const Data&);
                Data&                   operator-   (const Data&);
                Data&                   operator*   (const double);                                 // multiply by a scalar
                Data&                   operator*   (const int); 
                bool                    operator==  (const Data&);
                bool                    operator!=  (const Data& itself)                        {return !(*this == itself);};

    // statistical functions

                double                  mean        ()                              const;
                double                  std         ()                              const;
                void                    rnd_dist    (const double, const double)    const;      // inputs are min and max of the uniform distribution
                double                  get_min     ()                              const;
                double                  get_max     ()                              const;
private:
                std::vector<double>     data_vector;
                std::string             name;
                std::string             file_path;
                int                     entries;

};

#endif
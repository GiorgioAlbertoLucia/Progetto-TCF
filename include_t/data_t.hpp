#ifndef DATA_H
#define DATA_H

#include "file_t.hpp"


#include <iostream>
#include <vector>
#include <string>


/**
 * @brief Data object. Stores a vector of values and can do basic operations with it. You can load the vector directly from a data file.
 * 
 * @tparam T Any
 */
template <class T>
class Data
{
        friend  std::ostream&           operator<<(std::ostream&, const Data&);  

public:
                                        Data(const char *, const int, const char * = "");   // file_path, file_column and data_name
                                        Data(const Data<T>&);                                  // copy constructor
                                        ~Data();

    // setter / getter
                Data&                   set_data(const char *, const int, const int = 0);
                Data&                   set_name(const char * name = "")                {Data::name = std::string(name); return *this;};
                
        const   std::vector<T>          get_data()                              const   {return Data::data;};        
        const   std::string             get_name()                              const   {return Data::name;}; 

        const   void                    describe()                              const;
        const   void                    head(const int = 5)                     const;
        const   int                     size()                                  const   {return Data::data.size();};
        const   T&                      at(const int i)                         const   {return Data::data.at(i);};
                Data&                   add(const T& element)                           {Data::data.push_back(element); return *this;};
                Data&                   replace(const T& value, const int i)            {Data::data.at(i) = value; return *this;};

    // operators
                Data&                   operator+   (const Data&);
                Data&                   operator-   (const Data&);
                Data&                   operator*   (const double);                                 // multiply by a scalar
                Data&                   operator*   (const int); 
                bool                    operator==  (const Data&);
                bool                    operator!=  (const Data& itself)                {return !(*this == itself);};
                T&                      operator[]  (int n)                             {Data::at(n);}

    // statistical functions

        const   T&                      mean()                                  const;
        const   T&                      std()                                   const;
        const   T&                      min()                                   const;
        const   T&                      max()                                   const;

private:
                std::vector<T>          data;
                std::string             name;

};

#endif
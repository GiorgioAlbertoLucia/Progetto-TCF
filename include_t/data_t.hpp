#ifndef DATA_H
#define DATA_H

#include "file_t.hpp"
#include "fileFactory_t.hpp"

#include <string_view>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>


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
                T&                      operator[]  (int n)                             {return Data::at(n);};

    // statistical functions

        const   T                       mean()                                  const;
        const   T                       std()                                   const;
        const   T                       min()                                   const;
        const   T                       max()                                   const;

private:
                std::vector<T>          data;
                std::string             name;

};

#endif






//////////////////////////////////////////////////
//              IMPLEMENTATION                  //
//////////////////////////////////////////////////


/*  USEFUL FUNCTIONS  */

const char separator = ' ';
const int width = 6;
const int lenght = 5; 

template <typename T> void print_element(T element, const char separator, const int width, const int lenght)
{
        std::cout << std::left << std::setw(width) << std::setfill(separator) << element << "\t";
}
template <>           void print_element(double element, const char separator, const int width, const int lenght)
{
        std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << element << "\t";
}
template <>           void print_element(float element, const char separator, const int width, const int lenght)
{
        std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << element << "\t";
}



/*  FUNCTIONS FROM HEADER FILE  */  

/**
 * @brief Construct a new Data:: Data object.
 * @param file_path path of the file the data will be imported from. 
 * @param file_column column of the file the data will be imported from.
 * @param name name of the data distribution.
 */
template <class T>
                        Data<T>::Data(const char * file_path, const int file_column, const char * name)
{   
    set_name(name);
    set_data(file_path, file_column);
}
/**
 * @brief Copy Constructor. 
 * Construct a new Data:: Data object.
 * @param data 
 */
template <class T>
                        Data<T>::Data(const Data<T>& data)
{
    Data::data = data.data;
    Data::name = data.name;
}
/**
 * @brief Destroy the Data:: Data object
 */
template <class T>
                        Data<T>::~Data()
{

}

// setter and getter
/**
 * @brief Stores data into the data vector from a column of the file. If the first line is a string, it will be automatically set
 * as the name of the Data object.
 * @param file_path 
 * @param file_column 
 * @return Data& 
 */
template <class T>
Data<T>&                Data<T>::set_data(const char * file_path, const int file_col, const int err_col)
{
    FileFactory * factory = new FileFactory();

    if(Data::name == "" && factory->firstline_is_text(file_path))
    {
        Data::data = factory->vector_column<T>(file_path, file_col, 1);
        Data::name = factory->get_element(file_path, 0, file_col);
    }
    else if(factory->firstline_is_text(file_path))  Data::data = factory->vector_column<T>(file_path, file_col, 1);
    else                                            Data::data = factory->vector_column<T>(file_path, file_col, 0); 
    
    delete factory;
    return *this;  
}
/**
 * @brief Stores data into the data vector from a column of the file. If the first line is a string, it will be automatically set
 * as the name of the Data object.
 * @param file_path 
 * @param file_column 
 * @return Data& 
 */
/*
template <>
template <typename T2>
Data<Udouble<T2>>&       Data<Udouble<T2>>::set_data(const char * file_path, const int file_col, const int err_col)
{
    FileFactory * factory = new FileFactory();

    if(Data::name == "" && factory->firstline_is_text(file_path))
    {
        Data::data = factory->vector_column<Udouble>(file_path, file_col, 1, err_col);
        Data::name = factory->get_element(file_path, 0, file_col);
    }
    else if(factory->firstline_is_text(file_path))  Data::data = factory->vector_column<Udouble>(file_path, file_col, 1, err_col);
    else                                            Data::data = factory->vector_column<Udouble>(file_path, file_col, 0, err_col); 
    
    delete factory;
    return *this;  
}
*/



/**
 * @brief Prints mean, std, min and max of the Data column
 * 
 * @tparam T 
 */
template <class T>
const void              Data<T>::describe() const
{
    print_element(' ', width, separator, lenght);
    print_element(Data::name, width, separator, lenght);
    std::cout << std::endl;

    print_element("Mean:", width, separator, lenght);
    print_element(Data::mean(), width, separator, lenght);
    std::cout << std::endl;

    print_element("Std:", width, separator, lenght);
    print_element(Data::std(), width, separator, lenght);
    std::cout << std::endl;

    print_element("Min:", width, separator, lenght);
    print_element(Data::min(), width, separator, lenght);
    std::cout << std::endl;

    print_element("Max:", width, separator, lenght);
    print_element(Data::max(), width, separator, lenght);
    std::cout << std::endl;

}
/**
 * @brief Prints first n entries of the data column
 * 
 * @tparam T 
 * @param n 
 */
template <class T>
const void              Data<T>::head(const int n) const
{
    print_element(' ', width, separator, lenght);
    print_element(Data::name, width, separator, lenght);
    std::cout << std::endl;

    for(int i = 0; i < n; i++)  
    {
        print_element(i, width, separator, lenght);
        print_element(Data::data[i], width, separator, lenght);
        std::cout << std::endl;
    }
}




// operators

template <class T>
Data<T>&                Data<T>::operator+(const Data<T>& data2)
{
    if (Data::data.size() != data2.data.size())   std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    else                                          std::transform(Data::data.begin(), Data::data.end(), data2.data.begin(), Data::data.begin(), std::plus<T>());
    
    return *this;
}
template <class T>
Data<T>&                Data<T>::operator-(const Data<T>& data2)
{
    if (Data::data.size() != data2.data.size())   std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    else                                          std::transform(Data::data.begin(), Data::data.end(), data2.data.begin(), Data::data.begin(), std::minus<T>());
    
    return *this;
}
template <class T>
Data<T>&                Data<T>::operator*(const double scalar)
{
    for (std::vector<double>::iterator i = Data::data.begin(); i != Data::data.end(); i++)    *i = *i * scalar;
    return *this;
}
template <class T>
Data<T>&                Data<T>::operator*(const int scalar)
{
    for (std::vector<double>::iterator i = Data::data.begin(); i != Data::data.end(); i++)    *i = *i * scalar;
    return *this;
}

template <class T>
bool                    Data<T>::operator==(const Data<T>& data2)
{
    if (Data::size() != data2.size())
    {
        std::cerr << "Warning: size of the two vector is not the same." << std::endl;
        return false;
    }   
    else
    {
        if (Data::data == data2.data)                   return true;
        else                                            return false;
    }
}


// statistical functions

/**
 * @brief Returns the mean value of stored distribution.
 * @return double 
 */
template <class T>
const T                 Data<T>::mean()                                                         const
{
    T sum = std::accumulate(Data::data.begin(), Data::data.end(), 0.0);
    T mean = sum / Data::size();
    return mean;
}
/**
 * @brief Returns the standard deviation of stored distribution.
 * @return double 
 */
template <class T>
const T                 Data<T>::std()                                                          const
{
    std::vector<T> num_terms;
    for (typename std::vector<T>::const_iterator i = Data::data.begin(); i != Data::data.end(); i++)     num_terms.push_back(pow(*i - Data::mean(), 2));
    T num = std::accumulate(num_terms.begin(), num_terms.end(), 0.0);
    T std = sqrt(num / Data::size());
    
    return std;
}
/**
 * @brief Returns the minimum value of stored distribution.
 * @return double 
 */
template <class T>
const T                 Data<T>::min()                                                        const
{
    T min = Data::data.front();
    for (typename std::vector<T>::const_iterator i = Data::data.begin(); i != Data::data.end(); i++)
    {
        if (min > *i)   min = *i;
    }
    return min;
}
/**
 * @brief Returns the maximum value of stored distribution.
 * @return double 
 */
template <class T>
const T                 Data<T>::max()                                                      const
{
    T max = Data::data.front();
    for (typename std::vector<T>::const_iterator i = Data::data.begin(); i != Data::data.end(); i++)
    {
        if (max < *i)   max = *i;
    }
    return max;
}




// friend functions

template <class T>
std::ostream&       operator<<(std::ostream& out, const Data<T>& data)
{
    std::vector<double> storing_data = data.get_data();

    out << "Print: " << data.get_name() << std::endl;
    for (typename std::vector<T>::const_iterator i = storing_data.begin(); i != storing_data.end(); i++)
    {
        out << *i << std::endl;
    }

    return out;
}

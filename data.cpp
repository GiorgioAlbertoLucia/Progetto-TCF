#include "data.h"
#include "fileFactory.h"

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

/*  USEFUL FUNCTIONS  */



/*  FUNCTIONS FROM HEADER FILE  */  

/**
 * @brief Construct a new Txt Data:: Txt Data object.
 * @param file_path path of the file the data will be imported from. 
 * @param file_column column of the file the data will be imported from.
 * @param name name of the data distribution.
 */
                    Data::Data(const char * file_path, const int file_column, const char * name)
{   
    set_file(file_path);
    set_name(name);
    set_data(file_path, file_column);
}

/**
 * @brief Copy Constructor. 
 * Construct a new Txt Data:: Txt Data object.
 * @param data 
 */
                    Data::Data(const Data& data)
{
    Data::data_vector = data.data_vector;
    Data::name = data.name;
}

/**
 * @brief Destroy the Txt Data:: Txt Data object
 */
                    Data::~Data()
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
Data&               Data::set_data(const char * file_path, const int file_column)
{
    FileFactory * factory = new FileFactory();
    File * file = factory->create_file(file_path);  // new file

    if (file_column < file->count_column())
    {
        if(file->check_words())
        {
            Data::data_vector = file->get_column(file_column, 1);
            Data::name = file->get_element(file_column, 0);
            Data::entries = file->get_entries() - 1;
        }
        else   
        {
            Data::data_vector = file->get_column(file_column);
            Data::entries = file->get_entries();
        } 
        
    }
    else    std::cerr << "Error: file only contains " << file->count_column() << " columns." << std::endl;

    delete factory;
    delete file;
    return *this;  
}

std::vector<double> Data::get_data()                                                     const
{
    return Data::data_vector;
}

/**
 * @brief Sets the name of the Data object. The first condition will skip the operation if the inserted name is 0
 * (it will come in handy in the constructor).
 * @param name name of the Data object. 
 * @return Data& 
 */
Data&               Data::set_name(const char * name = 0)
{
    if (name == 0)  return *this;
    Data::name = name;
    return *this;
}

std::string         Data::get_name()                                                     const
{
    return Data::name;
}

/**
 * @brief Sets the file (choosing a path) from which you want to import data.
 * @param const_char_* file_path: path to the file.
 * @return Data&
 */
Data&               Data::set_file(const char * file_path)
{
    Data::file_path = file_path;
    return *this;
}

/**
 * @brief Gets the TxtFile where data is stored.
 * @returns TxtFile
 */
std::string         Data::get_file()                                                       const
{
    return Data::file_path;
}

/**
 * @brief Returns the number of entries in the data vector
 * 
 * @return int 
 */
int                 Data::get_entries()                                                     const
{
    return Data::entries;
}



Data&               Data::add_element(const double element)             
{
    Data::data_vector.push_back(element);
    return *this;
}

/**
 * @brief Replaces an element of stored distribution with given value.
 * @param new_element new replacing value.
 * @param position position of the element you want to swap new_element with.
 */
Data&               Data::replace_element(const double new_element, const int position)
{
    Data::data_vector.at(position) = new_element;
    return *this;
}


// operators

Data&               Data::operator+(const Data& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (Data::data_vector.size() != vector2.size())
    {
        std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    }
    else
    {
        std::transform(Data::data_vector.begin(), Data::data_vector.end(), vector2.begin(),
                        Data::data_vector.begin(), std::plus<double>() );
    }
    return *this;
}

Data&               Data::operator-(const Data& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (Data::data_vector.size() != vector2.size())
    {
        std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    }
    else
    {
        std::transform(Data::data_vector.begin(), Data::data_vector.end(), vector2.begin(),
                        Data::data_vector.begin(), std::plus<double>() );
    }
    return *this;
}

Data&               Data::operator*(const double scalar)
{
    for (std::vector<double>::iterator i = Data::data_vector.begin(); i != Data::data_vector.end(); i++)
    {
        *i = *i * scalar;
    }
    return *this;
}

Data&               Data::operator*(const int scalar)
{
    for (std::vector<double>::iterator i = Data::data_vector.begin(); i != Data::data_vector.end(); i++)
    {
        *i = *i * scalar;
    }
    return *this;
}

bool                Data::operator==(const Data& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (Data::data_vector.size() != vector2.size())
    {
        std::cerr << "Warning: size of the two vector is not the same." << std::endl;
        return false;
    }
    else
    {
        if (Data::data_vector == vector2)    return true;
        else                                    return false;
    }
}


// statistical functions

/**
 * @brief Returns the mean value of stored distribution.
 * @return double 
 */
double              Data::mean()                                                         const
{
    double sum = std::accumulate(Data::data_vector.begin(), Data::data_vector.end(), 0.0);
    double mean = sum / Data::data_vector.size();
    return mean;
}

/**
 * @brief Returns the standard deviation of stored distribution.
 * @return double 
 */
double              Data::std()                                                          const
{
    std::vector<double> difference(Data::data_vector.size());
    std::transform(Data::data_vector.begin(), Data::data_vector.end(), difference.begin(),
                    std::bind2nd(std::minus<double>(), mean()) );
    double squared_sum = std::inner_product(difference.begin(), difference.end(), difference.begin(), 0.0);
    double std = sqrt(squared_sum / Data::data_vector.size());
    return std;
}

/**
 * @brief Returns the minimum value of stored distribution.
 * @return double 
 */
double              Data::get_min()                                                      const
{
    double min = Data::data_vector.front();
    for (std::vector<double>::const_iterator i = Data::data_vector.begin(); i != Data::data_vector.end(); i++)
    {
        if (min > *i)   min = *i;
    }
    return min;
}

/**
 * @brief Returns the maximum value of stored distribution.
 * @return double 
 */
double              Data::get_max()                                                      const
{
    double max = Data::data_vector.front();
    for (std::vector<double>::const_iterator i = Data::data_vector.begin(); i != Data::data_vector.end(); i++)
    {
        if (max < *i)   max = *i;
    }
    return max;
}

/**
 * @brief Returns an element of stored distribution.
 * @param index: position of the element in the vector. First position is 0.
 * @return double 
 */
double              Data::get(const int index)                                           const
{
    double value = Data::data_vector.at(index);
    return value;
}



// friend functions

std::ostream&       operator<<(std::ostream& out, const Data& data)
{
    std::vector<double> storing_data = data.get_data();

    out << "Print: " << data.get_name() << std::endl;
    for (std::vector<double>::const_iterator i = storing_data.begin(); i != storing_data.end(); i++)
    {
        out << *i << std::endl;
    }

    return out;
}
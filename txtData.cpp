#include "txtFile.h"
#include "txtData.h"

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
                    TxtData::TxtData(const char * file_path, const int file_column, const char * name):TxtFile(file_path)
{   
    set_file(file_path);
    set_name(name);
    set_data(file_path, file_column);
}

/**
 * @brief Copy Constructor. 
 * Construct a new Txt Data:: Txt Data object.
 * @param txt_data 
 */
                    TxtData::TxtData(const TxtData& txt_data):TxtFile(txt_data.get_path())
{
    TxtData::data_vector = txt_data.data_vector;
    TxtData::name = txt_data.name;
}

/**
 * @brief Destroy the Txt Data:: Txt Data object
 */
                    TxtData::~TxtData()
{

}


// setter and getter

/**
 * @brief Sets the .txt file from which you want to import data.
 * @param const_char_* file_path: path to the file.
 * @return TxtData&
 */
TxtData&            TxtData::set_file(const char * file_path)
{
    set_path(file_path);
    return *this;
}

/**
 * @brief Gets the TxtFile where data is stored.
 * @returns TxtFile
 */
TxtFile             TxtData::get_file()                                                     const
{
    TxtFile txt_file(get_path());
    return txt_file;
}

void                TxtData::set_data(const char * file_path, const int file_column)
{
    set_file(file_path);
    TxtData::data_vector = get_file().get_column(file_column);   
}

std::vector<double> TxtData::get_data()                                                     const
{
    return TxtData::data_vector;
}

void                TxtData::set_name(const char * name)
{
    std::string str(name);
    TxtData::name = str;
}

std::string         TxtData::get_name()                                                     const
{
    return TxtData::name;
}



void                TxtData::add_element(const double element)             
{
    TxtData::data_vector.push_back(element);
}

/**
 * @brief Replaces an element of stored distribution with given value.
 * @param new_element new replacing value.
 * @param position position of the element you want to swap new_element with.
 */
void                TxtData::replace_element(const double new_element, const int position)
{
    TxtData::data_vector.at(position) = new_element;
}


// operators

TxtData&            TxtData::operator+(const TxtData& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (TxtData::data_vector.size() != vector2.size())
    {
        std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    }
    else
    {
        std::transform(TxtData::data_vector.begin(), TxtData::data_vector.end(), vector2.begin(),
                        TxtData::data_vector.begin(), std::plus<double>() );
    }
    return *this;
}

TxtData&            TxtData::operator-(const TxtData& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (TxtData::data_vector.size() != vector2.size())
    {
        std::cerr << "Error: unable to do the operation. Size of the two vector is not the same." << std::endl;
    }
    else
    {
        std::transform(TxtData::data_vector.begin(), TxtData::data_vector.end(), vector2.begin(),
                        TxtData::data_vector.begin(), std::plus<double>() );
    }
    return *this;
}

TxtData&            TxtData::operator*(const double scalar)
{
    for (std::vector<double>::iterator i = TxtData::data_vector.begin(); i != TxtData::data_vector.end(); i++)
    {
        *i = *i * scalar;
    }
    return *this;
}

TxtData&            TxtData::operator*(const int scalar)
{
    for (std::vector<double>::iterator i = TxtData::data_vector.begin(); i != TxtData::data_vector.end(); i++)
    {
        *i = *i * scalar;
    }
    return *this;
}

bool                TxtData::operator==(const TxtData& data2)
{
    std::vector<double> vector2 = data2.get_data();
    if (TxtData::data_vector.size() != vector2.size())
    {
        std::cerr << "Warning: size of the two vector is not the same." << std::endl;
        return false;
    }
    else
    {
        if (TxtData::data_vector == vector2)    return true;
        else                                    return false;
    }
}


// statistical functions

/**
 * @brief Returns the mean value of stored distribution.
 * @return double 
 */
double              TxtData::mean()                                                         const
{
    double sum = std::accumulate(TxtData::data_vector.begin(), TxtData::data_vector.end(), 0.0);
    double mean = sum / TxtData::data_vector.size();
    return mean;
}

/**
 * @brief Returns the standard deviation of stored distribution.
 * @return double 
 */
double              TxtData::std()                                                          const
{
    std::vector<double> difference(TxtData::data_vector.size());
    std::transform(TxtData::data_vector.begin(), TxtData::data_vector.end(), difference.begin(),
                    std::bind2nd(std::minus<double>(), mean()) );
    double squared_sum = std::inner_product(difference.begin(), difference.end(), difference.begin(), 0.0);
    double std = sqrt(squared_sum / TxtData::data_vector.size());
    return std;
}

/**
 * @brief Returns the minimum value of stored distribution.
 * @return double 
 */
double              TxtData::get_min()                                                      const
{
    double min = TxtData::data_vector.front();
    for (std::vector<double>::const_iterator i = TxtData::data_vector.begin(); i != TxtData::data_vector.end(); i++)
    {
        if (min > *i)   min = *i;
    }
    return min;
}

/**
 * @brief Returns the maximum value of stored distribution.
 * @return double 
 */
double              TxtData::get_max()                                                      const
{
    double max = TxtData::data_vector.front();
    for (std::vector<double>::const_iterator i = TxtData::data_vector.begin(); i != TxtData::data_vector.end(); i++)
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
double              TxtData::get(const int index)                                           const
{
    double value = TxtData::data_vector.at(index);
    return value;
}



// friend functions

std::ostream&       operator<<(std::ostream& out, const TxtData& data)
{
    std::vector<double> storing_data = data.get_data();

    out << "Print: " << data.get_name() << std::endl;
    for (std::vector<double>::const_iterator i = storing_data.begin(); i != storing_data.end(); i++)
    {
        out << *i << std::endl;
    }

    return out;
}
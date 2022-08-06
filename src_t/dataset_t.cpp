#include "../include_t/data_t.hpp"
#include "../include_t/dataset_t.hpp"

#include "../include_t/fileFactory_t.hpp"

#include <iostream>
#include <vector>
#include <string>

// USEFUL FUNCTIONS

const char separator = ' ';
const int width = 6; 

template <typename T> void print_element(T element, const char separator, const int width)
{
    cout << std::left << std::setw(width) << std::setfill(separator) << T;
}




/**
 * @brief Construct a new Dataset:: Dataset object
 * @param file_path 
 * @param first_column 
 */
template <class T>
                        Dataset<T>::Dataset(const char * file_path, const int first_column, const char * label)
{
    Dataset::fill(file_path, first_column);
}
/**
 * @brief Construct a new Dataset:: Dataset object
 * @param file_path 
 * @param first_column 
 */
template <class T>
                        Dataset<T>::Dataset(std::string file_path, const int first_column, const char * label)
{
    const char * char_path = file_path.c_str();
    Dataset::fill(char_path, first_column);
}
/**
 * @brief (Copy constructor) Construct a new Dataset:: Dataset object
 * 
 * @param dataset_object 
 */
template <class T>
                        Dataset<T>::Dataset(const Dataset<T>& dataset_object)
{
    Dataset::dataset = dataset_object.dataset;
    Dataset::columns = dataset_object.columns;
}
/**
 * @brief Destroy the Dataset:: Dataset object
 * 
 */
template <class T>
                        Dataset<T>::~Dataset()
{

}




/**
 * @brief Prints mean, std, min and max for each Data column
 * 
 * @tparam T 
 */
template <class T>
const void              Dataset<T>::describe()                                                      const
{

    print_element(' ', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->name, width, separator); 
    std::cout << std::endl;

    print_element('Mean:', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->mean(), width, separator);
    std::cout << std::endl;

    print_element('Std Dev:', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->std(), width, separator);
    std::cout << std::endl;

    print_element('Min:', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->min(), width, separator);
    std::cout << std::endl;

    print_element('Max:', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->max(), width, separator);
    std::cout << std::endl;

}
/**
 * @brief Prints first n entries of each data column
 * 
 * @tparam T 
 * @param n 
 */
template <class T>
const void              Data<T>::head(const int n) const
{
    print_element(' ', width, separator);
    for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->name, width, separator);
    std::cout << std::endl;

    for(int j = 0; j < n; j++)  
    {
        print_element(i, width, separator);
        for(std::vector<T>::const_iterator i = data.begin(); i != data.end(); i++)  print_element(*i->data[j], width, separator);
        std::cout << std::endl;
    }
}
/**
 * @brief Creates a dataset containing Data object. Each object is a data vector filled with elements from a column of a file
 * and its name is directly imported from the file (this is done only if the first line of the file is a string). Sets the
 * number of entries in the file.
 * @param file_path 
 * @param first_column column from which you want to import the file
 * @returns Dataset&
 */
template <class T>
Dataset<T>&             Dataset<T>::fill(const char * file_path, const int first_column)  
{
    FileFactory * factory = new FileFactory();
    File * file = factory->create_file(file_path);

    for (int i = first_column; i < file->get_columns(); i++)
    {
        Data<T> d(file_path, i);
        Dataset::data.push_back(d);
    }
        
    delete factory;
    delete file;
    return *this;
}
/**
 * @brief Appends a Dataset object to the current one.
 * 
 * @tparam T 
 * @param dataset 
 * @return Dataset<T>& 
 */
template <class T>
Dataset<T>&             Dataset<T>::concatenate(const Dataset<T>& dataset)
{
    Dataset<T>::data.insert(Dataset<T>::data.end(), dataset.data.begin(), dataset.data.end());
    Dataset<T>::columns.insert(Dataset<T>::columns.end(), dataset.columns.begin(), dataset.columns.end());
}
/**
 * @brief Adds an element to the dataset vector.
 * @param data 
 * @return Dataset& 
 */
template <class T>
Dataset<T>&             Dataset<T>::add(const Data<T>& d)
{
    Dataset::data.push_back(d);
    return *this;
}
/**
 * @brief Removes all the elements with given name from the dataset vector.
 * @param name
 * @return Dataset& 
 */
template <class T>
Dataset<T>&             Dataset<T>::remove(const char * name)
{
    std::vector<Data<T>>::const_iterator it = std::find(Dataset<T>::columns.begin(), Dataset<T>::columns.end(), name);
    if(it != Dataset<T>::columns.end())
    {
        const int index = std::distance(Dataset<T>::columns.begin(), it);
        Dataset<T>::data.erase(index);
    }
    std::cerr << "Error: there is no element with name " << name << "." << std::endl;
    return *this;
}


// FRIEND FUNCTIONS

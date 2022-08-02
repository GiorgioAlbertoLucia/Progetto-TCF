#ifndef DATASET_H
#define DATASET_H

#include "../include_t/data_t.hpp"

#include <vector>
#include <string>

/**
 * @brief Class prototype. The final class will be a class template.
 * It is recommended to import data from a file having names of the observables in the first line and it is better if 
 * none of them have the same name.
 */

template <class T>
class Dataset
{
    friend  std::ostream&           operator<<(std::ostream&, const Dataset&);
            Data<T>&                operator[](const char * column)                 {return Dataset::data[find(Dataset::columns.begin(), Dataset::columns.end(), column)]};

public:
                                    Dataset(const char *, const int = 0, const char * = "");     // file_path, first_column
                                    Dataset(std::string, const int = 0, const char * = "");  
                                    Dataset(const Dataset&);
                                    ~Dataset();
            
            std::vector<Data<T>>    get_dataset()                           const;
            Data<T>                 get_data(const int)                     const;
            Data<T>                 get_data(const char *)                  const;
            int                     get_entries()                           const;

            Dataset<T>&             fill(const char *, const int = 0);
            Dataset<T>&             concatenate(const Dataset<T>);
            Dataset<T>&             add(const Data<T>);
            Dataset<T>&             remove(const char *);

            Data<T>&                operator[](const char * column)                         {return data[find(columns.begin(), columns.end(), column)]};

private:
    std::vector<Data<T>>            data;
    std::vector<std::string>        columns;
};

#endif
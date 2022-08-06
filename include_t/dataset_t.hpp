#ifndef DATASET_H
#define DATASET_H

#include "../include_t/data_t.hpp"

#include <vector>
#include <string>


/**
 * @brief Dataset object. Stores a vector of Data. You can load a dataset from a file and inspect it with this class.
 * 
 * @tparam T Any
 */
template <class T>
class Dataset
{           

public:
                                    Dataset(const char *, const int = 0, const char * = "");     // file_path, first_column
                                    Dataset(std::string, const int = 0, const char * = "");  
                                    Dataset(const Dataset&);
                                    ~Dataset();
            
            std::vector<Data<T>>    get_dataset()                           const           {return data};
            Data<T>                 get_data(const int)                     const           {return data.at(i)};
            Data<T>                 get_data(const char *)                  const           {return data[find(columns.begin(), columns.end(), column)]};

            const   void            describe()                              const;
            const   void            head(const int = 5)                     const;
            int                     size()                                  const           {return data.size()};
            Dataset<T>&             fill(const char *, const int = 0);
            Dataset<T>&             concatenate(const Dataset<T>&);
            Dataset<T>&             add(const Data<T>&);
            Dataset<T>&             remove(const char *);

            Data<T>&                operator[](const char * column)                         {return data[find(columns.begin(), columns.end(), column)]};
            Data<T>&                operator[](const int * column)                          {return data.at(column)};

private:
    std::vector<Data<T>>            data;
    std::vector<std::string>        columns;
};

#endif
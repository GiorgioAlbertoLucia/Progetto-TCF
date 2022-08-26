#ifndef DATASET_H
#define DATASET_H

#include "../include/data.hpp"

#include <vector>
#include <string>

/**
 * @brief Class prototype. The final class will be a class template.
 * It is recommended to import data from a file having names of the observables in the first line and it is better if 
 * none of them have the same name.
 */
class Dataset
{
    friend  std::ostream&           operator<<(std::ostream&, const Dataset&);

public:
                                    Dataset(const char *, const int = 0, const char * = "");     // file_path, first_column
                                    Dataset(std::string, const int = 0, const char * = "");  
                                    Dataset(const Dataset&);
                                    ~Dataset();
            
            std::vector<Data>       get_dataset()                           const;
            Data                    get_data(const int)                     const;
            Data                    get_data(const char *)                  const;
            int                     get_entries()                           const;

            Dataset&                fill(const char *, const int = 0);
            Dataset&                add(const Data);
            Dataset&                remove(const int);
            Dataset&                remove(const char *);

private:
    std::vector<Data>               dataset;
    int                             entries;
    std::vector<int>                data_entries;   // entries for each Data object ()
    std::string                     label;
};

#endif
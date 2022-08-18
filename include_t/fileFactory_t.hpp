#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <string>
#include <fstream>

#include "../include_t/txtFile_t.hpp"
#include "../include_t/csvFile_t.hpp"

//#include "../include_t/udouble_t.hpp"

/**
 * @brief Class factory for classes derived from File. 
 * 
 */
class FileFactory
{
public:
    
    std::string                                     get_element(const char *, const int, const int) const;
    template <typename T> std::vector<T>&           vector_column(const char *, const int, const int = 0, const int = 0);
    template <typename T> void                      append_column(const char *, const std::vector<T>&, const char * = "") const;
    bool                                            firstline_is_text(const char *) const;

    TxtFile *                                       create_txt(const char *)  const;
    CsvFile *                                       create_csv(const char *)  const;

    File *                                          create_file(const char *) const;

};

#endif

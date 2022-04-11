#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <string>
#include <fstream>

#include "txtFile.hpp"
#include "csvFile.hpp"

/**
 * @brief Class factory that creates TxtFile and CsvFile. In this way, the client can choose, for instance, by checking the extension
 * of the input file. 
 * 
 */
class FileFactory
{
public:
    TxtFile *   create_txt(const char *)  const;
    CsvFile *   create_csv(const char *)  const;

    File *      create_file(const char *) const;
};

#endif

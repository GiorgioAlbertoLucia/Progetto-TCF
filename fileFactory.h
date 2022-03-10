#ifndef FILEFACTORY_H
#define FILEFACTORY_H

#include <string>
#include <fstream>

#include "txtFile.h"
#include "csvFile.h"

/**
 * @brief Class factory that creates TxtFile and CsvFile. In this way, the client can choose, for instance, by checking the extension
 * of the input file. 
 * 
 */
class FileFactory
{
public:
    TxtFile *   create_txt(const char * file_path)  const  {return new TxtFile(file_path);};
    CsvFile *   create_csv(const char * file_path)  const  {return new CsvFile(file_path);};

    File *      create_file(const char *)           const;
    int         count_column(const char *)          const;
};

/**
 * @brief Factory method that reads the extension of the chosen file and then creates the appropiate File object.
 * @param file_path data file path.
 * @return File* 
 */
File *          FileFactory::create_file(const char * file_path)   const
{
    std::string filepath(file_path);
    std::string::size_type idx;
    idx = filepath.rfind('.');

    if (idx != std::string::npos)
    {
        std::string extension = filepath.substr(idx+1);

        if (extension == "txt")         FileFactory::create_txt(file_path);
        else if (extension == "csv")    FileFactory::create_csv(file_path);
    }   
    else                                
    {
        std::cerr << "Error: no extension found." << std::endl;
        return 0;
    }    
}

#endif

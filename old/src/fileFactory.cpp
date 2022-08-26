#include <string>
#include <fstream>

#include "../include/fileFactory.hpp"
#include "../include/txtFile.hpp"
#include "../include/csvFile.hpp"

/**
 * @brief Create a TxtFile object
 * 
 * @param file_path 
 * @return TxtFile* 
 */
TxtFile *       FileFactory::create_txt(const char * file_path)                 const  
{
    return new TxtFile(file_path);
}
/**
 * @brief Create a CsvFile object
 * 
 * @param file_path 
 * @return CsvFile* 
 */
CsvFile *       FileFactory::create_csv(const char * file_path)                 const  
{
    return new CsvFile(file_path);
}

/**
 * @brief Factory method that reads the extension of the chosen file and then creates the appropiate File object.
 * @param file_path data file path.
 * @return File* 
 */
File *          FileFactory::create_file(const char * file_path)                const
{
    std::string filepath(file_path);
    std::string::size_type idx;
    idx = filepath.rfind('.');

    if (idx != std::string::npos)
    {
        std::string extension = filepath.substr(idx+1);

        if (extension == "txt")         return FileFactory::create_txt(file_path);
        else if (extension == "csv")    return FileFactory::create_csv(file_path);
    }   
    std::cerr << "Error: no extension found. A TxtFile object initialized to an empty file will be returned." << std::endl;
    return FileFactory::create_txt("empty.txt");
}

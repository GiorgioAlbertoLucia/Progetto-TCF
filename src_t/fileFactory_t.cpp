#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "../include_t/fileFactory_t.hpp"
#include "../include_t/txtFile_t.hpp"
#include "../include_t/csvFile_t.hpp"

//#include "../include_t/udouble_t.hpp"


/* MEMBER FUNCTIONS */

/**
 * @brief Returns a element from a file (automatically skips all comment). The returned element is a string. Will be 
 * used mainly to get the names of columns in data files.
 * @param file_path 
 * @param col 
 * @param row 
 * @return std::string 
 */
std::string                 FileFactory::get_element(const char * file_path, const int row, const int col) const
{
    File * file = this->create_file(file_path);
    std::fstream f(file->get_path(), std::ios::in);
    std::string str;

    // skip comment
    int first_line = file->comment_lines();
    for(int i=0; i<first_line; i++) f.ignore(10000, '\n'); 

    if(row >= file->get_rows())
    {
        std::cerr << "Error: line " << row << " does not exist. The file has " << file->get_rows() << " lines." << std::endl;
        return 0;
    }

    if(f.is_open())
    {   
        for(int i=0; i<=row; i++) getline(f, str); 
        f.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;

    std::vector<std::string> words = split_words(str);
    return words.at(col);
}


bool                        FileFactory::firstline_is_text(const char * file_path) const
{
    File * file = this->create_file(file_path);
    std::fstream f(file->get_path(), std::ios::in);

    // skip comment
    int first_line = file->comment_lines();
    for(int i=0; i<first_line; i++) f.ignore(10000, '\n');

    std::string line;
    getline(f, line);

    f.close();
    delete file;
    return check_words(line);
}



/**
 * @brief Create a TxtFile object
 * 
 * @param file_path 
 * @return TxtFile* 
 */
TxtFile *                   FileFactory::create_txt(const char * file_path)                 const  
{
    return new TxtFile(file_path);
}
/**
 * @brief Create a CsvFile object
 * 
 * @param file_path 
 * @return CsvFile* 
 */
CsvFile *                   FileFactory::create_csv(const char * file_path)                 const  
{
    return new CsvFile(file_path);
}

/**
 * @brief Factory method that reads the extension of the chosen file and then creates the appropiate File object.
 * @param file_path data file path.
 * @return File* 
 */
File *                      FileFactory::create_file(const char * file_path)                const
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

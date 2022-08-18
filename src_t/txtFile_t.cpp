#include "../include_t/file_t.hpp"
#include "../include_t/txtFile_t.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

/* USEFUL FUNCTIONS */



/* FUNCTIONS FROM HEADER FILE */



/**
 * @brief Construct a new Txt File:: Txt File object.
 * @param file_path 
 */
                            TxtFile::TxtFile(const char * file_path)
{
    // creates an empty .txt file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
    std::ofstream file;
    file.open(file_path, std::ios::app);
    file.close();

    set_path(file_path);
}
/**
 * @brief Construct a new Txt File:: Txt File object. Alternative constructor taking string as an input.
 * 
 * @param str_file_path 
 */
                            TxtFile::TxtFile(std::string str_file_path)
{
    // creates an empty .txt file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
    const char * file_path = str_file_path.c_str();

    std::ofstream file;
    file.open(file_path, std::ios::app);
    file.close();

    set_path(file_path);
}
/**
 * @brief Copy constructor.
 * Construct a new Txt File:: Txt File object.
 * @param txt_file 
 */
                            TxtFile::TxtFile(const TxtFile& txt_file)
{
    TxtFile::file_path = txt_file.file_path;
    TxtFile::rows = txt_file.rows;
    TxtFile::columns = txt_file.columns;
}
/**
 * @brief Destroy the Txt File:: Txt File object
 */
                            TxtFile::~TxtFile()
{

}


// setter and getter
/**
 * @brief Sets the file path and automatically sets the number of rows and columns
 * @param filepath complete path to the file
 */
void                        TxtFile::set_path(const char * file_path)
{
    TxtFile::file_path = std::string(file_path);
    TxtFile::rows = TxtFile::n_rows();
    TxtFile::columns = TxtFile::n_columns();
}


int                         TxtFile::n_rows()                           const
{
    std::ifstream file(TxtFile::file_path);
    int rows = 0;

    // skip comment
    int first_line = comment_lines();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(file.is_open())
    {
    // count entries
    std::string line;
    while(getline(file, line))  rows++;
    file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
    return rows;
}
/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * If different lines of the file have a different amount of columns, an error is displayed.
 * @return int number of columns.
 */
int                         TxtFile::n_columns()                        const
{
    int columns = 0;
    int save_columns = 0;       // used to check if each line has the same number of columns

    std::ifstream file(TxtFile::file_path);

    // skip comment
    int first_line = comment_lines();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(file.is_open())
    {   
        for (int j = 0; j < TxtFile::rows; j++)
        {
            std::string row, item;
            getline(file, row);
            std::istringstream iss(row);
            while(iss >> item)   if(item.length())  columns++;

            if (j > 0 && columns != save_columns)
            {
                std::cerr << "Error: not all the lines have the same amount of columns. First " << j << " lines have "
                << save_columns << " columns (this value will be returned)." << std::endl;
                return save_columns;
            }
            
            save_columns = columns;
            columns = 0;
        }
    }
    return save_columns;
}




/**
 * @brief Clear content inside your file
 * 
 */
void                        TxtFile::clear()
{
    std::fstream file;
    file.open(TxtFile::file_path, std::ios::out | std::ios::trunc);
    file.close();
}
/**
* @returns number of lines containing comments
*/
int                         TxtFile::comment_lines()                         const
{
    int comment = 0;
    std::string line;
    std::ifstream file(TxtFile::file_path);
    if(file.is_open())  while(file >> line) if(line.at(0)=='#') comment++;
    file.close();
    return comment;
}

// friend functions
std::ostream&               operator<<  (std::ostream& out, const TxtFile& txt_file)
{
    std::ifstream file;
    file.open(txt_file.file_path);
    if(file.is_open())
    {
        out << "Print " << txt_file.file_path << ": " << std::endl;
        while (!file.eof())
        {
            std::string this_line;
            getline(file, this_line);
            out << this_line << std::endl;
        }

        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;

    return out;
}

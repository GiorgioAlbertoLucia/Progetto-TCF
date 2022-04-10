#include "file.h"
#include "txtFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstddef>

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
    set_entries(file_path);
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
    set_entries(file_path);
}

/**
 * @brief Copy constructor.
 * Construct a new Txt File:: Txt File object.
 * @param txt_file 
 */
                            TxtFile::TxtFile(const TxtFile& txt_file)
{
    TxtFile::file_path = txt_file.file_path;
    TxtFile::entries = txt_file.entries;
}

/**
 * @brief Destroy the Txt File:: Txt File object
 */
                            TxtFile::~TxtFile()
{

}


// setter and getter

/**
 * @brief 
 * @param file_path 
 */
void                        TxtFile::set_path(const char * file_path)
{
    std::string str(file_path);
    TxtFile::file_path = str;
}

/**
 * @brief 
 * @return std::string 
 */
std::string                 TxtFile::get_path()                             const
{
    return TxtFile::file_path;
}

void                        TxtFile::set_entries(const char * file_path)
{
    std::ifstream file;
    file.open(file_path);

    if(file.is_open())
    {
    // count entries
    TxtFile::entries = 0;
    std::string line;
    while(getline(file, line))  TxtFile::entries++;

    file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}

int                         TxtFile::get_entries()                          const
{
    return TxtFile::entries;
}


/** 
 * @brief Writes into the file, deleting all previous content.
 * @param line: line you want to write into the file.
 */ 
void                        TxtFile::write(const std::string line)          const
{
    std::ofstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {
        file << line;
        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}

/** 
 * @brief Writes into the file, keeping all previous content.
 *  @param line: line you want to append to the file.
 */ 
void                        TxtFile::append(const std::string line)         const
{
    std::ofstream file;
    file.open(TxtFile::file_path, std::ios::app);

    if(file.is_open())
    {
        file << "\n" << line;
        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}

/** 
 * @brief Writes into the file, deleting all previous content.
 * @param line: line you want to write into the file.
 */ 
void                        TxtFile::write(const char * line)               const
{
    std::string str(line);
    TxtFile::write(str);
}

/** 
 * @brief Writes into the file, keeping all previous content.
 * @param line: line you want to append to the file.
 */ 
void                        TxtFile::append(const char * line)              const
{
    std::string str(line);
    TxtFile::append(str);
}

/**
 * @brief Gets an element from the file as a string.
 * @param line 
 * @param column 
 * @return std::string 
 */
std::string                 TxtFile::get_element(const int line, const int column)  const
{
    std::string file_line = TxtFile::get_line(line);
    std::vector<std::string> words = TxtFile::split_words(file_line);
    return words.at(column);
}

/**
 * @brief Returns a line from the file. Lines are numbered beginning with zero.
 * @param line line you want to return.
 */
std::string                 TxtFile::get_line(const int line)               const
{
    std::ifstream file;
    file.open(TxtFile::file_path);

    if(line >= entries)
    {
        std::cerr << "Error: line " << line << " does not exist. The file has " << entries << " lines." << std::endl;
        return 0;
    }

    if(file.is_open())
    {   
        int i = 0;
        std::string str;
        while(i <= line) getline(file, str);        // reads all the lines until the one you need
        file.close();

        return str;
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
    return 0;
}

/** 
 * @brief  This only works with .txt files using a space (' ') or a tab as delimiter between columns. 
 * Columns are numbered beginning with zero.
 * @param column: number referring to the column you want to print.
 * @param first_row = 0: row you want to start importing from. Lines are numbered from 0.
 */
std::vector<double>         TxtFile::get_column(const int column, const int first_row)       const
{
    std::vector<double> vector;

    std::ifstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {
        int n_columns = TxtFile::count_column();
        if(column >= n_columns)
        {
            std::cerr << "Error: column " << column << " does not exist. The file has " << n_columns << " columns." << std::endl;
            return vector;
        }

        // skip lines
        std::string row;
        for(int j = 0; j < first_row; j++)  getline(file, row);
        
        int i = 0;
        while (getline(file, row))
        {   
            std::istringstream iss(row);
            double column_element;
            for(int i = 0; i <= column; i++)    iss >> column_element;
            vector.push_back(column_element);
        }
        file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;
    return vector;
}

void                        TxtFile::current_file()                         const
{
    std::cout << std::endl << "Il file attualmente in lettura è: " << TxtFile::file_path << std::endl;
}

/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * If different lines of the file have a different amount of columns, an error is displayed.
 * @return int number of columns.
 */
int                         TxtFile::count_column()                         const
{
    int columns = 0;
    int save_columns = 0;       // used to check if each line has the same number of columns

    std::ifstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {   
        for (int j = 0; j < TxtFile::entries; j++)
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
 * @brief Extract single words (elements separated by space) from a string.
 * @param input string you want to extraxt words from.
 * @return vector containing single words.
 */
std::vector<std::string>    TxtFile::split_words(const std::string input)   const
{
    std::istringstream ss(input);
    std::string word;
    std::vector<std::string> vector1;

    while(ss >> word)   vector1.push_back(word);

    return vector1;
}

/**
 * @brief Checks if the first line of the file contains words. This function is used in txtDataset.cpp to use the words in the 
 * first line as names for the TxtData objects generated.
 * NOTE: "file1" will not be regarded as a number although it does contain a digit in it. 
 * @return true if no number is present in each element of the first line.
 * @return false if a number is found in the first line.
 */
bool                        TxtFile::check_words()                          const
{
    std::ifstream file;
    file.open(TxtFile::file_path);
    if(file.is_open())
    {
        std::string first_line;
        getline(file, first_line);

        bool check = true;

        std::vector<std::string> words = TxtFile::split_words(first_line);
        for (std::vector<std::string>::const_iterator i = words.begin(); i != words.end(); i++)
        {
            std::string word = *i;
            if (word.find_first_not_of("0123456789") == std::string::npos)  return false;
        }
        file.close();
        return true;
    }
    std::cerr << "Error: unable to open file" << std::endl;
    return false;
}

// friend functions

std::ostream&       operator<<  (std::ostream& out, const TxtFile& txt_file)
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

#include "file.h"
#include "csvFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

// useful functions

// functions from header file

/**
 * @brief Construct a new Csv File:: Csv File object
 * @param file_path 
 */
                            CsvFile::CsvFile(const char * file_path)
{
    // creates an empty .Csv file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
    std::ofstream file;
    file.open(file_path, std::ios::app);
    file.close();

    CsvFile::set_path(file_path);
    CsvFile::set_entries(file_path);
}

/**
 * @brief Construct a new Csv File:: Csv File object. Alternative constructor taking string as an input.
 * 
 * @param str_file_path 
 */
                            CsvFile::CsvFile(std::string str_file_path)
{
    // creates an empty .Csv file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
    const char * file_path = str_file_path.c_str();

    std::ofstream file;
    file.open(file_path, std::ios::app);
    file.close();

    set_path(file_path);
    set_entries(file_path);
}

/**
 * @brief Copy constructor.
 * Construct a new Csv File:: Csv File object.
 * @param csv_file 
 */
                            CsvFile::CsvFile(const CsvFile& csv_file)
{
    CsvFile::file_path = csv_file.file_path;
    CsvFile::entries = csv_file.entries;
}

/**
 * @brief Destroy the Csv File:: Csv File object.
 */
                            CsvFile::~CsvFile()
{

};

// file_path setter and getter

/**
 * @brief 
 * @param file_path 
 */
void                        CsvFile::set_path(const char * file_path)
{
    std::string str(file_path);
    CsvFile::file_path = str;
}

/**
 * @brief 
 * @return std::string 
 */
std::string                 CsvFile::get_path()                                             const
{
    return CsvFile::file_path;
}

/**
 * @brief 
 * @param file_path 
 */
void                        CsvFile::set_entries(const char * file_path)
{
    std::ifstream file;
    file.open(file_path);

    if(file.is_open())
    {
    // count entries
    CsvFile::entries = 0;
    std::string line;
    while(getline(file, line))  CsvFile::entries++;

    file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}

/**
 * @brief 
 * @return int 
 */
int                         CsvFile::get_entries()                                          const
{
    return CsvFile::entries;
}


// write into the file, deleting all previous content
void                        CsvFile::write(const std::string line)                          const
{
    std::ofstream file;
    file.open(CsvFile::file_path);

    if(file.is_open())
    {
        std::vector<std::string> words = split_words(line);
        for(std::vector<std::string>::iterator i = words.begin(); i != words.end(); i++)
        {
            if (i == words.end()-1)     file << *i;
            else                        file << *i << ",";
        }
        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}
// write into the file, keeping all previous content
void                        CsvFile::append(const std::string line)                         const
{
    std::ofstream file;
    file.open(CsvFile::file_path, std::ios::app);

    if(file.is_open())
    {
        file << "\n";
        std::vector<std::string> words = split_words(line);
        for(std::vector<std::string>::iterator i = words.begin(); i != words.end(); i++)
        {
            if (i == words.end()-1)     file << *i;
            else                        file << *i << ",";
        }
        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}
// write into the file, deleting all previous content
void                        CsvFile::write(const char * line)                               const
{
    std::string str(line);
    CsvFile::write(str);
}
// write into the file, keeping all previous content
void                        CsvFile::append(const char * line)                              const
{
    std::string str(line);
    CsvFile::append(str);
}



/**
 * @brief Gets an element from the file as a string.
 * @param line 
 * @param column 
 * @return std::string 
 */
std::string                 CsvFile::get_element(const int line, const int column)          const
{
    std::string file_line = CsvFile::get_line(line);
    std::vector<std::string> words = CsvFile::split_words(file_line);
    return words.at(column);
}

/**
 * @brief Returns a line from the file. Lines are numbered beginning with zero.
 * @param line line you want to return.
 */
std::string                 CsvFile::get_line(const int line)                               const
{
    std::ifstream file;
    file.open(CsvFile::file_path);

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
 * @brief  This only works with .Csv files using a space (' ') or a tab as delimiter between columns. 
 * Columns are numbered beginning with zero.
 * @param column: number referring to the column you want to print
 */
std::vector<double>         CsvFile::get_column(const int column, const int first_row)  const
{
    std::vector<double> vector;

    std::ifstream file;
    file.open(CsvFile::file_path);

    if(file.is_open())
    {
        int n_columns = CsvFile::count_column();
        file.clear();
        file.seekg(0, std::ios::beg);

        if(column >= n_columns)
        {
            std::cerr << "Error: column " << column << " does not exist. The file has " << n_columns << " columns." << std::endl;
            return vector;
        }

        // skip lines
        std::string skip;
        for (int j = 0; j < first_row; j++) getline(file, skip);

        int i = 0;
        while (! file.eof())
        {   
            std::string column_element;
            file >> column_element;
            if(i == column)
            {
                double element = atof(column_element.c_str());
                vector.push_back(element);
            }
            i++;
            if(i == n_columns)  i = 0;
        }

        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;

    return vector;
}

void                        CsvFile::current_file()                                         const
{
    std::cout << std::endl << "Il file attualmente in lettura è: " << CsvFile::file_path << std::endl;
}

/**
 * @brief Extract single words (elements separated by space) from a string.
 * @param input string you want to extraxt words from.
 * @return vector containing single words.
 */
std::vector<std::string>    CsvFile::split_words(const std::string input)                   const
{
    std::istringstream ss(input);
    std::string word;
    std::vector<std::string> vector1;

    while(ss >> word)   vector1.push_back(word);

    return vector1;
}

/**
 * @brief Checks if the first line of the file contains words. This function is used in Data.cpp to use the words in the 
 * first line as names for the CsvData objects generated.
 * NOTE: "file1" will not be regarded as a number although it does contain a digit in it. 
 * @return true if no number is present in each element of the first line.
 * @return false if a number is found in the first line.
 */
bool                        CsvFile::check_words()                                          const
{
    std::ifstream file;
    file.open(CsvFile::file_path);
    if(file.is_open())
    {
        std::string first_line;
        getline(file, first_line);

        bool check = true;

        std::vector<std::string> words = CsvFile::split_words(first_line);
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

/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * If different lines of the file have a different amount of columns, an error is displayed.
 * @return int number of columns.
 */
int                         CsvFile::count_column()                                         const
{
    int columns = 1;
    int save_columns = 0;       // used to check if each line has the same number of columns

    std::ifstream file;
    file.open(CsvFile::file_path);

    if(file.is_open())
    {
        for (int j = 0; j < CsvFile::entries; j++)
        {
            std::string row;
            getline(file, row);

            bool previous_was_space = false;

            for(int i=0; i<row.size(); i++)
            {
                if(row[i] == ' ' || row[i] == '\t' || row[i] == ',')
                {
                    if(! previous_was_space)
                    {
                        columns++;
                        previous_was_space = true;
                    }
                }
                else        previous_was_space = false;
            }

            if (j > 0 && columns != save_columns)
            {
                std::cerr << "Error: not all the lines have the same amount of columns. First " << j << " lines have "
                << save_columns << " columns (this value will be returned)." << std::endl;
                return save_columns;
            }
            
            save_columns = columns;
            columns = 1;
        }
    }
    return columns;
}


// friend functions

std::ostream&               operator<<  (std::ostream& out, const CsvFile& Csv_file)
{
    std::ifstream file;
    file.open(Csv_file.file_path);
    if(file.is_open())
    {
        out << "Print " << Csv_file.file_path << ": " << std::endl;
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

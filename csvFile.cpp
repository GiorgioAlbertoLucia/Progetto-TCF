#include "file.h"
#include "csvFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

// useful functions

// count number of columns in a string
int countcolumn_csv(const std::string row)
{
    std::cout << "first string is:" << row << std::endl;
    int columns = 1;
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

    return columns;
}

// extract single written elements from a string
std::vector<std::string> split_words(const std::string input)
{
    std::istringstream ss(input);
    std::string word;
    std::vector<std::string> vector1;

    while(ss >> word)   vector1.push_back(word);

    return vector1;
}

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
void                CsvFile::set_path(const char * file_path)
{
    std::string str(file_path);
    CsvFile::file_path = str;
}

/**
 * @brief 
 * @return std::string 
 */
std::string         CsvFile::get_path()                             const
{
    return CsvFile::file_path;
}

/**
 * @brief 
 * @param file_path 
 */
void                CsvFile::set_entries(const char * file_path)
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
int                 CsvFile::get_entries()                          const
{
    return CsvFile::entries;
}


// write into the file, deleting all previous content
void                CsvFile::write(const std::string line)          const
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
void                CsvFile::append(const std::string line)         const
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
void                CsvFile::write(const char * line)               const
{
    std::string str(line);
    CsvFile::write(str);
}
// write into the file, keeping all previous content
void                CsvFile::append(const char * line)              const
{
    std::string str(line);
    CsvFile::append(str);
}



/**
 * @brief Returns a line from the file. Lines are numbered beginning with zero.
 * @param line line you want to return.
 */
void                CsvFile::get_line(const int line)               const
{
    std::ifstream file;
    file.open(CsvFile::file_path);

    if(line >= entries)
    {
        std::cerr << "Error: line " << line << " does not exist. The file has " << entries << " lines." << std::endl;
        return;
    }

    if(file.is_open())
    {   
        int i = 0;
        std::string str;
        while(i <= line) getline(file, str);        // reads all the lines until the one you need
        std::cout << str << std::endl;

        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;

}

/** 
 * @brief  This only works with .Csv files using a space (' ') or a tab as delimiter between columns. 
 * Columns are numbered beginning with zero.
 * @param column: number referring to the column you want to print
 */
std::vector<double> CsvFile::get_column(const int column)           const
{
    std::vector<double> vector;

    std::ifstream file;
    file.open(CsvFile::file_path);

    if(file.is_open())
    {
        // count number of columns
        std::string first_line;
        getline(file, first_line);
        int n_columns = countcolumn_csv(first_line);
        std::cout << "n_cols is:" << n_columns << std::endl;

        // get back to the top of the file, then print the selected column
        file.clear();
        file.seekg(0, std::ios::beg);

        if(column >= n_columns)
        {
            std::cerr << "Error: column " << column << " does not exist. The file has " << n_columns << " columns." << std::endl;
            return vector;
        }

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

void                CsvFile::current_file()                         const
{
    std::cout << std::endl << "Il file attualmente in lettura è: " << CsvFile::file_path << std::endl;
}


// friend functions

std::ostream&       operator<<  (std::ostream& out, const CsvFile& Csv_file)
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

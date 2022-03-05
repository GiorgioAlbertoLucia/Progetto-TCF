#include "file.h"
#include "txtFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

/* USEFUL FUNCTIONS */

/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * @param row string you want the number of columns of.
 * @return int number of columns.
 */
int countcolumn_txt(const std::string row)
{
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
void                TxtFile::set_path(const char * file_path)
{
    std::string str(file_path);
    TxtFile::file_path = str;
}

/**
 * @brief 
 * @return std::string 
 */
std::string         TxtFile::get_path()                         const
{
    return TxtFile::file_path;
}

void                TxtFile::set_entries(const char * file_path)
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

int                 TxtFile::get_entries()                      const
{
    return TxtFile::entries;
}


/** Writes into the file, deleting all previous content.
 * @param line: line you want to write into the file.
 */ 
void                TxtFile::write(const std::string line)      const
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

/** @brief Writes into the file, keeping all previous content.
 *  @param line: line you want to append to the file.
 */ 
void                TxtFile::append(const std::string line)     const
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

/** Writes into the file, deleting all previous content.
 * @param line: line you want to write into the file.
 */ 
void                TxtFile::write(const char * line)           const
{
    std::string str(line);
    TxtFile::write(str);
}

/** 
 * @brief Writes into the file, keeping all previous content.
 * @param line: line you want to append to the file.
 */ 
void                TxtFile::append(const char * line)          const
{
    std::string str(line);
    TxtFile::append(str);
}



/**
 * @brief Returns a line from the file. Lines are numbered beginning with zero.
 * @param line line you want to return.
 */
void                TxtFile::get_line(const int line)           const
{
    /*
    Lines are numbered beginning with zero.
    int line: number referring to the line you want to print
    */

    std::ifstream file;
    file.open(TxtFile::file_path);

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
 * @brief  This only works with .txt files using a space (' ') or a tab as delimiter between columns. 
 * Columns are numbered beginning with zero.
 * @param column: number referring to the column you want to print
 */
std::vector<double> TxtFile::get_column(const int column)       const
{
    std::vector<double> vector;

    std::ifstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {
        // count number of columns
        std::string first_line;
        getline(file, first_line);
        int n_columns = countcolumn_txt(first_line);

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
    else    std::cout << "Error: unable to open file" << std::endl;
    return vector;
}

void                TxtFile::current_file()                     const
{
    std::cout << std::endl << "Il file attualmente in lettura è: " << TxtFile::file_path << std::endl;
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

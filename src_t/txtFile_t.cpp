#include "../include_t/file_t.hpp"
#include "../include_t/txtFile_t.hpp"

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
template <class T>
                            TxtFile<T>::TxtFile(const char * file_path)
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
template <class T>
                            TxtFile<T>::TxtFile(std::string str_file_path)
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
template <class T>
                            TxtFile<T>::TxtFile(const TxtFile& txt_file)
{
    TxtFile<T>::file_path = txt_file.file_path;
    TxtFile<T>::entries = txt_file.entries;
}

/**
 * @brief Destroy the Txt File:: Txt File object
 */
template <class T>
                            TxtFile<T>::~TxtFile()
{

}


// setter and getter

template <class T>
void                        TxtFile<T>::set_entries(const char * file_path)
{
    std::ifstream file(TxtFile<T>::file_path);

    // skip comment
    int first_line = comment();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(file.is_open())
    {
    // count entries
    TxtFile<T>::entries = 0;
    std::string line;
    while(getline(file, line))  TxtFile<T>::entries++;

    file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}


/** 
 * @brief Writes into the file, deleting all previous content.
 * @param line: line you want to write into the file.
 */ 
template <class T>
void                        TxtFile<T>::write(const std::string line)          const
{
    std::ofstream file;
    file.open(TxtFile<T>::file_path);

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
template <class T>
void                        TxtFile<T>::append(const std::string line)         const
{
    std::ofstream file;
    file.open(TxtFile<T>::file_path, std::ios::app);

    if(file.is_open())
    {
        file << "\n" << line;
        file.close();
    }
    else    std::cerr << "Error: unable to open file" << std::endl;
}
 

/**
 * @brief This function add a column of floats (with their description as top line) to an existing .txt file. The name of the column
 * is added only if the first line of the file (except comment) contains words 
 * @param col_name description of the column data
 * @param column data to add in the column
 */
template <class T>
void                        TxtFile<T>::append_column(const char * col_name, std::vector<T> column) const
{
    std::fstream file(TxtFile<T>::file_path, std::ios::in);
    std::string line;
    std::vector<std::string> file_lines;
    while(getline(file, line))  file_lines.push_back(line);     // fill a vector with the file content
    file.close();

    int comment = TxtFile<T>::comment();

    file.open(TxtFile<T>::file_path, std::ios::out);
    if(TxtFile<T>::check_words())
    {
        for (int i = 0; i < file_lines.size(); i++)
        {
            if (i < comment)        file << file_lines.at(i) << std::endl;
            else if (i == comment)  file << file_lines.at(i) << "\t\t" << col_name << std::endl;
            else                    file << file_lines.at(i) << "\t\t\t" << column.at(i-comment-1) << std::endl;                          
        }
    }
    else
    {
        for (int i = 0; i < file_lines.size(); i++)
        {
            if (i < comment)        file << file_lines.at(i) << std::endl;
            else                    file << file_lines.at(i) << "\t\t\t" << column.at(i-comment) << std::endl;                          
        }
    }
    
    file.close();
}

/**
 * @brief Gets an element from the file as a string.
 * @param line 
 * @param column 
 * @return std::string 
 */
template <class T>
std::string                 TxtFile<T>::get_element(const int line, const int column)  const
{
    std::string file_line = TxtFile<T>::get_line(line);
    std::vector<std::string> words = TxtFile<T>::split_words(file_line);
    return words.at(column);
}
/**
 * @brief Returns a line from the file. Lines are numbered beginning with zero.
 * @param line line you want to return.
 */
template <class T>
std::string                 TxtFile<T>::get_line(const int line)               const
{
    std::ifstream file(TxtFile<T>::file_path);

    // skip comment
    int first_line = comment();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(line >= entries)
    {
        std::cerr << "Error: line " << line << " does not exist. The file has " << entries << " lines." << std::endl;
        return 0;
    }

    if(file.is_open())
    {   
        std::string str;
        for(int i=0; i<=line; i++) getline(file, str);        // reads all the lines until the one you need
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
template <class T>
std::vector<T>              TxtFile<T>::get_column(const int column, const int first_row)       const
{
    std::vector<T> vector;

    std::ifstream file(TxtFile<T>::file_path);

    // skip comment
    int first_line = comment();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(file.is_open())
    {
        int n_columns = TxtFile<T>::count_column();
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
            T column_element;
            for(int i = 0; i <= column; i++)    iss >> column_element;
            vector.push_back(column_element);
        }
        file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;
    return vector;
}

template <class T>
void                        TxtFile<T>::current_file()                         const
{
    std::cout << std::endl << "Il file attualmente in lettura è: " << TxtFile<T>::file_path << std::endl;
}
/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * If different lines of the file have a different amount of columns, an error is displayed.
 * @return int number of columns.
 */
template <class T>
int                         TxtFile<T>::count_column()                         const
{
    int columns = 0;
    int save_columns = 0;       // used to check if each line has the same number of columns

    std::ifstream file(TxtFile<T>::file_path);

    // skip comment
    int first_line = comment();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 

    if(file.is_open())
    {   
        for (int j = 0; j < TxtFile<T>::entries; j++)
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
template <class T>
std::vector<std::string>    TxtFile<T>::split_words(const std::string input)   const
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
template <class T>
bool                        TxtFile<T>::check_words()                          const
{
    std::ifstream file(TxtFile<T>::file_path);

    // skip comment
    int first_line = comment();
    for(int i=0; i<first_line; i++) file.ignore(10000, '\n'); 
    
    if(file.is_open())
    {
        std::string first_line;
        getline(file, first_line);

        bool check = true;

        std::vector<std::string> words = TxtFile<T>::split_words(first_line);
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
         * @brief Skips all comment lines in the file. A line beginning with # is a comment line.
         */
template <class T>
int                         TxtFile<T>::comment()                              const
{
    int comment = 0;
    std::string line;
    std::ifstream file(TxtFile<T>::file_path);
    if(file.is_open())  while(file >> line) if(line.at(0)=='#') comment++;
    file.close();
    return comment;
}

// friend functions
template <class T>
std::ostream&               operator<<  (std::ostream& out, const TxtFile<T>& txt_file)
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

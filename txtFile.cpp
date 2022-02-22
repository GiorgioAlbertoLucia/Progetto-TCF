#include "file.h"
#include "txtFile.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// useful functions
int countcolumn_txt(const std::string row)
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


// functions from header file
                    TxtFile::TxtFile(const std::string file_path)
{
    // creates an empty .txt file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
    std::ofstream file;
    file.open(file_path, std::ios::app);
    file.close();

    TxtFile::set_path(file_path);
    TxtFile::set_entries(file_path);
}

                    TxtFile::~TxtFile()
{

};

// file_path setter and getter

void                TxtFile::set_path(const std::string file_path)
{
    TxtFile::file_path = file_path;
}

std::string         TxtFile::get_path()                 const
{
    return TxtFile::file_path;
}

void                TxtFile::set_entries(const std::string file_path)
{
    std::ifstream file;
    file.open(file_path);

    if(file.is_open())
    {
    // count entries
    TxtFile::file_lines = 0;
    std::string line;
    while(getline(file, line))  TxtFile::file_lines++;

    file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;
}

int                 TxtFile::get_entries()                  const
{
    return TxtFile::file_lines;
}


// write into the file, deleting all previous content
void                TxtFile::write(const std::string line)        const
{
    std::ofstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {
        file << line;
        file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;
}

// write into the file, keeping all previous content
void                TxtFile::append(const std::string line)       const
{
    std::ofstream file;
    file.open(TxtFile::file_path, std::ios::app);

    if(file.is_open())
    {
        file << "\n" << line;
        file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;
}



void                TxtFile::getLine(const int line)              const
{
    /*
    Lines are numbered beginning with zero.
    int line: number referring to the line you want to print
    */

    std::ifstream file;
    file.open(TxtFile::file_path);

    if(file.is_open())
    {   
        int i = 0;
        std::string str;
        while(i <= line) getline(file, str);        // reads all the lines until the one you need
        std::cout << str << std::endl;

        file.close();
    }
    else    std::cout << "Error: unable to open file" << std::endl;

}

/*
    This only works with .txt files using a space (' ') or a tab ('\t') as delimiter between columns.
    Columns are numbered beginning with zero.
    int column: number referring to the column you want to print
*/
std::vector<double> TxtFile::getColumn(const int column)          const
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
        std::cout << "n_cols is:" << n_columns << std::endl;

        // get back to the top of the file, then print the selected column
        file.clear();
        file.seekg(0, std::ios::beg);

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

void                TxtFile::current_file()                 const
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
    else    std::cout << "Error: unable to open file" << std::endl;

    return out;
}

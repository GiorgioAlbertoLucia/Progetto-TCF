#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

/*
Abstract class: 
    - object = data file
    - functions = open_file, read_file, write_file 
*/

class File
{
    public:
        virtual                             ~File(){};
        
        virtual void                        set_path(const char *)                        = 0;
        virtual std::string                 get_path()                              const = 0;
        virtual void                        set_entries(const char *)                     = 0;     // given the file, automatically sets the number of entries
        virtual int                         get_entries()                           const = 0;

        virtual void                        write(const std::string)                const = 0;
        virtual void                        append(const std::string)               const = 0;
        virtual void                        write(const char *)                     const = 0;
        virtual void                        append(const char *)                    const = 0;

        virtual std::string                 get_element(const int, const int)       const = 0;
        virtual std::string                 get_line(const int)                     const = 0;     
        /** 
        * @brief  This only works with .txt files using a space (' ') or a tab as delimiter between columns. 
        * Columns are numbered beginning with zero. Default template function.
        * @param column: number referring to the column you want to print.
        * @param first_row = 0: row you want to start importing from. Lines are numbered from 0.
        */
        virtual std::vector<double>         get_column(const int, const int = 0)    const = 0;     
        /**
         * @brief Get the column<udouble> object. Specialized implementation for get_column (udouble is a measure and an error,
         * therefore tow columns at a time need to be read from the file)
         * @return std::vector<udouble> 
         */
        //virtual std::vector<udouble>      get_column<udouble>(const int, const int = 0)   const = 0;

        virtual void                        current_file()                          const = 0;     
        /**
        * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
        * If different lines of the file have a different amount of columns, an error is displayed.
        * @return int number of columns.
        */
        virtual int                         count_column()                          const = 0;
        /**
        * @brief Extract single words (elements separated by space) from a string.
        * @param input string you want to extraxt words from.
        * @return vector containing single words.
        */
        virtual std::vector<std::string>    split_words(const std::string)          const = 0;
        /**
        * @brief Checks if the first line of the file contains words. This function is used in txtDataset.cpp to use the words in the 
        * first line as names for the Data objects generated.
        * NOTE: "file1" will not be regarded as a number although it does contain a digit in it. 
        * @return true if no number is present in each element of the first line.
        * @return false if a number is found in the first line.
        */
        virtual bool                        check_words()                           const = 0;
};

#endif
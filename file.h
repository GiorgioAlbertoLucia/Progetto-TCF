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
        * Columns are numbered beginning with zero.
        * @param column: number referring to the column you want to print.
        * @param first_row = 0: row you want to start importing from. Lines are numbered from 0.
        */
        virtual std::vector<double>         get_column(const int, const int = 0)    const = 0;     
        //getColumn per udouble

        virtual void                        current_file()                          const = 0;     
        /**
        * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
        * If different lines of the file have a different amount of columns, an error is displayed.
        * @return int number of columns.
        */
        virtual int                         count_column()                          const = 0;
        virtual std::vector<std::string>    split_words(const std::string)          const = 0;
        virtual bool                        check_words()                           const = 0;
};

#endif
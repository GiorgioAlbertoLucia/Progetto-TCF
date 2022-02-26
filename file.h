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
                        File(){};
        virtual         ~File(){};
        
        virtual void                set_path(const char *)                    = 0;
        virtual const char          get_path()                          const = 0;
        virtual void                set_entries(const char *)                 = 0;     // given the file, automatically sets the number of entries
        virtual int                 get_entries()                       const = 0;

        virtual void                write(const std::string)            const = 0;
        virtual void                append(const std::string)           const = 0;
        virtual void                write(const char *)                 const = 0;
        virtual void                append(const char *)                const = 0;

        virtual void                getLine(const int)                  const  {};     // returns the selected line
        virtual std::vector<double> getColumn(const int)                const = 0;     // returns the selected column 
        //getColumn per udouble
        virtual void                current_file()                      const  {};     // returns the file that is currently open


};




#endif
#ifndef CSVFILE_H
#define CSVFILE_H

#include "file.h"
#include <iostream>
#include <string>

class CsvFile: public File
{

        friend  std::ostream&    operator<< (std::ostream&, const CsvFile&);
        friend  std::istream&    operator>> (std::istream&, CsvFile&);              // writes inside the file

    public:
        CsvFile(std::string);
        ~CsvFile();
        
        virtual void                set_path(const std::string);                    // choose a txt file to work with
        virtual std::string         get_path()                          const;
        virtual void                set_entries(const std::string);      
        virtual int                 get_entries()                       const;

        virtual void                write(const std::string)            const;
        virtual void                append(const std::string)           const;

        virtual void                getLine(const int)                  const;
        virtual std::vector<double> getColumn(const int)                const;
        //getColumn per udouble
        virtual void                current_file()                      const;


    private:
                std::string     file_path;
                int             file_lines;



};

#endif
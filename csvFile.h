#ifndef CSVFILE_H
#define CSVFILE_H

#include "file.h"
#include <iostream>
#include <string>
#include <vector>

class CsvFile: public File
{

        friend  std::ostream&    operator<< (std::ostream&, const CsvFile&);

    public:
        CsvFile(const char *);
        ~CsvFile();
        
        virtual void                set_path(const char *);                         // choose a txt file to work with
        virtual const char          get_path()                          const;
        virtual void                set_entries(const char *);      
        virtual int                 get_entries()                       const;

        virtual void                write(const std::string)            const;
        virtual void                append(const std::string)           const;
        virtual void                write(const char *)                 const;
        virtual void                append(const char *)                const;

        virtual void                getLine(const int)                  const;
        virtual std::vector<double> getColumn(const int)                const;
        //getColumn per udouble
        virtual void                current_file()                      const;


    private:
                std::string     file_path;
                int             entries;



};

#endif
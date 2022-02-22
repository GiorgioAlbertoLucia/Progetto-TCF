#ifndef TXTFILE_H
#define TXTFILE_H

#include "file.h"
#include <iostream>
#include <string>
#include <vector>

class TxtFile: public File
{

        friend  std::ostream&       operator<< (std::ostream&, const TxtFile&);

    public:
        TxtFile(const std::string);
        ~TxtFile();
        
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
                int             file_lines;                                         // number of entries in the file


};

#endif
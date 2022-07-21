#ifndef CSVFILE_H
#define CSVFILE_H

#include "../include_t/file_t.hpp"
#include <iostream>
#include <string>
#include <vector>

template <class T>
class CsvFile: public File
{

        friend  std::ostream&               operator<< (std::ostream&, const CsvFile&);

    public:
                                            CsvFile(const char *);
                                            CsvFile(std::string);
                                            CsvFile(const CsvFile&);
                                            ~CsvFile();
        
        virtual void                        set_path(const char *)                                                      {CsvFile::file_path = std::string(file_path);};
        virtual void                        set_entries(const char *);                                  

        virtual std::string                 get_path()                                                          const   {return CsvFile::file_path;};
        virtual int                         get_entries()                                                       const   {return CsvFile::entries;};

        virtual void                        write(const std::string)                                            const;
        virtual void                        append(const std::string)                                           const;
                /** 
                * @brief Writes into the file, deleting all previous content.
                * @param line: line you want to write into the file.
                */
        virtual void                        write(const char *)                                                 const   {CsvFile::write(std::string (line));};
                /** 
                * @brief Writes into the file, keeping all previous content.
                * @param line: line you want to append to the file.
                */
        virtual void                        append(const char *)                                                const   {CsvFile::append(std::string (line));};
        virtual void                        append_column(const char * col_name, std::vector<T> column)         const;


        virtual std::string                 get_element(const int, const int)                                   const;
        virtual std::string                 get_line(const int)                                                 const;
        virtual std::vector<T>              get_column(const int, const int = 0)                                const;
        //getColumn per udouble                         


        virtual void                        current_file()                                                      const;
        virtual std::vector<std::string>    split_words(const std::string)                                      const;
        virtual int                         count_column()                                                      const;
        virtual bool                        check_words()                                                       const;
        virtual int                         comment()                                                           const;


    private:
                std::string                 file_path;
                int                         entries;



};

#endif
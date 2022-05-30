#ifndef TXTFILE_H
#define TXTFILE_H

#include "../include_t/file_t.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief 
 * 
 */
template <class T>
class TxtFile: public File
{

        friend  std::ostream&               operator<<(std::ostream&, const TxtFile&);

    public:
                                            TxtFile();
                                            TxtFile(const char *);
                                            TxtFile(std::string);
                                            TxtFile(const TxtFile&);
                                            ~TxtFile();
        
        virtual void                        set_path(const char * file_path)                                    {TxtFile::file_path = std::string(file_path);};                    
        virtual void                        set_entries(const char *);                                  
        

        virtual std::string                 get_path()                                                  const   {return TxtFile::file_path;};
        virtual int                         get_entries()                                               const   {return TxtFile::entries;};


        virtual void                        write(const std::string)                                    const;
        virtual void                        append(const std::string)                                   const;
                /** 
                * @brief Writes into the file, deleting all previous content.
                * @param line: line you want to write into the file.
                */
        virtual void                        write(const char * line)                                    const   {TxtFile::write(std::string (line));};
                /** 
                * @brief Writes into the file, keeping all previous content.
                * @param line: line you want to append to the file.
                */ 
        virtual void                        append(const char *line)                                    const   {TxtFile::append(std::string (line));};
        virtual void                        append_column(const char * col_name, std::vector<T> column) const;


        virtual std::string                 get_element(const int, const int)                           const;
        virtual std::string                 get_line(const int)                                         const;
        virtual std::vector<T>              get_column(const int, const int = 0)                        const;
        /** 
         * @brief Get the column<udouble> object. Specialized implementation for get_column (udouble is a measure and an error,
         * therefore tow columns at a time need to be read from the file)
         * @return std::vector<udouble> 
         */
        //virtual std::vector<udouble>      get_column<udouble>(const int, const int = 0)   const = 0;  
    
    
        virtual void                        current_file()                                              const;
        virtual int                         count_column()                                              const;
        virtual std::vector<std::string>    split_words(const std::string)                              const;
        virtual bool                        check_words()                                               const;
        virtual int                         comment()                                                   const;

    private:
                std::string                 file_path;
                int                         entries;                                         // number of entries in the file
};

#endif
#ifndef TXTFILE_H
#define TXTFILE_H

#include "file.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief 
 * 
 */
class TxtFile: public File
{

        friend  std::ostream&               operator<<(std::ostream&, const TxtFile&);

    public:
        TxtFile();
        TxtFile(const char *);
        TxtFile(std::string);
        TxtFile(const TxtFile&);
        ~TxtFile();
        
        virtual void                        set_path(const char *);                    
        virtual std::string                 get_path()                              const;
        virtual void                        set_entries(const char *);      
        virtual int                         get_entries()                           const;

        virtual void                        write(const std::string)                const;
        virtual void                        append(const std::string)               const;
        virtual void                        write(const char *)                     const;
        virtual void                        append(const char *)                    const;

        virtual std::string                 get_element(const int, const int)       const;
        virtual std::string                 get_line(const int)                     const;
        virtual std::vector<double>         get_column(const int, const int = 0)    const;
        /**
         * @brief Get the column<udouble> object. Specialized implementation for get_column (udouble is a measure and an error,
         * therefore tow columns at a time need to be read from the file)
         * @return std::vector<udouble> 
         */
        //virtual std::vector<udouble>      get_column<udouble>(const int, const int = 0)   const = 0;

        virtual void                        current_file()                          const;
        virtual int                         count_column()                          const;
        virtual std::vector<std::string>    split_words(const std::string)          const;
        virtual bool                        check_words()                           const;

    private:
                std::string                 file_path;
                int                         entries;                                         // number of entries in the file
};

#endif
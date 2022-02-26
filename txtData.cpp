#include "txtFile.h"
#include "txtData.h"

#include <iostream>
#include <vector>
#include <string>

/*  USEFUL FUNCTIONS  */



/*  FUNCTIONS FROM HEADER FILE  */  


                    TxtData::TxtData(const char * file_path, const int file_column, const char * name):TxtFile(file_path)
{   
    set_file(file_path);
    set_name(name);
    
    TxtData::data_vector = get_file.get_column(file_column);
}

                    TxtData::~TxtData()
{

}


// setter and getter

TxtData&            TxtData::set_file(const char * file_path)
{
    set_path(file_path);
    return *this;
}

TxtFile             TxtData::get_file()                                                     const
{
    TxtFile txt_file(get_path());
    return txt_file;
}

void                TxtData::set_name(const char * name)
{
    std::string str(name);
    TxtData::name = str;
}

const char          TxtData::get_name()                                                     const
{
    const char * name_char = TxtData::name.c_str();
    return * name_char;
}



void                TxtData::add_element(const double element)             
{
    TxtData::data_vector.push_back(element);
}
// position: goes from 0 to (number of elements -1)
void                TxtData::replace_element(const double element, const int position)
{
    
}


#include "data.h"
#include "dataset.h"

#include <iostream>
#include <vector>
#include <string>


                        TxtDataset::TxtDataset(const char * file_path, const char * name): TxtFile(file_path)
{
    TxtDataset::entries = TxtFile::count_column();
    TxtDataset::fill();
    TxtDataset::set_name(name);
}

/**
 * @brief Sets name of dataset
 * @param name 
 */
void                    TxtDataset::set_name(const char * name)
{
    std::string str_name(name);
    TxtDataset::name = str_name;
}

/**
 * @brief Sets name of dataset
 * @param name 
 */
void                    TxtDataset::set_name(std::string name)
{
    TxtDataset::name = name;
}

std::string             TxtDataset::get_name()                                                      const
{
    return TxtDataset::name;
}

void                    TxtDataset::fill()                                                          const
{
    if(TxtFile::check_words)
    {
        std::vector<std::string> names = TxtFile::split_words(TxtFile::get_line(0));
        for (int i = 0; i < TxtFile::count_column(); i++)
        {
            /* create a parallel file (copy of the original), erase the first line from it. Build all the txtdata elements
            from that file. At the end of the process erase that file. 
            */
            std::string path = TxtFile::get_path();

            TxtData txt_data(" ", i, names.at(i));
            std::vector<double> temporary = txt_data.get_data();
            temporary.erase(temporary.begin());
            txt_data.set_data()

            TxtDataset::dataset.push_back();
        }
        

        for (std::vector<TxtData>::const_iterator i = TxtDataset::dataset.begin(); i != TxtDataset::dataset.end(); i++)
        {
            *i->set_name()
        }
        
        
    }
    
    
}

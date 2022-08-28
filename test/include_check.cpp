#include "../include/polyfit.hpp"
#include "../include/csvFile.hpp"

#include <iostream>

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/test7.csv";
    CsvFile csv(path);

    std::cout << "rows: " << csv.get_rows() << std::endl << "columns: " << csv.get_columns() << std::endl;

    std::cout << "Hello world!" << std::endl;
    return 0;
}
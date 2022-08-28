#include "../include/dataset.hpp"

// Da eseguire con
// clang++ -std=c++11 test/test_t2.cpp src_t/txtFile_t.cpp src_t/csvFile_t.cpp -o exe/test_t2

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/test7.csv";

    // Dataset<double> dataset(path);
    // dataset.describe();

    Data<double> d1(path, 0); // d2(path, 1);
    //Data<double> d3;
    //d3 = d1 + d2;              // Dovrebbe essere una normalissima somma. Sta facendo qualcosa di diverso. Ho sonno. Vedo domani

    //std::cout << d3[0] << std::endl << dataset[1][2] << std::endl;

    d1.head();
    // d2.head();
    //d3.head();
}
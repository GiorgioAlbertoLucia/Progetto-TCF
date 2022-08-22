#include "../include_t/dataset_t.hpp"

// Da eseguire con
// clang++ -std=c++11 test/test_t2.cpp src_t/txtFile_t.cpp src_t/csvFile_t.cpp -o exe/test_t2

int main()
{
    const char * path = "/Users/giogi/Documents/TCF/Progetto/data/example.txt";

    Dataset<double> dataset(path);
    dataset.describe();

    Data<double> d1(path, 0), d2(path, 1);
    Data<double> d3;
    d3 = d1 + d2;              // Dovrebbe essere una normalissima somma. Sta facendo qualcosa di diverso. Ho sonno. Vedo domani

    d1.head();
    d2.head();
    d3.head();
}
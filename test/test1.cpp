#include "../include/txtFile.hpp"
#include "../include/csvFile.hpp"
#include "../include/data.hpp"
#include "../include/fileFactory.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// STATUS: OK

int main()
{
    TxtFile txt_file("data/test.txt");
    

    txt_file.write("1   2   3   4");
    txt_file.append("5   6   7   8");

    vector<double> data = txt_file.get_column(1);
    for (vector<double>::const_iterator i = data.begin(); i != data.end(); i++)
    {
        cout << *i << " ";
    }
    cout << endl;

    Data data1("data/test.txt", 2, "colonna 2");
    Data data2("data/test.txt", 3, "colonna 3");

    cout << data1 << endl;
    cout << data2 << endl;

    Data data3 = data1 + data2;
    data3.set_name("somma");

    cout << data3 << endl;


    //cout << txt_file.get_path() << endl;
    //txt_file.current_file();


    /*
    CsvFile csv_file("../data/test.csv");

    vector<double> vector1 = csv_file.getColumn(2);

    for(vector<double>::iterator i = vector1.begin(); i != vector1.end(); i++)   cout << *i << ' ';
    cout << endl;

    cout << csv_file << endl;
    */

    return 0;
}
#include "txtFile.h"
#include "csvFile.h"
#include "data.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    TxtFile txt_file("test.txt");
    

    txt_file.write("1   2   3   4");
    txt_file.append("5   6   7   8");

    Data data1("test.txt", 2, "colonna 2");
    Data data2("test.txt", 3, "colonna 3");

    cout << data1 << endl;
    cout << data2 << endl;

    Data data3 = data1 + data2;
    data3.set_name("somma");

    cout << data3 << endl;


    //cout << txt_file.get_path() << endl;
    //txt_file.current_file();


    /*
    CsvFile csv_file("test.csv");

    vector<double> vector1 = csv_file.getColumn(2);

    for(vector<double>::iterator i = vector1.begin(); i != vector1.end(); i++)   cout << *i << ' ';
    cout << endl;

    cout << csv_file << endl;
    */

    return 0;
}
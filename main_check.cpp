#include "txtFile.h"
#include "csvFile.h"
#include "txtData.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    TxtFile txt_file("test.txt");
    

    //txt_file.write("1   2   3   4");
    //txt_file.append("5  6   7   8");

    TxtData txt_data1("test.txt", 2, "colonna 2");
    TxtData txt_data2("test.txt", 3, "colonna 3");

    cout << txt_data1 << endl;
    cout << txt_data2 << endl;

    TxtData txt_data3 = txt_data1 + txt_data2;
    txt_data3.set_name("somma");

    cout << txt_data3 << endl;


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
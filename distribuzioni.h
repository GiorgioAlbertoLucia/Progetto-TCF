#ifndef DISTRIBUZIONI_H
#define DISTRIBUZIONI_H

#include "csvFile.h"
#include "txtFile.h"
#include <iostream>
#include <vector>
#include <string>

class Distribuzioni: public CsvFile, public TxtFile
{
    friend  std::ostream&   operator<<  (std::ostream&, const Distribuzioni&);
    friend  std::istream&   operator>>  (std::istream&, Distribuzioni&);


public:
                            Distribuzioni(std::string, int, std::string);   // file_path, file_column and distribution_name
                            ~Distribuzioni();
                            Distribuzioni(const Distribuzioni&);            // copy constructor

    // operators
            Distribuzioni&  operator+   (const Distribuzioni&);
            Distribuzioni&  operator-   (const Distribuzioni&);
            Distribuzioni&  operator*   (const double);
            Distribuzioni&  operator*   (const int); 
            bool            operator==  (const Distribuzioni&);
            bool            operator!=  (const Distribuzioni& right)    {return !(*this == right);};

            double          mean        ();
            double          std         ();
    const   void            rnd_dist    (double, double);           // inputs are min and max of the uniform distribution
    const   double          get_min     ();
    const   double          get_max     ();
    const   double          get         (int);                      // returns the nth element


private:
            std::vector<double>         data_vector;
            TxtFile                     data_file_txt;
            CsvFile                     data_file_csv;
            std::string                 name;



};




#endif
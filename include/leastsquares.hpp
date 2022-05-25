#ifndef LEASTSQUARES_H
#define LEASTSQUARES_H

#include <vector>
#include <string>

#include "../Eigen/Dense"
#include "udouble.hpp"

class LeastSquares
{
public:
    LeastSquares();
    //LeastSquares(const std::vector<Udouble>, const std::vector<Udouble>);
    LeastSquares(const std::vector<double>, const std::vector<double>, const std::vector<double>, const std::vector<double>, const char * = "");
    LeastSquares(const std::vector<double>, const std::vector<double>, const std::vector<double>, const char * = "");
    LeastSquares(const LeastSquares&);
    ~LeastSquares();

    //void set_ssquared(const char *);      to expand class to use errors on x
            void                fit(const char * = "");
            void                set_pvalue(const double);

    const   double              get_parameter(int i)    const       {return coeff.at(i);};
    const   double              get_parerror(int i)     const       {return sqrt( matrix.at(i).at(i) );};

    const   std::vector<double> get_yfit()              const       {return yfit;};  
    const   double              get_chisquared()        const       {return chi_squared;};
    const   double              get_pvalue()            const       {return p_value;};
    const   double              get_DoF()               const       {return DoF;};


private:
    int n;                                          // number of d    
    std::vector<double> x;              
    std::vector<double> y;              
    std::vector<double> sy;                         // errors on the y
    std::vector<double> coeff;                      // coefficients vector
    std::vector<std::vector<double>> matrix;        // coefficient matrix (U in documentation - wolfram)        

    std::vector<double> yfit;                           // values from fit
    int DoF;
    double chi_squared;
    double p_value;

    std::string formula;
};

#endif
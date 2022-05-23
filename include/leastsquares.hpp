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
    LeastSquares(const std::vector<double>, const std::vector<double>, const std::vector<double>, const char * = 0);
    LeastSquares(const LeastSquares&);
    ~LeastSquares();

    //void set_ssquared(const char *);      to expand class to use errors on x
    void    fit(const char * = "");
    void    set_pvalue(const double);

    double  get_parameter(int);
    double  get_parerror(int);
    
    double  get_chisquared();
    double  get_pvalue();
    double  get_DoF();


private:
    int n;                          // number of data

    Eigen::VectorXd x;
    Eigen::VectorXd y;
    Eigen::VectorXd sy;             // errors on the y
    Eigen::VectorXd coeff;          // coefficients vector
    Eigen::ArrayXXd matrix;         // coefficient matrix (U in documentation - wolfram)        

    int DoF;
    double chi_squared;
    double p_value;

    std::string formula;
};

#endif
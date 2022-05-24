#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "../Eigen/Dense"
#include "../include/leastsquares.hpp"

LeastSquares::LeastSquares(){}
LeastSquares::LeastSquares(const std::vector<double> x, const std::vector<double> y, const std::vector<double> sy, const char * formula)
{
    if(x.size() != y.size())    std::cerr << "Data vector x and y have different sizes." << std::endl;
    if(x.size() != sy.size())   std::cerr << "Data vector x and sy have different sizes." << std::endl;

    LeastSquares::n = x.size();

    LeastSquares::x.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::x[i] = x.at(i);

    LeastSquares::y.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::y[i] = y.at(i);

    LeastSquares::sy.resize(n);
    for(int i = 0; i < n; i++)   LeastSquares::sy[i] = sy.at(i);

    LeastSquares::yfit.resize(n);

    LeastSquares::formula = std::string(formula);
}
LeastSquares::~LeastSquares(){}


/**
 * @brief Creates a fit for the entered data, using a function passed by the user.
 * 
 * @param formula the function can be: 
 *      - "poln", with n any integer from 0 to 99
 *      - ""
 */
void LeastSquares::fit(const char * formula)
{
    if(std::string(formula) != "")   LeastSquares::formula = std::string(formula);
    if(std::string(formula) == "" && LeastSquares::formula == "")    std::cerr << "A formula is needed for the fit." << std::endl;

    Eigen::VectorXd v;                                  // vector v in documentation

    if(LeastSquares::formula.substr(0,3) == "pol")
    {   int grade;                                          // grade of the polynomial
        if(LeastSquares::formula.length() == 4)   grade = stoi(LeastSquares::formula.substr(3,1));
        if(LeastSquares::formula.length() == 5)   grade = stoi(LeastSquares::formula.substr(3,2));

        LeastSquares::matrix.resize(grade+1, grade+1);      // for a k-degree polynomial a (k+1)*(k+1) matrix is needed
        for(int i = 0; i < grade+1; i++)
        {
            for(int j = 0; j < grade+1; j++)
            {
                std::vector<double> sum_elem;
                for(int k = 0; k < n; k++)  sum_elem.push_back( pow(x[k],i+j)/pow(sy[k],2) );
                LeastSquares::matrix[i,j] = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
            }
        }

        v.resize(grade+1);
        for(int i = 0; i < grade+1; i++)
        {
            std::vector<double> sum_elem;
            for(int k = 0; k < n; k++)  sum_elem.push_back( y[k]*pow(x[k],i)/pow(sy[k],2) );
            v[i] = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
        }

        LeastSquares::DoF = LeastSquares::n - grade - 1;

        LeastSquares::coeff = (LeastSquares::matrix.matrix()).inverse() * v;
        
        std::vector<double> sum_elem;
        for(int k = 0; k < n; k++)
        {
            for(int i = 0; i < grade+1; i++)
            {
                yfit[k] += coeff[i] * pow(x[k], i);
            } 
            double num = y[k] - yfit[k]; 
            sum_elem.push_back( pow(num,2)/pow(sy[k],2) );
        }
        LeastSquares::chi_squared = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
    }
    
    

    // print fit results
    std::cout << "Fit results:" << std::endl;
}

void set_pvalue(const double chi_squared)
{

}
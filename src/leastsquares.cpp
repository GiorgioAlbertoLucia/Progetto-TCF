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

    LeastSquares::x = x;
    LeastSquares::y = y;
    LeastSquares::sy = sy;

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
    
    Eigen::VectorXd x_vec(LeastSquares::n), y_vec(LeastSquares::n), sy_vec(LeastSquares::n), yfit_vec(LeastSquares::n);

    for(int i = 0; i < n; i++)   x_vec(i) = LeastSquares::x.at(i);
    for(int i = 0; i < n; i++)   y_vec(i) = LeastSquares::y.at(i);
    for(int i = 0; i < n; i++)   sy_vec(i) = LeastSquares::sy.at(i);


    if(LeastSquares::formula.substr(0,3) == "pol")
    {   int grade;                                          // grade of the polynomial
        if(LeastSquares::formula.length() == 4)   grade = stoi(LeastSquares::formula.substr(3,1));
        if(LeastSquares::formula.length() == 5)   grade = stoi(LeastSquares::formula.substr(3,2));

        Eigen::MatrixXd matrix(grade+1, grade+1);           // for a k-degree polynomial a (k+1)*(k+1) matrix is needed
        for(int i = 0; i < grade+1; i++)
        {
            for(int j = 0; j < grade+1; j++)
            {
                std::vector<double> sum_elem;
                for(int k = 0; k < n; k++)  sum_elem.push_back( pow(x_vec(k),i+j)/pow(sy_vec(k),2) );
                matrix(i,j) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
            }
        }

        for (int i = 0; i < grade+1; i++)
        {
            std::vector<double> temp;
            for(int j = 0; j < grade+1; j++)    temp.push_back(matrix(i,j));
            LeastSquares::matrix.push_back(temp);
        }
        

        v.resize(grade+1);
        for(int i = 0; i < grade+1; i++)
        {
            std::vector<double> sum_elem;
            for(int k = 0; k < n; k++)  sum_elem.push_back( y_vec(k)*pow(x_vec(k),i)/pow(sy_vec(k),2) );
            v(i) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
        }

        LeastSquares::DoF = LeastSquares::n - grade - 1;

        Eigen::VectorXd coeff_vec = matrix.inverse() * v;
        for(int i = 0; i < grade+1; i++)   LeastSquares::coeff.push_back(coeff_vec(i));
        
        std::vector<double> sum_elem;
        for(int k = 0; k < n; k++)
        {
            for(int i = 0; i < grade+1; i++)
            {
                yfit_vec(k) += coeff_vec(i) * pow(x_vec(k), i);
            } 
            LeastSquares::yfit.push_back(yfit_vec(k));
            double num = y_vec(k) - yfit_vec(k); 
            sum_elem.push_back( pow(num,2)/pow(sy_vec(k),2) );
        }
        LeastSquares::chi_squared = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
    }
    
    

    // print fit results
    std::cout << "Fit results:" << std::endl;
}

void set_pvalue(const double chi_squared)
{

}
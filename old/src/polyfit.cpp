#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "../Eigen/Dense"
#include "../include/polyfit.hpp"
#include "../include/data.hpp"
#include "../include/udouble.hpp"

PolyFit::PolyFit(){}

PolyFit::PolyFit(const std::vector<Udouble> x, const std::vector<Udouble> y, const int polygrade)
{
    if(x.size() != y.size())    std::cerr << "Data vector x and y have different sizes." << std::endl;

    PolyFit::n = x.size();

    for(int i = 0; i < x.size(); i++)   PolyFit::x.push_back(x.at(i).get_value());
    for(int i = 0; i < y.size(); i++)   PolyFit::y.push_back(y.at(i).get_value());
    for(int i = 0; i < y.size(); i++)   PolyFit::sy.push_back(y.at(i).get_error());

    // swap zeros in sy vector with (lowest value > 0) * 0.001

    PolyFit::polygrade = polygrade;
}
PolyFit::PolyFit(const Data& x, const Data& y, const Data& sy, const int polygrade)
{
    if(x.get_entries() != y.get_entries())    std::cerr << "Data vector x and y have different sizes." << std::endl;
    if(x.get_entries() != sy.get_entries())   std::cerr << "Data vector x and sy have different sizes." << std::endl;

    PolyFit::n = x.get_entries();

    PolyFit::x = x.get_data();
    PolyFit::y = y.get_data();
    PolyFit::sy = sy.get_data();

    PolyFit::polygrade = polygrade;
}
PolyFit::~PolyFit(){}


/**
 * @brief Creates a fit for the entered data, using a function passed by the user.
 * 
 * @param formula the function can be: 
 *      - "poln", with n any integer from 0 to 99
 *      - ""
 */
void PolyFit::fit(const int polygrade)
{
    PolyFit::polygrade = polygrade;

    Eigen::VectorXd v;                                  // vector v in documentation
    
    Eigen::VectorXd x_vec(PolyFit::n), y_vec(PolyFit::n), sy_vec(PolyFit::n), yfit_vec(PolyFit::n);

    for(int i = 0; i < n; i++)   x_vec(i) = PolyFit::x.at(i);
    for(int i = 0; i < n; i++)   y_vec(i) = PolyFit::y.at(i);
    for(int i = 0; i < n; i++)   sy_vec(i) = PolyFit::sy.at(i);

    Eigen::MatrixXd matrix(polygrade+1, polygrade+1);           // for a k-degree polynomial a (k+1)*(k+1) matrix is needed
    for(int i = 0; i < polygrade+1; i++)
    {
        for(int j = 0; j < polygrade+1; j++)
        {
            std::vector<double> sum_elem;
            for(int k = 0; k < n; k++)  sum_elem.push_back( pow(x_vec(k),i+j)/pow(sy_vec(k),2) );
            matrix(i,j) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
        }
    }
    for (int i = 0; i < polygrade+1; i++)
    {
        std::vector<double> temp;
        for(int j = 0; j < polygrade+1; j++)    temp.push_back(matrix.inverse()(i,j));
        PolyFit::matrix.push_back(temp);
    }
    
    v.resize(polygrade+1);
    for(int i = 0; i < polygrade+1; i++)
    {
        std::vector<double> sum_elem;
        for(int k = 0; k < n; k++)  sum_elem.push_back( y_vec(k)*pow(x_vec(k),i)/pow(sy_vec(k),2) );
        v(i) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
    }
    PolyFit::DoF = PolyFit::n - polygrade - 1;
    Eigen::VectorXd coeff_vec = matrix.inverse() * v;
    for(int i = 0; i < polygrade+1; i++)   PolyFit::coeff.push_back(coeff_vec(i));
    
    std::vector<double> sum_elem;
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < polygrade+1; i++)
        {
            yfit_vec(k) += coeff_vec(i) * pow(x_vec(k), i);
        } 
        PolyFit::yfit.push_back(yfit_vec(k));
        double num = y_vec(k) - yfit_vec(k); 
        sum_elem.push_back( pow(num,2)/pow(sy_vec(k),2) );
    }
    std::cout << "check sum elem for chi" << std::endl;
    for(int i = 0; i < n; i++)  std::cout << sum_elem.at(i) << std::endl;
    std::cout << std::endl;
    PolyFit::chi_squared = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);

    // print fit results
    std::cout << std::endl << "//////////////////////////////////////////////////////" << std::endl;
    std::cout << "                   Fit results:" << std::endl;
    std::cout << "//////////////////////////////////////////////////////" << std::endl;
    std::cout << "       Grade of the polynomial = " << polygrade << std::endl;
    for (int i = 0; i < coeff.size(); i++)
    {
        printf("p%d", i);
        std::cout << " = (" << get_parameter(i) << " ± " << get_parerror(i) << ") " << std::endl;
    }
    std::cout << "//////////////////////////////////////////////////////" << std::endl;
    std::cout << "chi = " << PolyFit::chi_squared << std::endl;
    std::cout << "pvalue = " << PolyFit::p_value << std::endl;
    std::cout << "DoF = " << PolyFit::DoF << std::endl;
    std::cout << "//////////////////////////////////////////////////////" << std::endl << std::endl;
    
}

void PolyFit::set_pvalue(const double chi_squared)
{

}
#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "../Eigen/Dense"
#include "../include_t/polyfit_t.hpp"
#include "../include_t/data_t.hpp"
#include "../include_t/udouble_t.hpp"

/**
 * @brief Incomplete gamma function. Will be used to evaluate the chi-squared pvalue of a fit.
 * Reference at https://www.codeproject.com/Articles/432194/How-to-Calculate-the-Chi-Squared-P-Value.
 * 
 * @param S 
 * @param Z 
 * @return double 
 */
static double igf(double S, double Z)
{
    if(Z < 0.0)
    {
	return 0.0;
    }
    double Sc = (1.0 / S);
    Sc *= pow(Z, S);
    Sc *= exp(-Z);
 
    double Sum = 1.0;
    double Nom = 1.0;
    double Denom = 1.0;
 
    for(int I = 0; I < 200; I++)
    {
	Nom *= Z;
	S++;
	Denom *= S;
	Sum += (Nom / Denom);
    }
 
    return Sum * Sc;
}


template <class T>
PolyFit<T>::PolyFit(const std::vector<Udouble<T>> x, const std::vector<Udouble<T>> y, const int polygrade)
{
    if(x.size() != y.size())    std::cerr << "Data vector x and y have different sizes." << std::endl;

    PolyFit<T>::n = x.size();

    for(int i = 0; i < x.size(); i++)   PolyFit<T>::x.push_back(x.at(i).get_value());
    for(int i = 0; i < y.size(); i++)   PolyFit<T>::y.push_back(y.at(i).get_value());
    for(int i = 0; i < y.size(); i++)   PolyFit<T>::sy.push_back(y.at(i).get_error());

    // swap zeros in sy vector with (lowest value > 0) * 0.001

    PolyFit<T>::polygrade = polygrade;
}
template <class T>
PolyFit<T>::PolyFit(const Data<T>& x, const Data<T>& y, const Data<T>& sy, const int polygrade)
{
    if(x.get_entries() != y.get_entries())    std::cerr << "Data vector x and y have different sizes." << std::endl;
    if(x.get_entries() != sy.get_entries())   std::cerr << "Data vector x and sy have different sizes." << std::endl;

    PolyFit<T>::n = x.get_entries();

    PolyFit<T>::x = x.get_data();
    PolyFit<T>::y = y.get_data();
    PolyFit<T>::sy = sy.get_data();

    PolyFit<T>::polygrade = polygrade;
}
template <class T>
PolyFit<T>::~PolyFit<T>(){}


/**
 * @brief Creates a fit for the entered data, using a function passed by the user.
 * 
 * @param formula the function can be: 
 *      - "poln", with n any integer from 0 to 99
 *      - ""
 */
template <class T>
void PolyFit<T>::fit(const int polygrade)
{
    PolyFit<T>::polygrade = polygrade;

    Eigen::VectorXd v;                                  // vector v in documentation
    
    Eigen::VectorXd x_vec(PolyFit<T>::n), y_vec(PolyFit<T>::n), sy_vec(PolyFit<T>::n), yfit_vec(PolyFit<T>::n);

    for(int i = 0; i < n; i++)   x_vec(i) = PolyFit<T>::x.at(i);
    for(int i = 0; i < n; i++)   y_vec(i) = PolyFit<T>::y.at(i);
    for(int i = 0; i < n; i++)   sy_vec(i) = PolyFit<T>::sy.at(i);

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
        PolyFit<T>::matrix.push_back(temp);
    }
    
    v.resize(polygrade+1);
    for(int i = 0; i < polygrade+1; i++)
    {
        std::vector<double> sum_elem;
        for(int k = 0; k < n; k++)  sum_elem.push_back( y_vec(k)*pow(x_vec(k),i)/pow(sy_vec(k),2) );
        v(i) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
    }
    PolyFit<T>::DoF = PolyFit<T>::n - polygrade - 1;
    Eigen::VectorXd coeff_vec = matrix.inverse() * v;
    for(int i = 0; i < polygrade+1; i++)   PolyFit<T>::coeff.push_back(coeff_vec(i));
    
    std::vector<double> sum_elem;
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < polygrade+1; i++)    yfit_vec(k) += coeff_vec(i) * pow(x_vec(k), i);
        
        PolyFit<T>::yfit.push_back(yfit_vec(k));
        double num = y_vec(k) - yfit_vec(k); 
        sum_elem.push_back( pow(num,2)/pow(sy_vec(k),2) );
    }
    std::cout << "check sum elem for chi" << std::endl;
    for(int i = 0; i < n; i++)  std::cout << sum_elem.at(i) << std::endl;
    std::cout << std::endl;
    PolyFit<T>::chi_squared = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);

    // print fit results
    std::cout << std::endl  << "//////////////////////////////////////////////////////" << std::endl;
    std::cout               << "                   Fit results:" << std::endl;
    std::cout               << "//////////////////////////////////////////////////////" << std::endl;
    std::cout               << "       Grade of the polynomial = " << polygrade << std::endl;
    for (int i = 0; i < coeff.size(); i++)
    {
        printf("p%d", i);
        std::cout << " = (" << get_parameter(i) << " ± " << get_parerror(i) << ") " << std::endl;
    }
    std::cout               << "//////////////////////////////////////////////////////" << std::endl;
    std::cout               << "chi = " << PolyFit<T>::chi_squared << std::endl;
    std::cout               << "pvalue = " << PolyFit<T>::p_value << std::endl;
    std::cout               << "DoF = " << PolyFit<T>::DoF << std::endl;
    std::cout               << "//////////////////////////////////////////////////////" << std::endl << std::endl;
    
}

/**
 * @brief Function to set the chi-squared pvalue from a fit. The function is implemented using an 
 * incomplete gamma function. Reference at https://www.codeproject.com/Articles/432194/How-to-Calculate-the-Chi-Squared-P-Value.
 * 
 * @tparam T 
 */
template <class T>
void PolyFit<T>::set_pvalue()
{

    if(PolyFit<T>::chi_squared < 0 || PolyFit<T>::DoF < 1)
    {
        return 0.0;
    }
    double K = ((double)PolyFit<T>::DoF) * 0.5;
    double X = PolyFit<T>::chi_squared * 0.5;
    if(PolyFit<T>::DoF == 2)
    {
	return exp(-1.0 * X);
    }
 
    double PValue = igf(K, X);
    if(isnan(PValue) || isinf(PValue) || PValue <= 1e-8)
    {
        return 1e-14;
    } 

    PValue /= std::tgamma(K); 
	
    return (1.0 - PValue);
}
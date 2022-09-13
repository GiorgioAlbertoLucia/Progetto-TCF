#include <iostream>
#include <math.h>
#include <vector>
#include <numeric>

#include "../Eigen/Dense"
#include "../include/polyfit.hpp"

/* USEFUL FUNCTUIONS */

/**
 * @brief Incomplete gamma function. Will be used to evaluate the chi-squared pvalue of a fit.
 * Reference at https://www.codeproject.com/Articles/432194/How-to-Calculate-the-Chi-Squared-P-Value.
 * 
 * @param S 
 * @param Z 
 * @return double 
 */
static double igf(double S, double Z) {
	if (Z < 0.0) {
		return 0.0;
	}
	double Sc = (1.0 / S);
	Sc *= pow(Z, S);
	Sc *= std::exp(-Z);

	double Sum = 1.0;
	double Nom = 1.0;
	double Denom = 1.0;

	for (int I = 0; I < 200; I++) {
		Nom *= Z;
		S++;
		Denom *= S;
		Sum += (Nom / Denom);
	}

	return Sum * Sc;
}



/* MEMBER FUNCTIONS */

PolyFit::PolyFit(const std::vector<Udouble> x, const std::vector<Udouble> y, const int polygrade) 
{
	assert(x.size() == y.size());

	PolyFit::n = x.size();

	for (int i = 0; i < x.size(); i++) PolyFit::x.push_back(x.at(i).get_value());
	for (int i = 0; i < y.size(); i++) PolyFit::y.push_back(y.at(i).get_value());
	for (int i = 0; i < y.size(); i++) PolyFit::sy.push_back(y.at(i).get_error());

	// avoid division by zero
	double min = sy.at(0);
	for (double i: PolyFit::sy) {
		if (min > i && i != 0) min = i;
	}
	for (double i: PolyFit::sy) {
		if (i == 0) i = min * 0.001;
	}


	PolyFit::polygrade = polygrade;
}
PolyFit::PolyFit(const std::vector<double> x, const std::vector<double> y, const std::vector<double> sy, const int polygrade) 
{
	assert(x.size() == y.size());
	assert(x.size() == sy.size());

	PolyFit::n = x.size();

	PolyFit::x = x;
	PolyFit::y = y;
	PolyFit::sy = sy;

	// avoid division by zero
	double min = sy.at(0);
	for (double i: PolyFit::sy) {
		if (min > i && i != 0) min = i;
	}
	for (double i: PolyFit::sy) {
		if (i == 0) i = min * 0.001;
	}

	PolyFit::polygrade = polygrade;
}
PolyFit::PolyFit(Data <Udouble> &x, Data <Udouble> &y, const int polygrade) 
{
	assert(x.size() == y.size());

	PolyFit::n = x.size();

	for (int i = 0; i < x.size(); i++) 	PolyFit::x.push_back(x.at(i).get_value());
	for (int i = 0; i < y.size(); i++)	PolyFit::y.push_back(y.at(i).get_value());
	for (int i = 0; i < y.size(); i++)	PolyFit::sy.push_back(y.at(i).get_error());

	// avoid division by zero
	double min = sy.at(0);
	for (double i: PolyFit::sy) {
		if (min > i && i != 0) min = i;
	}
	for (double i: PolyFit::sy) {
		if (i == 0) i = min * 0.001;
	}


	PolyFit::polygrade = polygrade;
}
PolyFit::PolyFit(Data<double> &x, Data<double> &y, Data<double> &sy, const int polygrade) 
{
	assert(x.size() == y.size());
	assert(x.size() == sy.size());

	PolyFit::n = x.size();

	PolyFit::x = x.get_data();
	PolyFit::y = y.get_data();
	PolyFit::sy = sy.get_data();

	// avoid division by zero
	double min = sy.at(0);
	for (double i: PolyFit::sy) {
		if (min > i && i != 0) min = i;
	}
	for (double i: PolyFit::sy) {
		if (i == 0) i = min * 0.001;
	}

	PolyFit::polygrade = polygrade;
}
PolyFit::~PolyFit() {}




/**
 * @brief Creates a fit for the entered data, using a function passed by the user.
 * 
 * @param polygrade: grade of the polynomial
 */
void PolyFit::fit(const int polygrade) {
	
	PolyFit::polygrade = polygrade;
	Eigen::VectorXd v;                                  // vector v in documentation
	Eigen::VectorXd x_vec(PolyFit::n), y_vec(PolyFit::n), sy_vec(PolyFit::n), yfit_vec(PolyFit::n);

	for (int i = 0; i < n; i++) x_vec(i) = PolyFit::x.at(i);
	for (int i = 0; i < n; i++) y_vec(i) = PolyFit::y.at(i);
	for (int i = 0; i < n; i++) sy_vec(i) = PolyFit::sy.at(i);

	// Solve the system with a matrix
	//_______________________________________

	// create a matrix
	Eigen::MatrixXd matrix(polygrade + 1,
						   polygrade + 1);           // for a k-degree polynomial a (k+1)*(k+1) matrix is needed
	for (int i = 0; i < polygrade + 1; i++) {
		for (int j = 0; j < polygrade + 1; j++) {
			std::vector<double> sum_elem;
			for (int k = 0; k < n; k++) sum_elem.push_back(pow(x_vec(k), i + j) / pow(sy_vec(k), 2));
			matrix(i, j) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0.);
		}
	}
	// invert the matrix (and store it as a vector of vectors as a member function)
	for (int i = 0; i < polygrade + 1; i++) {
		std::vector<double> temp;
		Eigen::MatrixXd inv = matrix.inverse();
		for (int j = 0; j < polygrade + 1; j++) temp.push_back(inv(i, j));
		PolyFit::matrix.push_back(temp);
	}
	// create the vector to multiply the inverted matrix with
	v.resize(polygrade + 1);
	for (int i = 0; i < polygrade + 1; i++) {
		std::vector<double> sum_elem;
		for (int k = 0; k < n; k++) sum_elem.push_back(y_vec(k) * pow(x_vec(k), i) / pow(sy_vec(k), 2));
		v(i) = std::accumulate(sum_elem.begin(), sum_elem.end(), 0);
	}
	// calculate the vector of coefficient and save it as a data member
	Eigen::VectorXd coeff_vec = matrix.inverse() * v;
	for (int i = 0; i < polygrade + 1; i++) PolyFit::coeff.push_back(coeff_vec(i));

	// Evaluate DoF, chi, pvalue
	// ________________________________________

	PolyFit::DoF = PolyFit::n - polygrade - 1;
	PolyFit::set_chi();
	PolyFit::set_pvalue();

	// Print fit results
	// _________________________________________

	std::cout << std::endl << "//////////////////////////////////////////////////////" << std::endl;
	std::cout <<              "                     Fit results:                     " << std::endl;
	std::cout << "//////////////////////////////////////////////////////" << std::endl;
	std::cout << "             	Degree of the polynomial = " << polygrade << std::endl << std::endl;
	std::cout << "y = ";
	for (int i = 0; i < coeff.size(); i++) {
		std::cout << "p" << i << "*x^" << i;
		if (i != coeff.size() - 1) {
			std:: cout << " + ";
		} else {
			std::cout << std::endl;
		}
	}
	for (int i = 0; i < coeff.size(); i++) {
		printf("p%d", i);
		std::cout << " = (" << get_parameter(i) << " ± " << get_parerror(i) << ") " << std::endl;
	}
	std::cout << "//////////////////////////////////////////////////////" << std::endl << std::endl;
	std::cout << "chi = " << PolyFit::chi_squared << std::endl;
	std::cout << "pvalue = " << PolyFit::p_value << std::endl;
	std::cout << "DoF = " << PolyFit::DoF << std::endl;
	std::cout << "//////////////////////////////////////////////////////" << std::endl << std::endl;

}

/**
 * @brief This function is implemented to be used only in the fit process or after a fit is done (In this way all the needed
 * parameters and data member are already set).
 * 
 */
void PolyFit::set_chi()
{
	Eigen::VectorXd x_vec(PolyFit::n), y_vec(PolyFit::n), sy_vec(PolyFit::n), yfit_vec(PolyFit::n);
	for (int i = 0; i < n; i++) x_vec(i) = PolyFit::x.at(i);
	for (int i = 0; i < n; i++) y_vec(i) = PolyFit::y.at(i);
	for (int i = 0; i < n; i++) sy_vec(i) = PolyFit::sy.at(i);
	
	std::vector<double> sum_elem, yfit;
	for (int k = 0; k < n; k++) 
	{
		yfit_vec(k) = 0;
		for (int i = 0; i < polygrade + 1; i++) yfit_vec(k) += PolyFit::coeff.at(i) * pow(x_vec(k), i);
		double num = y_vec(k) - yfit_vec(k);
		sum_elem.push_back(pow(num, 2) / pow(sy_vec(k), 2));
	}

	PolyFit::chi_squared = std::accumulate(sum_elem.begin(), sum_elem.end(), 0.);	
}

/**
 * @brief Function to set the chi-squared pvalue from a fit. The function is implemented using an 
 * incomplete gamma function. Reference at https://www.codeproject.com/Articles/432194/How-to-Calculate-the-Chi-Squared-P-Value.
 * 
 * @tparam T 
 */
void PolyFit::set_pvalue() {

	if (PolyFit::chi_squared < 0 || PolyFit::DoF < 1) {
		PolyFit::p_value = 0.0;
	}
	double K = ((double) PolyFit::DoF) * 0.5;
	double X = PolyFit::chi_squared * 0.5;
	if (PolyFit::DoF == 2) {
		PolyFit::p_value = std::exp(-1.0 * X);
	}

	double PValue = igf(K, X);
	if (isnan(PValue) || isinf(PValue) || PValue <= 1e-8) {
		PolyFit::p_value = 1e-14;
	}

	PValue /= std::tgamma(K);

	PolyFit::p_value = (1.0 - PValue);
}
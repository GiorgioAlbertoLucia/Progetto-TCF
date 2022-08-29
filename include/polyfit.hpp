#ifndef POLYFIT_T_H
#define POLYFIT_T_H

#include <vector>
#include <string>

#include "../Eigen/Dense"
#include "../include/udouble.hpp"
#include "../include/data.hpp"

class PolyFit {
public:
	PolyFit() {};

	PolyFit(const std::vector<Udouble>, const std::vector<Udouble>, const int = 1);

	PolyFit(const std::vector<double>, const std::vector<double>, const std::vector<double>, const int = 1);

	PolyFit(Data<double> &, Data<double> &, Data<double> &, const int = 1);

	PolyFit(Data<Udouble> &, Data<Udouble> &, const int = 1);

	PolyFit(const PolyFit &);

	~PolyFit();

	void fit(std::vector<double>, const int = 1);

	void set_chi();

	void set_pvalue();

	const double get_parameter(int i) const { return coeff.at(i); };

	const double get_parerror(int i) const { return sqrt(matrix.at(i).at(i)); };

	const double get_chisquared() const { return chi_squared; };

	const double get_pvalue() const { return p_value; };

	const double get_DoF() const { return DoF; };


private:
	int n;                                            // size of the input vectors
	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> sy;                              // errors on the y

	std::vector<double> coeff;                           // coefficients vector
	std::vector<std::vector<double>> matrix;             // coefficient matrix (U in documentation - wolfram)

	int DoF;
	double chi_squared;
	double p_value;

	int polygrade;
};

#endif
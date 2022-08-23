#include <iostream>
#include <cmath>
#include <map>

#include "../include_t/partder.hpp"

int PartDer::count = 0;

PartDer::PartDer() {
	count++;
	PartDer::label = std::string("");
	for (int i = 0; i < count; i++) PartDer::label += "p";
}

PartDer::PartDer(const double x, const char *label) {
	count++;
	PartDer::f = x;
	PartDer::label = label;
	if (PartDer::label == "") for (int i = 0; i < count; i++) PartDer::label += "p";
	PartDer::df = {{PartDer::label, 1.},};
}

PartDer::PartDer(const double x, const std::map<std::string, double> df, const char *label) {
	count++;
	PartDer::f = x;
	PartDer::df = df;

	std::map<std::string, double> m = PartDer::df;
	if (m.size() == 1)
		for (std::map<std::string, double>::const_iterator i = m.begin(); i != m.end(); i++)
			PartDer::label = i->first;
	else PartDer::label = std::string(label);
	if (PartDer::label == "") for (int i = 0; i < count; i++) PartDer::label += "p";
}

PartDer::PartDer(const PartDer &derivative) {
	count++;
	PartDer::f = derivative.f;
	PartDer::df = derivative.df;

	std::string label("");
	for (int i = 0; i < count; i++) label += "p";
	set_label(label);

}

PartDer PartDer::operator+(const PartDer &g) {
	PartDer h;
	h.f = PartDer::f + g.f;

	// checks if the two functions are functions of the same variable. If they are, the partial derivative is
	// determined via standard rules of differentiation, if not the partial derivative of the function of that
	// variable is set

	for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++) {
		if (g.df.find(i->first) != g.df.end()) {
			double diff = i->second + g.df.at(i->first);
			h.df.insert(std::make_pair(i->first, diff));
		} else if (g.df.find(i->first) == g.df.end()) {
			h.df.insert(std::make_pair(i->first, i->second));
		}
	}
	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}


	return h;
}

PartDer PartDer::operator-(const PartDer &g) {
	PartDer h;
	h.f = PartDer::f - g.f;


	for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++) {
		if (g.df.find(i->first) != g.df.end()) {
			double diff = i->second - g.df.at(i->first);
			h.df.insert(std::make_pair(i->first, diff));
		} else if (g.df.find(i->first) == g.df.end()) {
			h.df.insert(std::make_pair(i->first, i->second));
		}
	}
	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}


	return h;
}

PartDer PartDer::operator*(const PartDer &g) {
	PartDer h;
	h.f = PartDer::f * g.f;


	for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++) {
		if (g.df.find(i->first) != g.df.end()) {
			double diff = i->second * g.f + f * g.df.at(i->first);
			h.df.insert(std::make_pair(i->first, diff));
		} else if (g.df.find(i->first) == g.df.end()) {
			double diff = i->second * g.f;
			h.df.insert(std::make_pair(i->first, diff));
		}
	}
	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * f;
		h.df.insert(std::make_pair(i->first, diff));
	}


	return h;
}

PartDer PartDer::operator/(const PartDer &g) {
	PartDer h;
	h.f = PartDer::f / g.f;


	for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++) {
		if (g.df.find(i->first) != g.df.end()) {
			double diff = i->second * g.f - f * g.df.at(i->first) / pow(g.f, 2);
			h.df.insert(std::make_pair(i->first, diff));
		} else if (g.df.find(i->first) == g.df.end()) {
			double diff = i->second / g.f;
			h.df.insert(std::make_pair(i->first, diff));
		}
	}
	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * f / pow(g.f, 2);
		h.df.insert(std::make_pair(i->first, i->second));
	}


	return h;
}

PartDer sin(const PartDer &g) {
	PartDer h;
	h.f = std::sin(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = cos(g.f) * i->second;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer cos(const PartDer &g) {
	PartDer h;
	h.f = std::cos(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = -sin(g.f) * i->second;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer tan(const PartDer &g) {
	PartDer h;
	h.f = std::tan(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / pow(cos(g.f), 2);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer sinh(const PartDer &g) {
	PartDer h;
	h.f = std::sinh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = cosh(g.f) * i->second;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer cosh(const PartDer &g) {
	PartDer h;
	h.f = std::cosh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = sinh(g.f) * i->second;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer tanh(const PartDer &g) {
	PartDer h;
	h.f = std::tanh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / pow(cosh(g.f), 2);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer asin(const PartDer &g) {
	PartDer h;
	h.f = std::asin(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / sqrt(1 - pow(g.f, 2));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer acos(const PartDer &g) {
	PartDer h;
	h.f = std::acos(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / sqrt(1 - pow(g.f, 2));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer atan(const PartDer &g) {
	PartDer h;
	h.f = std::atan(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / sqrt(1 + pow(g.f, 2));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer asinh(const PartDer &g) {
	PartDer h;
	h.f = std::asinh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / sqrt(1 + pow(g.f, 2));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer acosh(const PartDer &g) {
	PartDer h;
	h.f = std::acosh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / (sqrt(1 - g.f) * sqrt(1 + g.f));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer atanh(const PartDer &g) {
	PartDer h;
	h.f = std::atanh(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / sqrt(1 - pow(g.f, 2));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer exp(const PartDer &g) {
	PartDer h;
	h.f = exp(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * h.f;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer pow(const PartDer &g, const double n) {
	PartDer h;
	h.f = pow(g.f, n);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * n * pow(g.f, n - 1);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer pow(const PartDer &g, const int n) {
	PartDer h;
	h.f = pow(g.f, n);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * n * pow(g.f, n - 1);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer pow(const PartDer &g, const PartDer &n) {
	PartDer h;
	h.f = pow(g.f, n.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second * n.f * pow(g.f, n.f - 1);
		h.df.insert(std::make_pair(i->first, diff));
	}
	for (std::map<std::string, double>::const_iterator i = n.df.begin(); i != n.df.end(); i++) {
		double diff = i->second * pow(g.f, n.f) * log(g.f);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer log(const PartDer &g) {
	PartDer h;
	h.f = log(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / g.f;
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer log10(const PartDer &g) {
	PartDer h;
	h.f = log10(g.f);

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = i->second / (g.f * log(10));
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer operator+(const double c, const PartDer &g) {
	PartDer h;
	h.f = c + g.f;

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}

	return h;
}

PartDer operator-(const double c, const PartDer &g) {
	PartDer h;
	h.f = c - g.f;

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}

	return h;
}

PartDer operator*(const double c, const PartDer &g) {
	PartDer h;
	h.f = c * g.f;

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}

	return h;
}

PartDer operator/(const double c, const PartDer &g) {
	PartDer h;
	h.f = c / g.f;

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		double diff = -c / pow(g.f, 2);
		h.df.insert(std::make_pair(i->first, diff));
	}

	return h;
}

PartDer operator/(const PartDer &g, const double c) {
	PartDer h;
	h.f = g.f / c;

	for (std::map<std::string, double>::const_iterator i = g.df.begin(); i != g.df.end(); i++) {
		h.df.insert(std::make_pair(i->first, i->second));
	}

	return h;
}


void PartDer::print() {
	std::cout << "f = " << PartDer::f << std::endl;
	std::cout << "Partial derivatives: " << std::endl;

	for (std::map<std::string, double>::const_iterator i = df.begin(); i != df.end(); i++) {
		std::cout << "df/d" << i->first << " = " << i->second << std::endl;
	}

}

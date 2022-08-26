#include "../include_t/data_t.hpp"

#include <iostream>


template<>
void print_element(double element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << std::fixed
			  << element << "\t";
}

template<>
void print_element(float element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << std::fixed
			  << element << "\t";
}

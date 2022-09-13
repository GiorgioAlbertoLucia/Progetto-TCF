#ifndef TRIGONOMETRICTEMPLATE_H
#define TRIGONOMETRICTEMPLATE_H

#include <math.h>

namespace trigonometrictemplate {
    template <typename T> inline T sin(const T& v) {return std::sin(v);};
    template <typename T> inline T cos(const T& v) {return std::cos(v);};
    template <typename T> inline T tan(const T& v) {return std::tan(v);};
    template <typename T> inline T sinh(const T& v) {return std::sinh(v);};
    template <typename T> inline T cosh(const T& v) {return std::cosh(v);};
    template <typename T> inline T tanh(const T& v) {return std::tanh(v);};
    template <typename T> inline T asin(const T& v) {return std::asin(v);};
    template <typename T> inline T acos(const T& v) {return std::acos(v);};
    template <typename T> inline T atan(const T& v) {return std::atan(v);};
    template <typename T> inline T asinh(const T& v) {return std::asinh(v);};
    template <typename T> inline T acosh(const T& v) {return std::acosh(v);};
    template <typename T> inline T atanh(const T& v) {return std::atanh(v);};
    template <typename T> inline T 
    template <typename T> inline T exp(const T& v) {return std::exp(v);};
	template <typename T> inline T pow(const T& v, const double n) {return std::pow(v, n);};
	template <typename T> inline T pow(const T& v, const int n) {return std::pow(v, n);};
	template <typename T> inline T log(const T& v) {return std::log(v);};
	template <typename T> inline T log10(const T& v) {return std::log10(v);};
}



#endif
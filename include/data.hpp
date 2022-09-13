#ifndef DATA_H
#define DATA_H

#include "../include/file.hpp"
#include "../include/fileFactory.hpp"

#include <string_view>
#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <functional>
#include <random>


/* TEMPLATE DECLARATION */

template<class T>
class Data;

template<class T>
std::ostream &operator<<(std::ostream &, const Data<T> &);
template<class T>
Data<T> operator+(Data<T> , Data<T> );
template<class T>
Data<T> operator-(Data<T> , Data<T> );
template<class T>
Data<T> operator*(Data<T> , Data<T> );
template<class T>
Data<T> operator*(double, Data<T> );                                 // multiply by a scalar
template<class T>
Data<T> operator*(int, Data<T> );
template<class T>
Data<T> operator*(Data<T> , const int);                                 // multiply by a scalar
template<class T>
Data<T> operator*(const int, Data<T>);   
template<class T>
Data<T> operator*(Data<T> , const double);
template<class T>
Data<T> operator*(const double, Data<T>);
template<class T>
Data<T> operator/(Data<T> , Data<T> );
template<class T>
Data<T> operator/(Data<T> , const int);
template<class T>
Data<T> operator/(Data<T> , const double);

template<class T>
Data<T> sin(Data<T> );
template<class T>
Data<T> cos(Data<T> );
template<class T>
Data<T> tan(Data<T> );
template<class T>
Data<T> sinh(Data<T> );
template<class T>
Data<T> cosh(Data<T> );
template<class T>
Data<T> tanh(Data<T> );
template<class T>
Data<T> asin(Data<T> );
template<class T>
Data<T> acos(Data<T> );
template<class T>
Data<T> atan(Data<T> );
template<class T>
Data<T> asinh(Data<T> );
template<class T>
Data<T> acosh(Data<T> );
template<class T>
Data<T> atanh(Data<T> );
template<class T>
Data<T> exp(Data<T> );
template<class T>
Data<T> pow(Data<T> , const double);
template<class T>
Data<T> pow(Data<T> , const int);
template<class T>
Data<T> pow(Data<T> , Data<T> );
template<class T>
Data<T> log(Data<T> );
template<class T>
Data<T> log10(Data<T> );


/**
 * @brief Data object. Stores a vector of values and can do basic operations with it. You can load the vector directly from a data file.
 * 
 * @tparam T Any
 */
template<class T>
class Data {
public:
	Data() {};
	Data(const std::vector<T>, const char * = "");

	Data(const char *, const int, const char * = "");   // file_path, file_column and data_name
	Data(const char *, const int, const int, const char * = "");
	Data(const Data<T> &);                                  // copy constructor
	~Data();

	// setter / getter	
	inline Data<T> &set_data(const char *, const int, const int = 0);
	inline Data<T> &set_data(const std::vector<T> data) {
		Data::data = data;
		return *this;
	};
	inline Data<T> &set_name(const char *name = "") {
		Data::name = std::string(name);
		return *this;
	};

	inline std::vector<T> get_data() const { return Data::data; };
	inline std::string get_name() const { return Data::name; };

	inline void describe() const;
	inline void head(const int = 5) const;

	inline int size() const { return Data::data.size(); };
	inline T &at(const int i) { return Data::data.at(i); };

	inline std::vector<double> values();
	inline std::vector<double> errors();

	inline Data<T> &add(const T &element) {
		Data::data.push_back(element);
		return *this;
	};
	inline Data<T> &replace(const T &value, const int i) {
		Data::data.at(i) = value;
		return *this;
	};

	// operators

	friend std::ostream &operator
	<<<T>(std::ostream &, const Data<T> &);

	friend Data<T> operator+<T>(Data<T> , Data<T> );
	friend Data<T> operator-<T>(Data<T> , Data<T> );

	friend Data<T> operator*<T>(Data<T> , Data<T> );
	friend Data<T> operator*<T>(Data<T> , const int);   
	friend Data<T> operator*<T>(const int n, Data<T> data)		{ return data * n; };                             
	friend Data<T> operator*<T>(Data<T> , const double);
	friend Data<T> operator*<T>(const double n, Data<T> data) 	{ return data * n; };
	friend Data<T> operator/<T>(Data<T> , Data<T> );
	friend Data<T> operator/<T>(Data<T> , const int);
	friend Data<T> operator/<T>(Data<T> , const double);

	friend Data<T> sin<T>(Data<T> );
	friend Data<T> cos<T>(Data<T> );
	friend Data<T> tan<T>(Data<T> );
	friend Data<T> sinh<T>(Data<T> );
	friend Data<T> cosh<T>(Data<T> );
	friend Data<T> tanh<T>(Data<T> );
	friend Data<T> asin<T>(Data<T> );
	friend Data<T> acos<T>(Data<T> );
	friend Data<T> atan<T>(Data<T> );
	friend Data<T> asinh<T>(Data<T> );
	friend Data<T> acosh<T>(Data<T> );
	friend Data<T> atanh<T>(Data<T> );
	friend Data<T> exp<T>(Data<T> );
	friend Data<T> pow<T>(Data<T> , const double);
	friend Data<T> pow<T>(Data<T> , const int);
	friend Data<T> pow<T>(Data<T> , Data<T> );
	friend Data<T> log<T>(Data<T> );
	friend Data<T> log10<T>(Data<T> );

	bool operator==(const Data &);
	bool operator!=(const Data &itself) { return !(*this == itself); };

	T &operator[](int n) { return Data::at(n); };
	Data<T> operator^(const int n) { return pow(*this, n); };
	Data<T> operator^(const double n) { return pow(*this, n); };
	Data<T> operator^(const Data<T> &n) { return pow(*this, n); };

	inline Data<T>& add_noise(const double, const double);

	// statistical functions

	const double mean() const;
	const double std() const;
	const double min() const;
	const double max() const;

private:
	std::vector<T> data;
	std::string name;

};





//////////////////////////////////////////////////
//          TEMPLATE SPECIALIZATION             //
//////////////////////////////////////////////////


template <>
inline Data<Udouble>& Data<Udouble>::set_data(const char * file_path, const int file_col, const int err_col);

template <> 
inline Udouble& Data<Udouble>::at(const int);



template <> 
inline Udouble& Data<Udouble>::operator[](int n);



template<>
inline const double Data<std::string>::mean() const;
template<>
inline const double Data<Udouble>::mean() const;

template<>
inline const double Data<std::string>::std() const;
template<>
inline const double Data<Udouble>::std() const;

template<>
inline const double Data<std::string>::min() const;
template<>
inline const double Data<Udouble>::min() const;

template<>
inline const double Data<std::string>::max() const;
template<>
inline const double Data<Udouble>::max() const;







//////////////////////////////////////////////////
//              IMPLEMENTATION                  //
//////////////////////////////////////////////////


/*  USEFUL FUNCTIONS  */

const char separator = ' ';
const int width = 6;
const int lenght = 2;

template<typename T>
extern inline void print_element(T element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << element << "\t";
}

template<>
inline void print_element(double element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << std::fixed
			  << element << "\t";
}

template<>
inline void print_element(float element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << std::fixed
			  << element << "\t";
}

template<>
inline void print_element(Udouble element, const char separator, const int width, const int lenght) {
	std::cout << std::left << std::setw(width) << std::setfill(separator) << std::setprecision(lenght) << std::fixed
			  << element << "\t";
}



/*  MEMBER FUNCTIONS  */

/**
 * @brief Construct a new Data:: Data object.
 * @param file_path path of the file the data will be imported from. 
 * @param file_column column of the file the data will be imported from.
 * @param name name of the data distribution.
 */
template<class T>
Data<T>::Data(const std::vector<T> data, const char *name) {
	set_name(name);
	Data::data = data;
}
/**
 * @brief Construct a new Data:: Data object.
 * @param file_path path of the file the data will be imported from. 
 * @param file_column column of the file the data will be imported from.
 * @param name name of the data distribution.
 */
template<class T>
Data<T>::Data(const char *file_path, const int file_column, const char *name) {
	set_name(name);
	set_data(file_path, file_column);
}

/**
 * @brief Specific constructor for Udouble templates
 * 
 * @param file_path 
 * @param file_column 
 * @param err_column 
 * @param name 
 */
template<>
inline Data<Udouble>::Data(const char *file_path, const int file_column, const int err_column, const char *name)	{
	set_name(name);
	set_data(file_path, file_column, err_column);
}
/**
 * @brief Copy Constructor. 
 * Construct a new Data:: Data object.
 * @param data 
 */
template<class T>
Data<T>::Data(const Data<T> &data) {
	Data::data = data.data;
	Data::name = data.name;
}
/**
 * @brief Destroy the Data:: Data object
 */
template<class T>
Data<T>::~Data() {

}



// setter and getter
/**
 * @brief Stores data into the data vector from a column of the file. If the first line is a string, it will be automatically set
 * as the name of the Data object.
 * @param file_path 
 * @param file_column 
 * @return Data& 
 */
template<class T>
Data<T> &Data<T>::set_data(const char *file_path, const int file_col, const int err_col) {
	FileFactory *factory = new FileFactory();

	if (Data::name == "" && factory->firstline_is_text(file_path)) {
		Data::data = factory->vector_column<T>(file_path, file_col, 1);
		Data::name = factory->get_element(file_path, 0, file_col);
	} else if (factory->firstline_is_text(file_path)) Data::data = factory->vector_column<T>(file_path, file_col, 1);
	else Data::data = factory->vector_column<T>(file_path, file_col, 0);

	delete factory;
	return *this;
}
/**
 * @brief Stores data into the data vector from a column of the file. If the first line is a string, it will be automatically set
 * as the name of the Data object.
 * @param file_path 
 * @param file_column 
 * @return Data& 
 */
template <>
inline Data<Udouble>& Data<Udouble>::set_data(const char * file_path, const int file_col, const int err_col)
{
    FileFactory * factory = new FileFactory();

    if(Data::name == "" && factory->firstline_is_text(file_path))
    {
        Data::data = factory->vector_column<Udouble>(file_path, file_col, 1, err_col);
        Data::name = factory->get_element(file_path, 0, file_col);
    }
    else if(factory->firstline_is_text(file_path))  Data::data = factory->vector_column<Udouble>(file_path, file_col, 1, err_col);
    else                                            Data::data = factory->vector_column<Udouble>(file_path, file_col, 0, err_col); 
    

    delete factory;
    return *this;  
}



/**
 * @brief Prints mean, std, min and max of the Data column
 * 
 * @tparam T 
 */
template<class T>
void Data<T>::describe() const {
	print_element(' ', width, separator, lenght);
	print_element(Data::name, width, separator, lenght);
	std::cout << std::endl;

	print_element("Mean:", width, separator, lenght);
	print_element(Data::mean(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Std:", width, separator, lenght);
	print_element(Data::std(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Min:", width, separator, lenght);
	print_element(Data::min(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Max:", width, separator, lenght);
	print_element(Data::max(), width, separator, lenght);
	std::cout << std::endl;

}

/**
 * @brief Prints first n entries of the data column
 * 
 * @tparam T 
 * @param n 
 */
template<class T>
void Data<T>::head(const int n) const {
	print_element(' ', width, separator, lenght);
	print_element(Data::name, width, separator, lenght);
	std::cout << std::endl;

	for (int i = 0; i < n; i++) {
		print_element(i, width, separator, lenght);
		print_element(Data::data[i], width, separator, lenght);
		std::cout << std::endl;
	}
}

template <>
inline Udouble& Data<Udouble>::at(const int n) {
	return Data::data.at(n);
}

template <>
inline std::vector<double> Data<Udouble>::values() {
	std::vector<double> vector;
	for (Udouble u: Data::data)	vector.push_back(u.get_value());
	return vector;
}

template <>
inline std::vector<double> Data<Udouble>::errors() {
	std::vector<double> vector;
	for (Udouble u: Data::data)	vector.push_back(u.get_error());
	return vector;
}

// operators

template<class T>
bool Data<T>::operator==(const Data<T> &data2) {
	if (Data::size() != data2.size()) {
		std::cerr << "Warning: size of the two vector is not the same." << std::endl;
		return false;
	} else {
		if (Data::data == data2.data) return true;
		else return false;
	}
}

template <>
inline Udouble& Data<Udouble>::operator[](const int n) {
	return Data::at(n);
}

// statistical functions

/**
 * @brief Returns the mean value of stored distribution.
 * @return double 
 */
template<class T>
const double Data<T>::mean() const {
	T sum = std::accumulate(Data::data.begin(), Data::data.end(), 0.0);
	T mean = sum / Data::size();
	return double(mean);
}
template<>
inline const double Data<std::string>::mean() const {
	return 0.;
}
template<>
inline const double Data<Udouble>::mean() const {
	std::vector<double> temp;
	for(Udouble i: Data::data)	temp.push_back(i.get_value());
	double sum = std::accumulate(temp.begin(), temp.end(), 0.0);
	double mean = sum / Data::size();
	return mean;
}

/**
 * @brief Returns the standard deviation of stored distribution.
 * @return double 
 */
template<class T>
const double Data<T>::std() const {
	std::vector<T> num_terms;
	for (T i: Data::data)	num_terms.push_back(pow(i - Data::mean(), 2));
	T num = std::accumulate(num_terms.begin(), num_terms.end(), 0.0);
	T std = sqrt(num / Data::size());

	return double(std);
}
template<>
inline const double Data<std::string>::std() const {
	return 0.;
}
template<>
inline const double Data<Udouble>::std() const {
	std::vector<double> num_terms;
	for(Udouble i: Data::data)	num_terms.push_back(pow(i.get_value() - Data::mean(), 2));
	double num = std::accumulate(num_terms.begin(), num_terms.end(), 0.0);
	double std = sqrt(num / Data::size());
	return std;
}

/**
 * @brief Returns the minimum value of stored distribution.
 * @return double 
 */
template<class T>
const double Data<T>::min() const {
	T min = Data::data.front();
	for (T i: Data::data) if (min > i)	min = i;
	return double(min);
}
template<>
inline const double Data<std::string>::min() const {
	return 0.;
}
template<>
inline const double Data<Udouble>::min() const {
	double min = Data::data.front().get_value();
	for (Udouble i: Data::data) if (min > i.get_value())	min = i.get_value();
	return double(min);
}

/**
 * @brief Returns the maximum value of stored distribution.
 * @return double 
 */
template<class T>
const double Data<T>::max() const {
	T max = Data::data.front();
	for (T i: Data::data) if (max < i)	max = i;
	return double(max);
}
template<>
inline const double Data<std::string>::max() const {
	return 0.;
}
template<>
inline const double Data<Udouble>::max() const {
	double max = Data::data.front().get_value();
	for (Udouble i: Data::data) if (max < i.get_value())	max = i.get_value();
	return max;
}


/**
 * @brief Add gaussian noise to the data vector
 * 
 * @tparam T 
 * @return Data<T> 
 */
template <class T>
inline Data<T>& Data<T>::add_noise(const double mean, const double stddev) {
	std::default_random_engine generator;
	std::normal_distribution<T> dist(mean, stddev);
	
	for (int i = 0; i < Data::size(); i++) 	Data::data[i] = Data::data[i] + dist(generator);
	return *this;
}
template <>
inline Data<Udouble>& Data<Udouble>::add_noise(const double mean, const double stddev) {
	std::default_random_engine generator;
	std::normal_distribution<double> dist(mean, stddev);

	for (int i = 0; i < Data::size(); i++)
	{
		Udouble u;
		Udouble w(dist(generator), 0.);
		Data::data[i] = Data::data[i] + w;
	}
	return *this;
}



// friend functions

template<class T>
std::ostream &operator<<(std::ostream &out, const Data<T> &data) {
	std::vector<double> storing_data = data.get_data();

	out << "Print: " << data.get_name() << std::endl;
	for (typename std::vector<T>::const_iterator i = storing_data.begin(); i != storing_data.end(); i++) {
		out << *i << std::endl;
	}

	return out;
}


template<class T>
Data<T> operator+(Data<T> data1, Data<T> data2) {
	assert(data1.size() == data2.size());

	Data<T> data;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] + data2[i];
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator-(Data<T> data1, Data<T> data2) {
	assert(data1.size() == data2.size());

	Data<T> data;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] - data2[i];
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator*(Data<T> data1, Data<T> data2) {
	assert(data1.size() == data2.size());
	Data<T> data;
	data.name = data1.name;

	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] * data2[i];
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator*(Data<T> data1, const double scalar) {
	Data<T> data;
	data.name = data1.name;

	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] * scalar;
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator*(Data<T> data1, const int scalar) {
	Data<T> data;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = scalar * data1[i];
		std::cout << t << " " << data1[i] << std::endl;
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator/(Data<T> data1, Data<T> data2) {
	assert(data1.size() == data2.size());
	Data<T> data;
	data.name = data1.name;

	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] / data2[i];
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator/(Data<T> data1, const double scalar) {
	Data<T> data;
	data.name = data1.name;

	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] / scalar;
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> operator/(Data<T> data1, const int scalar) {
	Data<T> data;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = data1[i] / scalar;
		data.data.push_back(t);
	}
	return data;
}



template<class T>
Data<T> sin(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = sin(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> cos(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = cos(data1[i]);
		data.data.push_back(t);
	}
	return data;
}
template<class T>
Data<T> tan(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = tan(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> sinh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = sinh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> cosh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = cosh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> tanh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = tanh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> asin(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = asin(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> acos(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = acos(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> atan(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = atan(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> asinh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = asinh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> acosh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = acosh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> atanh(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = atanh(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> exp(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = exp(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> pow(Data<T> data1, const double n) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = pow(data1[i], n);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> pow(Data<T> data1, const int n) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = pow(data1[i], n);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> pow(const Data<T> data1, Data<T> data2) {
	assert(data1.size() == data2.size());

	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = pow(data1[i], data2[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> log(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = log(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}
template<class T>
Data<T> log10(Data<T> data1) {
	Data<T> data;
	std::vector<T> vector;
	data.name = data1.name;
	
	for(int i = 0; i < data1.size(); i++) 
	{
		T t;
		t = log10(data1[i]);
		vector.push_back(t);
	}
	data.data = vector;
	return data;
}






#endif
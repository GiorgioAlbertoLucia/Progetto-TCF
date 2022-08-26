#ifndef DATASET_H
#define DATASET_H

#include "../include/data.hpp"
#include "../include/fileFactory.hpp"

#include <iostream>
#include <vector>
#include <string>


/**
 * @brief Dataset object. Stores a vector of Data. You can load a dataset from a file and inspect it with this class.
 * 
 * @tparam T Any
 */
template<class T>
class Dataset {

public:
	Dataset() {};
	Dataset(const char *, const int = 0, const char * = "");     // file_path, first_column
	Dataset(std::string, const int = 0, const char * = "");

	Dataset(const Dataset<T> &);

	~Dataset();

	std::vector<Data<T>> get_dataset() const { return data; };

	std::vector<std::string> get_columns() const { return columns; };

	Data<T>& get_data(const int i) { return data.at(i); };

	Data<T>& get_data(const char *column) { return data[find(columns.begin(), columns.end(), column)]; };

	const void describe() const;

	const void head(int = 5) const;

	const void print_columns() const;

	int size() const { return data.size(); };

	Dataset<T> &fill(const char *, const int = 0);

	Dataset<T> &concatenate(const Dataset<T> &);

	Dataset<T> &add(const Data<T> &);

	Dataset<T> &remove(const char *);

	Data<T> &operator[](const char *column) { return data[find(columns.begin(), columns.end(), column)]; };

	Data<T> &operator[](const int column) { return data.at(column); };

private:
	std::vector<Data<T>> data;
	std::vector<std::string> columns;
};



//////////////////////////////////////////////////
//              IMPLEMENTATION                  //
//////////////////////////////////////////////////


/* MEMBER FUNCTION */

/**
 * @brief Construct a new Dataset:: Dataset object
 * @param file_path 
 * @param first_column 
 * @param label dataset name (you can leave this blank)
 */
template<class T>
Dataset<T>::Dataset(const char *file_path, const int first_column, const char *label) {
	Dataset::fill(file_path, first_column);
}

/**
 * @brief Construct a new Dataset:: Dataset object
 * @param file_path 
 * @param first_column 
 * @param label dataset name (you can leave this blank
 */
template<class T>
Dataset<T>::Dataset(std::string file_path, const int first_column, const char *label) {
	const char *char_path = file_path.c_str();
	Dataset::fill(char_path, first_column);
}

/**
 * @brief (Copy constructor) Construct a new Dataset:: Dataset object
 * 
 * @param dataset_object 
 */
template<class T>
Dataset<T>::Dataset(const Dataset<T> &dataset_object) {
	Dataset::data = dataset_object.data;
	Dataset::columns = dataset_object.columns;
}

/**
 * @brief Destroy the Dataset:: Dataset object
 * 
 */
template<class T>
Dataset<T>::~Dataset() {

}


/**
 * @brief Prints mean, std, min and max for each Data column
 * 
 * @tparam T 
 */
template<class T>
const void Dataset<T>::describe() const {

	print_element(" \t", width, separator, lenght);
	for (Data<T> d: data) print_element(d.get_name(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Entries:", width, separator, lenght);
	for (Data<T> d: data) print_element(d.size(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Mean:\t", width, separator, lenght);
	for (Data<T> d: data) print_element(d.mean(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Std:\t", width, separator, lenght);
	for (Data<T> d: data) print_element(d.std(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Min:\t", width, separator, lenght);
	for (Data<T> d: data) print_element(d.min(), width, separator, lenght);
	std::cout << std::endl;

	print_element("Max:\t", width, separator, lenght);
	for (Data<T> d: data) print_element(d.max(), width, separator, lenght);
	std::cout << std::endl;

}

/**
 * @brief Prints first n entries of each data column
 * 
 * @tparam T 
 * @param n 
 */
template<class T>
const void Dataset<T>::head(int n) const {
	if (data.at(0).size() < n) {
		n = data.at(0).size();
	}
	print_element(' ', width, separator, lenght);
	for (Data<T> d: data) print_element(d.get_name(), width, separator, lenght);
	std::cout << std::endl;

	for (int j = 0; j < n; j++) {
		print_element(j, width, separator, lenght);
		for (Data<T> d: data) print_element(d.at(j), width, separator, lenght);
		std::cout << std::endl;
	}
}

/**
 * @brief Creates a dataset containing Data object. Each object is a data vector filled with elements from a column of a file
 * and its name is directly imported from the file (this is done only if the first line of the file is a string). Sets the
 * number of entries in the file.
 * @param file_path 
 * @param first_column column from which you want to import the file
 * @returns Dataset&
 */
template<class T>
Dataset<T> &Dataset<T>::fill(const char *file_path, const int first_column) {
	FileFactory *factory = new FileFactory();
	File *file = factory->create_file(file_path);

	for (int i = first_column; i < file->get_columns(); i++) {
		Data<T> d(file_path, i);
		Dataset::data.push_back(d);
		Dataset::columns.push_back(d.get_name());
	}

	delete factory;
	delete file;
	return *this;
}

/**
 * @brief Appends a Dataset object to the current one.
 * 
 * @tparam T 
 * @param dataset 
 * @return Dataset<T>& 
 */
template<class T>
Dataset<T> &Dataset<T>::concatenate(const Dataset<T> &dataset) {
	Dataset<T>::data.insert(Dataset<T>::data.end(), dataset.data.begin(), dataset.data.end());
	Dataset<T>::columns.insert(Dataset<T>::columns.end(), dataset.columns.begin(), dataset.columns.end());
}

/**
 * @brief Adds an element to the dataset vector.
 * @param data 
 * @return Dataset& 
 */
template<class T>
Dataset<T> &Dataset<T>::add(const Data<T> &d) {
	Dataset::data.push_back(d);
	return *this;
}

/**
 * @brief Removes all the elements with given name from the dataset vector.
 * @param name
 * @return Dataset& 
 */
template<class T>
Dataset<T> &Dataset<T>::remove(const char *name) {
	typename std::vector<Data<T>>::const_iterator it = std::find(Dataset<T>::columns.begin(), Dataset<T>::columns.end(),
																 name);
	if (it != Dataset<T>::columns.end()) {
		const int index = std::distance(Dataset<T>::columns.begin(), it);
		Dataset<T>::data.erase(index);
	}
	std::cerr << "Error: there is no element with name " << name << "." << std::endl;
	return *this;
}


#endif
#include "../include_t/file_t.hpp"
#include "../include_t/csvFile_t.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

/* USEFUL FUNCTIONS */

/* FUNCTIONS FROM HEADER FILE */

/**
 * @brief Construct a new Csv File:: Csv File object
 * @param file_path 
 */
CsvFile::CsvFile(const char *file_path) {
	// creates an empty .Csv file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
	std::ofstream file;
	file.open(file_path, std::ios::app);
	file.close();

	CsvFile::set_path(file_path);
}

/**
 * @brief Construct a new Csv File:: Csv File object. Alternative constructor taking string as an input.
 * 
 * @param str_file_path 
*/
CsvFile::CsvFile(std::string str_file_path) {
	// creates an empty .Csv file if none is actually in your folder (app prevents the deleting of contents of pre-existing files)
	const char *file_path = str_file_path.c_str();

	std::ofstream file;
	file.open(file_path, std::ios::app);
	file.close();

	CsvFile::set_path(file_path);
}

/**
 * @brief Copy constructor.
 * Construct a new Csv File:: Csv File object.
 * @param csv_file 
 */
CsvFile::CsvFile(const CsvFile &csv) 
{
	CsvFile::file_path = csv.file_path;
	CsvFile::rows = csv.rows;
	CsvFile::columns = csv.columns;
}

/**
 * @brief Destroy the Csv File:: Csv File object.
 */
CsvFile::~CsvFile() {

};

// file_path setter and getter
/**
 * @brief Sets the file path and automatically sets the number of rows and columns
 * @param filepath complete path to the file
 */
void CsvFile::set_path(const char *file_path) {
	CsvFile::file_path = file_path;
	CsvFile::rows = CsvFile::n_rows();
	CsvFile::columns = CsvFile::n_columns();

}


/**
 * @brief 
 * @return number of rows in the file (not considering comment lines)
 */
int CsvFile::n_rows() const {
	int rows = 0;
	std::ifstream file(CsvFile::file_path);

	// skip comment
	int first_line = comment_lines();
	for (int i = 0; i < first_line; i++) file.ignore(10000, '\n');

	if (file.is_open()) {
		// count entries
		std::string line;
		while (getline(file, line)) rows++;

		file.close();
	} else std::cerr << "Error: unable to open file" << std::endl;
	return rows;
}

/**
 * @brief Counts how many columns (text separated by a space, tab or comma) there are in a given string.
 * If different lines of the file have a different amount of columns, an error is displayed.
 * @return number of columns.
 */
int CsvFile::n_columns() const {
	int columns = 0;
	int save_columns = 0;       // used to check if each line has the same number of columns

	std::ifstream file(CsvFile::file_path);

	if (file.is_open()) {
		// skip comment
		int first_line = comment_lines();
		for (int i = 0; i < first_line; i++) file.ignore(10000, '\n');

		for (int j = 0; j < CsvFile::rows; j++) {
			std::string row, item;
			getline(file, row);
			std::istringstream iss(row);
			while (getline(iss, item, ',')) 	if (item.length()) 		columns++;

			if (j > 0 && columns != save_columns) {
				std::cerr << "Error: not all the lines have the same amount of columns. First " << j << " lines have "
						  << save_columns << " columns (this value will be returned)." << std::endl;
				return save_columns;
			}

			save_columns = columns;
			columns = 0;
		}
	}
	return save_columns;
}


/**
 * @brief Clear content inside your file
 * 
 */
void CsvFile::clear() {
	std::fstream file;
	file.open(CsvFile::file_path, std::ios::out | std::ios::trunc);
	file.close();
}

/**
 * @brief 
 * @returns number of lines containing comments
 */
int CsvFile::comment_lines() const {
	int comment = 0;
	std::string line;
	std::ifstream file(CsvFile::file_path);
	if (file.is_open()) while (file >> line) if (line.at(0) == '#') comment++;
	file.close();
	return comment;
}

// friend functions
std::ostream &operator<<(std::ostream &out, const CsvFile &csv) {
	std::ifstream file;
	file.open(csv.file_path);
	if (file.is_open()) {
		out << "Print " << csv.file_path << ": " << std::endl;
		while (!file.eof()) {
			std::string this_line;
			getline(file, this_line);
			out << this_line << std::endl;
		}

		file.close();
	} else std::cerr << "Error: unable to open file" << std::endl;

	return out;
}

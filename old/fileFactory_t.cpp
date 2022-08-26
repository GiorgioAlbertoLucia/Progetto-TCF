#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

#include "../include_t/fileFactory_t.hpp"
#include "../include_t/txtFile_t.hpp"
#include "../include_t/csvFile_t.hpp"



/**
 * @brief  This only works with .Csv files using a space (' ') or a tab as delimiter between columns. 
 * Columns are numbered beginning with zero.
 * @param val_col: number referring to the column where values are stored
 * @param err_col: number referring to the column where errors are stored
 * @param beginning: line index of the first element that will be included. This will be used in building Data objects that will
 * want to fetch the name of the column
 */
template<>
std::vector<Udouble>    FileFactory::vector_column(const char *file_path, const int val_col, const int beginning, const int err_col) {
	std::vector<Udouble> vector;
	File *file = this->create_file(file_path);
	std::ifstream f(file->get_path());

	if (f.is_open()) {
		// skip comment
		int first_line = file->comment_lines();
		for (int i = 0; i < first_line; i++) f.ignore(10000, '\n');

		if (val_col >= file->n_columns() || err_col >= file->n_columns()) {
			std::cerr << "Error: column " << std::max(val_col, err_col) << " does not exist. The file has ";
			std::cout << file->n_columns() << " columns." << std::endl;
			return vector;
		}

		// skip lines
		std::string row;
		for (int i = 0; i < beginning; i++) getline(f, row);

		while (getline(f, row)) {
			std::istringstream iss(row);
			double column_value, column_error;
			if (val_col < err_col) {
				for (int i = 0; i <= val_col; i++) iss >> column_value;
				for (int i = val_col; i <= err_col; i++) iss >> column_error;
			}
			if (err_col < val_col) {
				for (int i = 0; i <= err_col; i++) iss >> column_error;
				for (int i = err_col; i <= val_col; i++) iss >> column_value;
			}
			Udouble u(column_value, column_error);
			vector.push_back(u);
		}
		f.close();
	} else std::cout << "Error: unable to open file" << std::endl;
	return vector;
}



/**
 * @brief Template specialization for Udouble.
 * This function adds a column of floats (with their description as top line) to an existing .txt file. The name of the column
 * is added only if the first line of the file (except comment) contains words 
 * @tparam  
 * @param file_path 
 * @param column 
 * @param name 
 */
template<>
void    FileFactory::append_column<Udouble>(const char *file_path, const std::vector<Udouble> &column, const char *name) const {
	File *file = this->create_file(file_path);
	std::fstream f(file->get_path(), std::ios::in);

	// fill a vector with the file content
	std::string line;
	std::vector<std::string> file_lines;
	while (getline(f, line)) file_lines.push_back(line);
	f.clear();
	f.seekg(0, std::ios::beg);

	int comment = file->comment_lines();

	if (check_words(file_lines.at(0))) {
		for (int i = 0; i < file_lines.size(); i++) {
			if (i < comment) f << file_lines.at(i) << std::endl;
			else if (i == comment) f << file_lines.at(i) << "\t\t" << name << std::endl;
			else
				f << file_lines.at(i) << "\t\t\t" << column.at(i - comment - 1).get_value()
				  << column.at(i - comment - 1).get_error() << std::endl;
		}
	} else {
		for (int i = 0; i < file_lines.size(); i++) {
			if (i < comment) f << file_lines.at(i) << std::endl;
			else
				f << file_lines.at(i) << "\t\t\t" << column.at(i - comment).get_value()
				  << column.at(i - comment).get_error() << std::endl;
		}
	}

	f.close();
	delete file;
}

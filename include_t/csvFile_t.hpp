#ifndef CSVFILE_H
#define CSVFILE_H

#include "../include_t/file_t.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Concrete class to read .csv files.
 * 
 */
class CsvFile : public File {

	friend std::ostream &operator<<(std::ostream &, const CsvFile &);

public:
	CsvFile();

	CsvFile(const char *);

	CsvFile(std::string);

	CsvFile(const CsvFile &);

	~CsvFile();

	virtual void set_path(const char *);

	virtual std::string get_path() const { return CsvFile::file_path; };

	virtual int get_rows() const { return CsvFile::rows; };

	virtual int get_columns() const { return CsvFile::columns; };

	virtual int n_rows() const;

	virtual int n_columns() const;

	virtual void clear();

	virtual int comment_lines() const;


private:
	std::string file_path;
	int rows;
	int columns;


};

#endif
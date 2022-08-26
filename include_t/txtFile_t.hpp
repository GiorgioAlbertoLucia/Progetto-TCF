#ifndef TXTFILE_H
#define TXTFILE_H

#include "../include_t/file_t.hpp"
#include "../include_t/udouble.hpp"
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Concrete class to read .txt files
 * 
 */
class TxtFile : public File {

	friend std::ostream &operator<<(std::ostream &, const TxtFile &);

public:
	TxtFile();

	TxtFile(const char *);

	TxtFile(std::string);

	TxtFile(const TxtFile &);

	~TxtFile();

	virtual void set_path(const char *file_path);

	virtual std::string get_path() const { return TxtFile::file_path; };
	virtual int get_rows() const { return TxtFile::rows; };
	virtual int get_columns() const { return TxtFile::columns; };
	
	virtual int n_rows() const;
	virtual int n_columns() const;

	virtual char separator() { return ' '; };
	virtual void clear();
	virtual int comment_lines() const;

private:
	std::string file_path;
	int rows;
	int columns;
};


#endif
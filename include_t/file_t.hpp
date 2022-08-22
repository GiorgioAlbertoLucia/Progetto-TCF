#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

/**
 * @brief Abstract class to read files. Two concrete classes, TxtFile and CsvFile, are currently implemented.
 * 
 */
class File {
public:
	virtual ~File() {};

	virtual void set_path(const char *) = 0;

	virtual std::string get_path() const = 0;

	virtual int get_rows() const = 0;

	virtual int get_columns() const = 0;

	virtual int n_rows() const = 0;

	virtual int n_columns() const = 0;

	virtual void clear() = 0;

	virtual int comment_lines() const = 0;
};

#endif
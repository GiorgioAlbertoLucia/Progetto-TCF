#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>

/**
 * @brief Abstract class prototype. The final class will be a class template.
 * 
 */
class Dataset
{
    friend  std::ostream            operator<<(std::ostream, const TxtDataset&);

public:
                                    TxtDataset(const char *, const char * = 0);     // file_path, name
                                    TxtDataset(std::string, const char * = 0);  
                                    TxtDataset(const TxtDataset&);
                                    ~TxtDataset();

    virtual void                    set_name(const char *);
    virtual void                    set_name(std::string);
    virtual std::string             get_name()                                  const;

    virtual void                    fill()                                      const;

private:
    std::vector<TxtData>            dataset;
    int                             entries;
    std::string                     name;
};

#endif
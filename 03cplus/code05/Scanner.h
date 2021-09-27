#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>

class Scanner
{
public:
    Scanner(const std::string &buf);
private:
    const std::string buf_;
};

#endif
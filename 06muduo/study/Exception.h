#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
    explicit Exception(const char *what);
    virtual ~Exception() throw();
    virtual const char *what() const throw();
    const char *stackTrace() const throw();

private:
    std::string message_;
    std::string stack_;
};

#endif
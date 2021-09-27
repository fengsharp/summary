#ifndef PARSER_H_
#define PARSER_H_

class Scanner;
class Parser
{
public:
    Parser(Scanner &scanner);
    void parse();
    double cal() const;
private:
    Scanner& scanner_;
};

#endif
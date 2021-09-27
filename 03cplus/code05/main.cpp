#include <iostream>
#include <string>

#include "Express.h"
#include "Scanner.h"
#include "Parser.h"

int main()
{    
    while (true)
    {
        std::cout << "> ";

        std::string buf;
        std::getline(std::cin, buf);
        Scanner scanner(buf);
        Parser parser(scanner);
        parser.parse();
        std::cout << parser.cal() << std::endl;
    }

    return 0;
}
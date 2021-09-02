#include <iostream>
#include <string>

void test01();
void test02();

int main()
{
    // test01();
    test02();

    return 0;
}

void test01()
{
    std::string line;
    while (getline(std::cin, line))
    {
        std::cout << line << " --- ok." << std::endl;
    }
}

void test02()
{
    class Foo
    {
    public:
        Foo() = default;
        Foo(const Foo &rhs)
        {
            std::cout << "foo copy ctor" << std::endl;
        }
    };

    Foo x;
    Foo y(x);
    Foo z(std::move(x));
}

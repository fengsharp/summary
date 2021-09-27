#include <iostream>
#include <vector>
#include <string>
#include "Shape.h"
#include "DynBase.h"
using namespace std;

void drawAllShapes(const vector<Shape*>& v)
{
    for (auto &it : v)
    {
        it->draw();
    }
}

void deleteAllShapes(const std::vector<Shape*>& v)
{
    for (auto &it : v)
    {
        delete it;
    }
}

int main(void)
{
    // Shape s;//Error, 不能实例化抽象类
    vector<Shape*> v;

    Shape *ps;
    ps = static_cast<Shape*>(DynObjectFactory::createObject("Circle"));
    v.push_back(ps);
    ps = static_cast<Shape*>(DynObjectFactory::createObject("Square"));
    v.push_back(ps);
    ps = static_cast<Shape*>(DynObjectFactory::createObject("Rectangle"));
    v.push_back(ps);

    drawAllShapes(v);
    deleteAllShapes(v);
    return 0;
}

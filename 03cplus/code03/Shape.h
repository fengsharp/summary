#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>

#include "DynBase.h"

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void draw() = 0;
};

class Circle : public Shape
{
public:
    virtual ~Circle()
    {
        std::cout << "~Circle ..." << std::endl;
    }

    virtual void draw() override
    {
        std::cout << "circle draw" << std::endl;
    }
};

class Square : public Shape
{
public:
    virtual ~Square()
    {
        std::cout << "~Square ..." << std::endl;
    }

    virtual void draw() override
    {
        std::cout << "Square draw" << std::endl;
    }
};

//增加一个类
class Rectangle : public Shape
{
    virtual ~Rectangle()
    {
        std::cout << "~Rectangle ..." << std::endl;
    }

    virtual void draw() override
    {
        std::cout << "Rectangle draw" << std::endl;
    }
};

//这里添加了三个宏,仅仅是做为展开操作
REGISTER_CLASS(Circle);
REGISTER_CLASS(Square);
REGISTER_CLASS(Rectangle);

#endif
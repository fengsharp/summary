#include "Express.h"

#include <cmath>

double NumberNode::cal() const
{
    return number_;
}

BinaryNode::~BinaryNode()
{
    delete left_;
    delete right_;
}

double AddNode::cal() const
{
    return left_->cal() + right_->cal();
}

double SubNode::cal() const
{
    return left_->cal() - right_->cal();
}

double MultyNode::cal() const
{
    return left_->cal() * right_->cal();
}

double DivideNode::cal() const
{
    double divisor = right_->cal();
    if (std::abs(divisor) > 0.000001)
    {
        return left_->cal() / divisor;
    }
    else
    {
        // todo: error
        return 0.0;
    }
}

UnaryNode::~UnaryNode()
{
    delete child_;
}

double UminiusNode::cal() const
{
    return -child_->cal();
}
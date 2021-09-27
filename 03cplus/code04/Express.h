#ifndef EXPRESS_H_
#define EXPRESS_H_

class Node
{
public:
    virtual ~Node() = default;
    virtual double cal() const = 0;
};

class NumberNode : public Node
{
public:
    NumberNode(double number)
        : number_(number)
    {
    }
    virtual double cal() const override;

private:
    double number_;
};

class BinaryNode : public Node
{
public:
    BinaryNode(Node *left, Node *right)
        : left_(left), right_(right)
    {
    }

    ~BinaryNode();

protected:
    Node *const left_;
    Node *const right_;
};

class AddNode : public BinaryNode
{
public:
    AddNode(Node *left, Node *right)
        : BinaryNode(left, right)
    {
    }

    virtual double cal() const override;
};

class SubNode : public BinaryNode
{
public:
    SubNode(Node *left, Node *right)
        : BinaryNode(left, right)
    {
    }

    virtual double cal() const override;
};

class MultyNode : public BinaryNode
{
public:
    MultyNode(Node *left, Node *right)
        : BinaryNode(left, right)
    {
    }

    virtual double cal() const override;
};

class DivideNode : public BinaryNode
{
public:
    DivideNode(Node *left, Node *right)
        : BinaryNode(left, right)
    {
    }

    virtual double cal() const override;
};

class UnaryNode : public Node
{
public:
    UnaryNode(Node *child)
        : child_(child)
    {
    }
    ~UnaryNode();

protected:
    Node *child_;
};

class UminiusNode : public UnaryNode
{
public:
    UminiusNode(Node *child)
        : UnaryNode(child)
    {
    }

    virtual double cal() const override;
};

#endif
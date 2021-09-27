#include <iostream>

#include "Express.h"

int main()
{
    Node* num1 = new NumberNode(3);
    Node* num2 = new NumberNode(6);
    Node* add = new AddNode(num1, num2);
    Node* minusNode = new UminiusNode(add);
    Node* num3 = new NumberNode(5);
    Node* root = new MultyNode(minusNode, num3);

    std::cout << root->cal() << std::endl;

    delete root;

    return 0;
}
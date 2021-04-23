//Juhi Patel
//jmp170130
//CS 1337.007

#include "DoubleLinkedNode.h"
DoubleLinkedNode::DoubleLinkedNode() //default constructor null
{
    next = nullptr;
    prev = nullptr;
}

DoubleLinkedNode* DoubleLinkedNode::getNext() //next accessor
{
    return next;
}

DoubleLinkedNode* DoubleLinkedNode::getPrev() //prev accessor
{
    return prev;
}

void DoubleLinkedNode::setNext(DoubleLinkedNode* n) //next mutator
{
    next = n;
}

void DoubleLinkedNode::setPrev (DoubleLinkedNode* p) //prev mutator
{
    prev = p;
}

DoubleLinkedNode::DoubleLinkedNode(std::string r, int d) : BaseNode(r, d) //overloaded constructor calls basenode overloaded constructor
{
    next = nullptr;
    prev = nullptr;
}

DoubleLinkedNode::DoubleLinkedNode(const DoubleLinkedNode &cpy) : BaseNode(cpy) {} //overloaded constructor calls basenode overloaded constructor

DoubleLinkedNode::~DoubleLinkedNode() //destructor
{
}

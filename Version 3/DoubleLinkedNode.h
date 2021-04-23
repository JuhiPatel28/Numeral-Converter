//Juhi Patel
//jmp170130
//CS 1337.007

#ifndef DOUBLELINKEDNODE_H
#define DOUBLELINKEDNODE_H
#include "BaseNode.h"
#include <string>
#include <iostream>
class DoubleLinkedNode : public BaseNode
{
public:
    //constructors
    DoubleLinkedNode();
    DoubleLinkedNode(std::string r, int d);
    DoubleLinkedNode(const DoubleLinkedNode &cpy);

    void getHi() {std::cout << "hi";}

    //destructor
    virtual ~DoubleLinkedNode();

    //accessors
    DoubleLinkedNode* getNext();
    DoubleLinkedNode* getPrev();

    //mutators
    void setNext(DoubleLinkedNode* n);
    void setPrev (DoubleLinkedNode* p);

private:
    //private members
    DoubleLinkedNode* next = nullptr;
    DoubleLinkedNode* prev = nullptr;
};

#endif // DOUBLELINKEDNODE_H

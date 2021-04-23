//Juhi Patel
//jmp170130
//CS 1337.007

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <fstream>
#include "DoubleLinkedNode.h"

class LinkedList
{
public:
    //constructor
    LinkedList();
    LinkedList(DoubleLinkedNode* h);

    //destructor
    virtual ~LinkedList();

    //accessors
    DoubleLinkedNode* getHead();
    DoubleLinkedNode* getTail();

    //mutators
    void setHead(DoubleLinkedNode* h);
    void setTail(DoubleLinkedNode* t); //need t write

    //print functions
    void PrintList(DoubleLinkedNode*);
    void PrintList() {PrintList(head);}

    //overloaded operators
    void operator+=(DoubleLinkedNode*);
    void operator--();
    void operator--(int);

    //delete function
    void Delete(int);

private:
    //private members
    DoubleLinkedNode* head;
    DoubleLinkedNode* tail;
};

#endif // LINKEDLIST_H

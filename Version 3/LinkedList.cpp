//Juhi Patel
//jmp170130
//CS 1337.007

#include "LinkedList.h"
#include <iostream>
#include <fstream>
using namespace std;

LinkedList::~LinkedList() //destructor
{
    while(head != nullptr) //delete all nodes in linked list
    {
        DoubleLinkedNode* temp = head;
        head = head->getNext();
        delete temp;
    }
}

LinkedList::LinkedList() //default constructor
{
    head = nullptr;
    tail = nullptr;
}

LinkedList::LinkedList(DoubleLinkedNode* h) //overloaded constructor
{
    head = h;
    DoubleLinkedNode* cpy = head;
    while(cpy->getNext() != nullptr)
    {
        cpy = cpy->getNext();
    }
    tail = cpy;
}

DoubleLinkedNode* LinkedList::getHead() //head accessor
{
    return head;
}

DoubleLinkedNode* LinkedList::getTail() //tail accessor
{
    return tail;
}

void LinkedList::setHead(DoubleLinkedNode* h) //head mutator
{
    head = h;
}
void LinkedList::setTail(DoubleLinkedNode* t) //tail mutator
{
    tail = t;
}

void LinkedList::PrintList(DoubleLinkedNode* n) //recursive print list function
{
    ofstream file ("numbers2.txt", ios::app); //open file
    file << *n;
    if(n->getNext() != nullptr)
    {
        PrintList(n->getNext());
    }
}

void LinkedList::operator+=(DoubleLinkedNode* add) //overloaded +=
{
    if(head == nullptr) //if empty list
    {
        head = add;
        tail = add;
    }
    else
    {
        tail->setNext(add); //add to list
        add->setPrev(tail);
        tail = add;
        add->setNext(nullptr);
    }

}

void LinkedList::Delete(int d) //delete function
{
    DoubleLinkedNode* cpy = this->getHead()->getNext();
    for(int counter = 0; counter < d; counter++) //move cpy to node set for deletion
    {
        cpy = cpy->getNext();
    }

    DoubleLinkedNode* cpy2 = cpy->getPrev();

    if(cpy->getNext() != nullptr) //unlink node from list
    {
        cpy2->setNext(cpy->getNext());
        cpy->getNext()->setPrev(cpy2);
    }
    else
    {
        cpy2->setNext(nullptr);
        this->setTail(cpy2);
    }
    delete cpy; //delete node
}


void LinkedList::operator--() //overloaded prefix --
{
    DoubleLinkedNode* cpy = this->getHead()->getNext(); //unlink node from list
    DoubleLinkedNode* cpy2 = cpy->getNext();
    this->getHead()->setNext(cpy2);
    cpy2->setPrev(this->getHead());
    delete cpy; //delete node
}

void LinkedList::operator--(int) //overloaded postfix --
{
    DoubleLinkedNode* cpy = this->getHead();
    while(cpy->getNext()->getNext() != nullptr) //move to end of list
    {
        cpy = cpy->getNext();
    }
    DoubleLinkedNode* cpy2 = cpy->getNext(); //unlink node from list
    cpy->setNext(nullptr);
    this->setTail(cpy); //reset tail
    delete cpy2; //delete node
}

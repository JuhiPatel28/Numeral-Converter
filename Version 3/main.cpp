//Juhi Patel
//jmp170130
//CS 1337.007

#include <string> //allow strings to be used
#include <fstream> //allow writing to and from file
#include <iostream> //allow writing to the console
#include "LinkedList.h"
#include "DoubleLinkedNode.h"
using namespace std;

void Sort(LinkedList*); //to sort both roman and decimal values
int Search(LinkedList*, string, char); //to search for values in nodes

//overloaded << used on line 55 linkedlist.cpp
//overloaded >> used on line 30 main.cpp
//overloaded += used on lines 34 and 103 main.cpp
//overloaded -- prefix used on line 110 main.cpp
//overloaded -- postfix used on line 116 main.cpp

//files are opened:
//line 30 main.cpp
//line 48 main.cpp
//line 54 linkedlist.cpp

int main() //main function
{
    LinkedList* l = new LinkedList(); //create linked list
    DoubleLinkedNode* e = new DoubleLinkedNode(); //create node
    *l += e; //null head

    fstream file ("numbers2.txt", ios::in | ios::out | ios::binary); //open file that can have data written and read

    if(!file.fail()) //if file opens
    {
        while(!file.fail()) //while eof is not false
        {
            DoubleLinkedNode* node = new DoubleLinkedNode(); //create new node
            file >> *node; //instert node
            if(node->GetDecimal() != 0 && node->GetRoman() != "") //if the node isnt empty
            {
                *l += node; //add to linked list
            }
        }
        file.close(); //close file

    }

    file.open("numbers2.txt", ios::out); //clear file
    file.close();

    Sort(l); //sort list

    int choice;
    while(choice != 5)
    {
        cout << "1. Search \n2. Add \n3. Delete first \n4. Delete last \n5. Exit \n6. Delete Specific Node" << endl; //user interface
        cout << "Please Enter Choice: ";
        cin >> choice;
        if(choice == 1)
        {
            cout << "Please enter what you are searching for: ";
            string srch;
            cin >> srch;
            if(isdigit(srch[0])) //if arabic
            {
                int node = Search(l, srch, 'd'); //call search funtion
                if(node != -1) //if value is found
                {
                    cout << "Value was found in node " << node << endl; //display which node it is in
                }
                else
                {
                    cout << "Value not found" << endl; //display not found
                }

            }
            else //if roman
            {
                int node = Search(l, srch, 'r'); //call search
                if(node != -1)
                {
                    cout << "Value was found in node " << node << endl;
                }
                else
                {
                    cout << "Value not found" << endl;
                }
            }
        }
        else if(choice == 2)
        {
            DoubleLinkedNode *New = new DoubleLinkedNode(); //new node
            cout << "Enter a value to add: ";
            string add, cadd;
            int temp;
            cin >> add;
            if(isdigit(add[0])) //if arabic
            {
                New->SetDecimal(stoi(add)); //store values in node
                cadd = New->d2r(stoi(add));
                New->SetRoman(cadd);
            }
            else //if decimal
            {
                New->SetRoman(add); //store values in node
                temp = New->r2d(add);
                New->SetDecimal(temp);
            }

            *l += New; //add to list
             Sort(l); //sort list
        }
        else if(choice == 3)
        {
            --(*l); //delete first node
            cout << "First Node Deleted" << endl;
        }
        else if(choice == 4)
        {
            (*l)--; //delete last node
            cout << "Last Node Deleted" << endl;
        }
        else if(choice == 6)
        {
            cout << "Enter a value to delete: ";
            string srch;
            cin >> srch;
            if(isdigit(srch[0])) //if arabic
            {
                int node = Search(l, srch, 'd'); //look for node
                if(node != -1) //if value found
                {
                    l->Delete(node); //call delete function
                    cout << "Value deleted" << endl;
                }
                else //if value not found
                {
                    cout << "Value not found" << endl;
                }

            }
            else //if roman
            {
                int node = Search(l, srch, 'r');
                if(node != -1)
                {
                    l->Delete(node);
                    cout << "Value deleted" << endl;
                }
                else
                {
                    cout << "Value not found" << endl;
                }
            }

        }
        else if(choice > 6 || choice < 1)
        {
            cout << "Invalid Choice" << endl;
        }
    }
    l->PrintList(); //print list
    delete l; //delete list
}

void Sort(LinkedList* h)
{
    DoubleLinkedNode* ptr = h->getHead(); //copy of h
    int number1, number2; //numbers to store comparison values
    if(ptr->getNext()->getNext() != nullptr) //check if only one item in the list
    {
        number1 = ptr->getNext()->GetDecimal(); //set numbers
        number2 = ptr->getNext()->getNext()->GetDecimal();
    }
    else //return without sorting if only one item
    {
        return;
    }
    DoubleLinkedNode* ptr2 = nullptr; //nodes to swap
    DoubleLinkedNode* ptr3 = nullptr;
    bool swapped = true;
    if(ptr->getNext() != nullptr) //if not an empty list
    {
        while(swapped == true) //while still swapping values
        {
            swapped = false;

            while(ptr->getNext()->getNext() != nullptr) //if not at end of list
            {
                if(number1 > number2) //if number1 is greater tham number2
                {
                    if(ptr->getNext()->getNext()->getNext() != nullptr) //swap them
                    {
                        ptr2 = ptr->getNext();
                        ptr3 = ptr2->getNext();
                        ptr->setNext(ptr3);
                        ptr3->setPrev(ptr);
                        ptr2->setNext(ptr3->getNext());
                        ptr3->getNext()->setPrev(ptr2);
                        ptr3->setNext(ptr2);
                        ptr2->setPrev(ptr3);
                    }
                    else //if end of list
                    {
                        ptr2 = ptr->getNext();
                        ptr3 = ptr2->getNext();
                        ptr->setNext(ptr3);
                        ptr3->setPrev(ptr);
                        ptr2->setNext(nullptr);
                        ptr3->setNext(ptr2);
                        ptr2->setPrev(ptr3);
                        h->setTail(ptr2);
                        swapped = true;
                        break; //break out of while loop
                    }
                    swapped = true;
                    ptr = ptr->getNext();
                    number1 = ptr->getNext()->GetDecimal();
                    number2 = ptr->getNext()->getNext()->GetDecimal();
                }
                else if(number1 <= number2) //if smaller
                {
                    if(ptr->getNext()->getNext()->getNext() != nullptr) //dont swap
                    {
                        ptr = ptr->getNext(); //set next
                        number1 = ptr->getNext()->GetDecimal();
                        number2 = ptr->getNext()->getNext()->GetDecimal();
                    }
                    else //if at end of list
                    {
                        break; //break out of while loop
                    }
                }
            }
            ptr = h->getHead(); //reset ptr
            number1 = ptr->getNext()->GetDecimal();
            number2 = ptr->getNext()->getNext()->GetDecimal();
        }
    }
}

int Search(LinkedList* h, string s, char type) //search for values
{
    DoubleLinkedNode* ptr = h->getHead()->getNext(); //copy of h
    int counter = 0; //store where found/if found at all
    if(type == 'r') //if looking for a roman value
    {
        while(ptr != nullptr) //search roman values
        {
            if (ptr->GetRoman() == s)
            {
                return counter; //return value when found
            }
            else
            {
                counter++; //increment when not found until end of list
            }
            ptr = ptr->getNext();
        }
    }
    else //if looking for decimal value
    {
        while(ptr != nullptr) //while not end of list
        {
            if (ptr->GetDecimal() == stoi(s)) //search decimal values
            {
                return counter; //return value found
            }
            else
            {
                counter++;
            }
            ptr = ptr->getNext();
        }
    }
    return -1; //if not found, return -1
}



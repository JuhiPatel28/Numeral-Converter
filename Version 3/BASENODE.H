//Juhi Patel
//jmp170130
//CS 1337.007

#ifndef BASENODE_H
#define BASENODE_H

#include <fstream>
#include <string>

class BaseNode
{
public:
    //constructors
    BaseNode();
    BaseNode(std::string r, int d);
    BaseNode(const BaseNode &cpy);

    //accessors
    std::string GetRoman();
    int GetDecimal();

    //pure virtual function
    virtual void getHi() = 0;

    //mutators
    void SetRoman(std::string r);
    void SetDecimal(int d);

    //destructor
    virtual ~BaseNode();

    //converion functions
    int r2d(std::string); //prototype roman to decimal conversion function
    std::string d2r(int); //prototype decimal to roman conversion function
    bool romanvalid(std::string); //to check validity of roman values
    bool decvalid(std::string); //to check validity of decimal values

    //overloaded operator
    friend std::ostream& operator<<(std::ostream& out, BaseNode& print);
    friend std::istream& operator>>(std::istream& in, BaseNode& input);

private:
    //private members
    std::string roman;
    int decimal;
};

#endif // BASENODE_H

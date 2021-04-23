//Juhi Patel
//jmp170130
//CS 1337.007

#include "BaseNode.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

std::ostream& operator<<(std::ostream& out, BaseNode& print) //overloaded << operator
{
    if(print.GetRoman() != "" && print.GetDecimal() != 0)
    {
       out << std::left << std::setw(16) << print.GetRoman() << std::setw(4) << print.GetDecimal() << std::endl; //print
    }
    return out; //return ostream
}

BaseNode::BaseNode() //default constructor
{
    roman = "";
    decimal = 0;
}

std::istream& operator>>(std::istream& in, BaseNode& input) //overloaded >> operator
{
    std::string temp;
    in >> temp;
    if(isdigit(temp[0])) //if arabic
    {
        if(input.decvalid(temp)) //if valid
        {
            input.SetDecimal(stoi(temp)); //put data in node
            string crom = input.d2r(stoi(temp));
            input.SetRoman(crom);
        }
        else //if not valid
        {
            input.SetDecimal(0);
        }

    }
    else if(isalpha(temp[0])) //if arabic
    {
        if(input.romanvalid(temp))
        {
            input.SetRoman(temp); //put data in node
            int dec = input.r2d(temp);
            string cdec = to_string(dec);
            input.SetDecimal(stoi(cdec));
        }
        else //if not valid
        {
            input.SetRoman("");
        }

    }
    return in; //return istream
}

BaseNode::BaseNode(std::string r, int d) //overloaded constructor
{
    roman = r;
    decimal = d;
}

BaseNode::BaseNode(const BaseNode &cpy) //overloaded constructor
{
    roman = cpy.roman;
    decimal = cpy.decimal;
}

std::string BaseNode::GetRoman() //roman accessor
{
    return roman;
}

int BaseNode::GetDecimal() //decimal accessor
{
    return decimal;
}

void BaseNode::SetRoman(std::string r) //roman mutator
{
    roman = r;
}

void BaseNode::SetDecimal(int d) //decimal mutator
{
    decimal = d;
}

BaseNode::~BaseNode() //destructor
{
}


bool BaseNode::romanvalid(string r) //validates roman numerals
{
    bool validnumber = true; //flag
    int cdec = r2d(r); //send to be converted
    string ccrom = d2r(cdec); //send to be converted
    if((cdec==-1)) //if conversion returns an error
    {
        validnumber = false; //not valid
    }
    else if(r != ccrom) //if conversion doesnt return an error, but roman numeral is in the wrong order
    {
        validnumber = false; //not valid
    }
    else if(!(cdec <= 4999 && cdec >= 1)) //if roman numeral is out of bounds
    {
        validnumber = false; //not valid
    }
    return validnumber;

}

bool BaseNode::decvalid(string d) //validates decimal numbers
{
    bool validnumber = true; //flag
    for(int counter = 0; counter < d.length(); counter++) //for all parts of the string
    {
        if(!isdigit(d[counter])) //if component is not a number
        {
            return false; //not valid
        }
    }
    int dec = stoi(d); //convert to integer
    if(!(dec <= 4999 && dec >= 1)) //if out of bounds
    {
        validnumber = false; //not valid
    }
    return validnumber;
}

string BaseNode::d2r(int decimal)
{
    string roman = ""; //string to store converted roman string
    int thousand, hundred, ten, one; //ints that will decide number of letters added to string
    int counter;

    thousand = decimal/1000; //find number of thousand values
    hundred = decimal%1000/100; //find number of hundred values
    ten = decimal%1000%100/10; //find number of ten values
    one = decimal%1000%100%10; //find number of one values

    if(thousand > 0 && thousand <= 4) //add M to string for every thousand value
    {
        for(counter = 0; counter < thousand; counter++)
        {
            roman += "M";
        }
    }

    if(hundred < 4 && hundred > 0) //add C to string for every thousand value
    {
        for(counter = 0; counter < hundred; counter++)
        {
            roman += "C";
        }
    }
    else if(hundred == 4) //unless there are four hundred values
    {
        roman += "CD";
    }
    else if(hundred == 5) //unless there are five hundred values
    {
        roman += "D";
    }
    else if(hundred > 5 && hundred < 9) //unless there are more than five hundred values in which case you subtract 5 from number of hundred values and add that to string with D
    {
        roman += "D";
        for(counter = 0; counter < (hundred-5); counter++)
        {
            roman += "C";
        }
    }
    else if(hundred == 9) //unless there are 9 hundred values
    {
        roman += "CM";
    }

    if(ten > 0 && ten < 4) //add X for every ten value
    {
        for(counter = 0; counter < ten; counter++)
        {
            roman += "X";
        }
    }
    else if(ten == 4) //unless there are 4 ten values
    {
        roman += "XL";
    }
    else if(ten == 5) //unless there are 5 ten values
    {
        roman += "L";
    }
    else if(ten >5 && ten < 9) //unless there are more than five ten values in which case you subtract 5 from number of ten values and add that to string with L
    {
        roman += "L";
        for(counter = 0; counter < (ten - 5); counter++)
        {
            roman += "X";
        }
    }
    else if(ten == 9) //unless there are 9 ten values
    {
        roman += "XC";
    }

    if(one > 0 && one < 4) //add I for every one value
    {
        for(counter = 0; counter < one; counter++)
        {
            roman += "I";
        }
    }
    else if(one == 4) //unless there are 4 one values
    {
        roman += "IV";
    }
    else if(one == 5) //unless there are 5 one values
    {
        roman += "V";
    }
    else if(one >5 && one < 9) //unless there are more than five one values in which case you subtract 5 from number of one values and add that to string with V
    {
        roman += "V";
        for(counter = 0; counter < (one - 5); counter++)
        {
            roman += "I";
        }
    }
    else if(one == 9) //unless there are 9 one values
    {
        roman += "IX";
    }
    return roman; //return newly converted string
}




int BaseNode::r2d(string cheese) //roman to decimal conversion
{
    int length = cheese.length(); //store length of array
    int store = 0; //will hold decimal value

    for(int counter = 0; counter < length; counter++) //while not at end of array
    {
        if(cheese[counter] == 'M') //checks value of array at index counter
        {
            store +=1000; //add appropriate value
        }
        else if(cheese[counter] == 'D' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
                cheese[counter+1] == 'M')
        {
            store -=500; //subtracts appropriate value
        }
        else if(cheese[counter] == 'D') //checks value of array at index counter
        {
            store +=500; //add appropriate value
        }
        else if(cheese[counter] == 'C' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
               (cheese[counter+1] == 'M' ||
                cheese[counter+1] == 'D'))
        {
            store -=100; //subtracts appropriate value
        }
        else if(cheese[counter] == 'C') //checks value of array at index counter
        {
            store +=100; //add appropriate value
        }
        else if(cheese[counter] == 'L' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
               (cheese[counter+1] == 'M' ||
                cheese[counter+1] == 'D' ||
                cheese[counter+1] == 'C'))
        {
            store -=50; //subtracts appropriate value
        }
        else if(cheese[counter] == 'L') //checks value of array at index counter
        {
            store +=50; //add appropriate value
        }
        else if(cheese[counter] == 'X' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
               (cheese[counter+1] == 'M' ||
                cheese[counter+1] == 'D' ||
                cheese[counter+1] == 'C' ||
                cheese[counter+1] == 'L'))
        {
             store -=10; //subtracts appropriate value
        }
        else if(cheese[counter] == 'X') //checks value of array at index counter
        {
            store +=10; //add appropriate value
        }
         else if(cheese[counter] == 'V' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
               (cheese[counter+1] == 'M' ||
                cheese[counter+1] == 'D' ||
                cheese[counter+1] == 'C' ||
                cheese[counter+1] == 'L' ||
                cheese[counter+1] == 'X'))
        {
            store -=5; //subtracts appropriate value
        }
        else if(cheese[counter] == 'V') //checks value of array at index counter
        {
            store +=5; //add appropriate value
        }
        else if(cheese[counter] == 'I' && //checks value of array at index counter and one more that the index counter to see if there is a larger value in front of a smaller one
               (cheese[counter+1] == 'M' ||
                cheese[counter+1] == 'D' ||
                cheese[counter+1] == 'C' ||
                cheese[counter+1] == 'L' ||
                cheese[counter+1] == 'X' ||
                cheese[counter+1] == 'V'))
        {
            store -=1; //subtracts appropriate value
        }
        else if(cheese[counter] == 'I') //checks value of array at index counter
        {
            store +=1; //add appropriate value
        }
        else
        {
            return -1;
        }
    }
    return store; //returns newly converted decimal
}

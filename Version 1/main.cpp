#include <string> //allow strings to be used
#include <fstream> //allow writing to and from file
using namespace std;

int r2d(string); //prototype roman to decimal conversion function
string d2r(int); //prototype decimal to roman conversion function

int main() //main function
{
    fstream file ("numbers3.txt", ios::in | ios::out | ios::binary); //open file that can have data written and read
    string roman, croman; //string variables to store data from file and send to conversion function
    char peek, newline; //char variables to check for spaces and \n
    int decimal, cdecimal, position; //int variables to store data from file, send to conversion function, and store pointer position
    bool eof= false; //boolean for eof check

    if(!file.fail()) //if file opens
    {
        while(!eof) //while eof is not false
        {
            eof = file.eof(); //set eof again
            position = file.tellg(); //store pointer location
            peek = file.peek(); //store peek() value in variable
            if(peek == ' ') //check for space character
            {
                file.seekg((16+position), ios::beg); //move pointer 16 spaces up on current line
                file >> decimal; //read and store decimal value from file
                croman = d2r(decimal); //send decimal value to conversion function and store result in string
                file.seekp(position, ios::beg); //put pointer back at the beginning of the line
                file << croman; //write string to file
            }
            else //if peek is not a space character
            {
                file >> roman; //read the roman value to a string
                cdecimal = r2d(roman); //send roman value to conversion function and store results in int
                file.seekp((16+position), ios::beg); //set pointer 16 spaces forward on current line
                file << cdecimal; //write decimal value to file
            }

            while(file.get(newline)) //move pointer to newline character
            {
                if(newline == '\n')
                {
                    break;
                }
            }
            file.clear(); //clear badbits
        }

    }
    return 0;
}

int r2d(string cheese) //roman to decimal conversion
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
    }
    return store; //returns newly converted decimal
}


string d2r(int decimal)
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
        roman = "XL";
    }
    else if(ten == 5) //unless there are 5 ten values
    {
        roman = "L";
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


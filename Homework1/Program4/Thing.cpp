/*
* Author: Cole Barbes
* Creation Date: 09/03/23
* Last Edited: 09/03/23
* Description: Defines a class structure called thing
*/
#include "Thing.h"
#include <string>

/*
 * Constructor
*/
Thing::Thing(int a, int b)
{
    A = a;
    B = (b!=0) ? b : 1;
}

/*
 * Destructor
*/
Thing::~Thing(){}

/*
 * Description: return A from the class
 * Return: integer value of A
*/
int Thing::getA()
{
    return A;
}

/*
 * Description: return B from the class
 * Return: integer value of B
*/
int Thing::getB()
{
    return B;
}

/*
 * Description: take a parameter and set the value of A
 * Parameters: integer value for A
*/
void Thing::setA(int a)
{
    A = a;
}

/*
 * Description: take a parameter and set the value of B that cannot be 0
 * Parameters: integer value for B
*/
void Thing::setB(int b)
{
    B = (b!=0) ? b : 1;
}

/*
 * Description: take 2 parameters and set both A and B
 * Parameters: integer value for A and B
*/
void Thing::set(int first, int second)
{
    A = first;
    B = (second!=0) ? second : 1;
}

/*
 * Description: overload the == operator 
 * Parameters: the other "Thing"
 * Return: true if A*X.B = B*X.A
*/
bool Thing::operator==(const Thing &other)
{
    return (A*other.B) == (B*other.A);
}

/*
 * Description: overload the != operator
 * Parameters: the other "Thing"
 * Return: true if A*X.B != B*X.A
*/
bool Thing::operator!=(const Thing &other)
{
    return (A*other.B) != (B*other.A);
}

/*
 * Description: overload the < operator
 * Parameters: the other "Thing"
 * Return: true if A*X.B < B*X.A
*/
bool Thing::operator<(const Thing &other)
{
    return ((A*other.B) < (B*other.A));
}

/*
 * Description: overload the > operator
 * Parameters: the other "Thing"
 * Return: true if A*other.B > B*other.A
*/
bool Thing::operator>(const Thing &other)
{
    return ((A*other.B) > (B*other.A));
}

/*
 * Description: overload the <= operator
 * Parameters: the other "Thing"
 * Return true if A*other.B <= B*other.B
 *
*/
bool Thing::operator<=(const Thing &other)
{
    return ((A*other.B) <= (B*other.A));
}

/*
 * Description: overload the >= operator
 * Parameters: the other "Thing"
 * Return true if A*other.B >= B*other.B 
*/
bool Thing::operator>=(const Thing &other)
{
    return ((A*other.B) >= (B*other.A));
}
/*
 * Description: Overload the print statement to print the values of A and B
 * Parameters: The stream and the output thing
 * Return: the stream
*/
ostream& operator<<(ostream & strm, const Thing& output)
{
    strm<<"("<<output.A<<", "<<output.B<<")";
    return strm;
}

/*
* Author: Cole Barbes
* Creation Date: 09/03/23
* Last Edited: 09/03/23
* Description: Defines a class structure called thing
*/
#include "Thing.h"
#include <string>

/*
*/
Thing::Thing(int a, int b)
{
    A = a;
    B = (b!=0) ? b : 1;
}

/*
*/
Thing::~Thing(){}

/*
*/
int Thing::getA()
{
    return A;
}

/*
*/
int Thing::getB()
{
    return B;
}

/*
*/
void Thing::setA(int a)
{
    A = a;
}

/*
*/
void Thing::setB(int b)
{
    B = (b!=0) ? b : 1;
}

/*
*/
void Thing::set(int first, int second)
{
    A = first;
    B = (second!=0) ? second : 1;
}

/*
*/
bool Thing::operator==(const Thing other)
{
    return (A*other.B) == (B*other.A);
}

/*
*/
bool Thing::operator!=(const Thing other)
{
    return (A*other.B) != (B*other.A);
}

/*
*/
bool Thing::operator<(const Thing other)
{
    return (A*other.B) < (B*other.A);
}

/*
*/
bool Thing::operator>(const Thing other)
{
    return (A*other.B) > (B*other.A);
}

/*
*/
bool Thing::operator<=(const Thing other)
{
    return (A*other.B) <= (B*other.A);
}

/*
*/
bool Thing::operator>=(const Thing other)
{
    return (A*other.B) >= (B*other.A);
}

/*
*/
ostream& operator<<(ostream & strm, const Thing& output)
{
    strm<<"("<<output.A<<", "<<output.B<<")";
    return strm;
}
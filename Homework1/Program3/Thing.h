/*
* Author: Cole Barbes
* Creation Date: 09/03/23
* Last Edited: 09/03/23
* Description: Defines a class structure called thing
*/
#ifndef THING_H
#define THING_H

#include <iostream>// include iostream for overload

using namespace std;

class Thing{
    private:
        int A;
        int B;
    public: 
        // constructor and destructor
        Thing(int A = 0, int B = 1);
        ~Thing();

        // get functions
        int getA();
        int getB();

        // set functions
        void setA(int);
        void setB(int);
        void set(int, int);

        // overloaded boolean operations
        bool operator==(const Thing);
        bool operator!=(const Thing);
        bool operator<(const Thing);
        bool operator>(const Thing);
        bool operator<=(const Thing);
        bool operator>=(const Thing);

        // overloaded stream out 
        friend ostream& operator<<(ostream &, const Thing&);
};

#endif
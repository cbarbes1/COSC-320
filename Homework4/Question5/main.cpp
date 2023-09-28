#include <iostream>
#include "crossref.h"

using namespace std;

int main(){

    crossref theBookCrossReference("new.txt");

    theBookCrossReference.printDataBase();

    return 0;

}

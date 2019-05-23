#include <iostream>

#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"

int main() {

    CNumber n1(4);
    CString s1("Hello World!");
    CFunction f1("=sin(3)");

    std::cout << n1 << " " << s1;


    return 0;
}
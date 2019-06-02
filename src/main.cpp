#include <iostream>

#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"

int main() {

    CNumber n1(4);
    CString s1("Hello World!");
    CFunction f1("=Sin(3)");
    CFunction f2("=cin(3)");
    COperation o1("=3+4");

    std::cout << "----------------------------" << std::endl;
    std::cout << n1 << std::endl;
    std::cout << s1 << std::endl;
    std::cout << f1 << std::endl;
    std::cout << f2 << std::endl;


    return 0;
}
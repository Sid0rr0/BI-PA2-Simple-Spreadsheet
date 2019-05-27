#include <utility>
#include <iostream>
#include "CFunction.h"

CFunction::CFunction(std::string mInput): m_Input(std::move(mInput)){
    if(m_Input.at(0) != '=') {
        std::cout << "Not a function" << std::endl;
    }

    ParseInput(m_Input);
}

CFunction::~CFunction() = default;

void CFunction::Print (std::ostream & os) const {
    os << m_Input;
}

std::ostream &operator<<(std::ostream &os, const CFunction &function) {
    function.PrintValue(os);
    return os;
}

void CFunction::PrintValue(std::ostream &os) const {
    os << m_Result;
}

/*bool CFunction::IsNumber() const {
    return false;
}*/

CCell::CType CFunction::CellType() const {
    return FUNC;
}

int CFunction::ParseInput(const std::string& input) {
    std::string delimiter = "=";
    size_t pos = 0, len = 0;
    std::string token;

    auto start = input.find('=')+1;
    auto end = input.find('(');
    m_Operation = input.substr(start, end - start);
    std::cout << m_Operation << std::endl;

    start = input.find('(')+1;
    end = input.find(')');

    m_Value = std::stod(input.substr(start, end - start));
    std::cout << m_Value << std::endl;

    /*while (end != std::string::npos)
    {
        std::cout << input.substr(start, end - start) << std::endl;
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }

    std::cout << input.substr(start, end) << std::endl;*/
    return 1;
}





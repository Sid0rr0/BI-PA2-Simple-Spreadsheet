

//
// Created by hung on 12.5.19.
//

#include "CNumber.h"
#include <string>
#include <utility>


CNumber::CNumber(std::string mInput) : m_Input(std::move(mInput)) {
    m_Result = std::stod(m_Input);
}

CNumber::~CNumber() = default;

std::ostream &operator<<(std::ostream &os, const CNumber &number) {
    number.Print(os);
    return os;
}

void CNumber::Print(std::ostream &os) const {
    os << m_Result;
}

CCell::CType CNumber::CellType() const {
    return NUM;
}

std::string CNumber::GetOutput() const {
    return m_Input;
}

/*bool CNumber::IsNumber() const {
    return true;
}*/

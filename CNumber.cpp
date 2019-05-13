//
// Created by hung on 12.5.19.
//

#include "CNumber.h"

CNumber::CNumber(double mVal) : m_Val(mVal) {}

CNumber::~CNumber() = default;

std::ostream &operator<<(std::ostream &os, const CNumber &number) {
    number.Print(os);
    return os;
}

void CNumber::Print(std::ostream &os) const {
    os << m_Val;
}

bool CNumber::isNumber() const {
    return true;
}

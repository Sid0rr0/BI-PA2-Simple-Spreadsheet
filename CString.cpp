#include <utility>

//
// Created by hung on 12.5.19.
//

#include "CString.h"

CString::CString(std::string mVal) : m_Val(std::move(mVal)) {}

CString::~CString() = default;

std::ostream &operator<<(std::ostream &os, const CString &string) {
    string.Print(os);
    return os;
}

void CString::Print(std::ostream &os) const {
    os << m_Val;
}

bool CString::isNumber() const {
    return false;
}

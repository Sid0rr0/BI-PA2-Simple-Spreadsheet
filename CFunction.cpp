#include <utility>

//
// Created by hung on 12.5.19.
//

#include "CFunction.h"

CFunction::CFunction(std::string mOperation, double mVal) : m_Operation(std::move(mOperation)), m_Value(mVal) {}

CFunction::~CFunction() = default;

void CFunction::Print (std::ostream & os) const {
    os << "=" << m_Operation << "(" << m_Value << ")";
}

std::ostream &operator<<(std::ostream &os, const CFunction &function) {
    function.PrintValue(os);
    return os;
}

void CFunction::PrintValue(std::ostream &os) const {
    os << m_Result;
}

bool CFunction::isNumber() const {
    return false;
}



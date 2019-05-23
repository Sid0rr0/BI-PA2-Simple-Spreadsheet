#include <utility>
#include "CFunction.h"

CFunction::CFunction(std::string mInput): m_Input(std::move(mInput)){

}

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

/*bool CFunction::IsNumber() const {
    return false;
}*/

CCell::CType CFunction::CellType() const {
    return FUNC;
}





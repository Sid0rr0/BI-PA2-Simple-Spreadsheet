#include <utility>
#include "COperation.h"

COperation::COperation(std::string mInput): m_Input(std::move(mInput)) {

}

COperation::~COperation() = default;

void COperation::Print(std::ostream &os) const {
    os << this->m_Input;
}

CCell::CType COperation::CellType() const {
    return NUM;
}

std::ostream &operator<<(std::ostream &os, const COperation &operation) {
    operation.PrintResult(os);
    return os;
}

void COperation::PrintResult(std::ostream &os) const {
    os << this->m_Result;
}

bool COperation::getResult() {
    return false;
}

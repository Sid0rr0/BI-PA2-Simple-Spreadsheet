#include <utility>
#include "CString.h"

CString::CString(std::string mVal) : m_Input(std::move(mVal)) {}

CString::~CString() = default;

std::ostream &operator<<(std::ostream &os, const CString &string) {
    string.Print(os);
    return os;
}

void CString::Print(std::ostream &os) const {
    os << m_Input;
}

CCell::CType CString::CellType() const {
    return STR;
}

std::string CString::GetOutput() const {
    return m_Input;
}

bool CString::HasChildren() {
    return !m_Children.empty();
}

void CString::AddChild(const std::string &child) {
    m_Children.push_back(child);
}

std::vector<std::string> CString::GetChildren() {
    return std::vector<std::string>();
}

void CString::Update(const std::string &content) {
    m_Input = content;
}

void CString::AddParent(const std::string &parent) {

}

bool CString::HasParents() {
    return false;
}

std::set<std::string> CString::GetParents() {
    return std::set<std::string>();
}

void CString::CycleSwitch() {

}


#include <utility>
#include "CString.h"

CString::CString(std::string mVal) : m_Input(std::move(mVal)) {
    m_Cycle = false;
    m_Error = false;
}

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
    if(m_Error)
        return "Error";
    if(m_Cycle)
        return "Cycle";
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
    m_Parents.insert(parent);
}

bool CString::HasParents() {
    return !m_Parents.empty();
}

std::set<std::string> CString::GetParents() {
    return m_Parents;
}

void CString::CycleSwitch() {
    m_Cycle = true;
}

std::string CString::GetInput() const {
    return m_Input;
}

bool CString::InCycle() {
    return m_Cycle;
}

void CString::DeleteParent(std::string parent) {
    for(const auto& i : m_Parents) {
        if (i == parent)
            m_Parents.erase(i);
    }
}

void CString::DeleteChild(const std::string &child) {
    int j = 0;
    for(const auto& i : m_Children) {
        if (i == child)
            m_Children.erase(m_Children.begin()+j);

        j++;
    }
}

void CString::CycleFalse() {
    m_Cycle = false;
}

void CString::ErrorTrue() {
    m_Error = true;
}


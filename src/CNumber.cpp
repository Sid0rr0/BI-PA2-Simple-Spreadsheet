

//
// Created by hung on 12.5.19.
//

#include "CNumber.h"
#include <string>
#include <utility>

CNumber::CNumber(std::string mInput) : m_Input(std::move(mInput)) {
    m_Result = std::stod(m_Input);
    m_Cycle = false;
    m_Error = false;
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
    if(m_Error)
        return "Error";
    if(m_Cycle)
        return "Cycle";
    return m_Input;
}

void CNumber::AddChild(const std::string& child) {
    this->m_Children.push_back(child);
}

bool CNumber::HasChildren() {

    return !this->m_Children.empty();
}

std::vector<std::string> CNumber::GetChildren() {
    return this->m_Children;
}

void CNumber::Update(const std::string &content) {
    m_Result = std::stod(content);
}

void CNumber::AddParent(const std::string &parent) {
    m_Parents.insert(parent);
}

bool CNumber::HasParents() {
    return !m_Parents.empty();
}

std::set<std::string> CNumber::GetParents() {
    return m_Parents;
}

void CNumber::CycleSwitch() {
    m_Cycle = true;
}

std::string CNumber::GetInput() const {
    return m_Input;
}

bool CNumber::InCycle() {
    return m_Cycle;
}

void CNumber::DeleteParent(std::string parent) {
    for(const auto& i : m_Parents) {
        if (i == parent)
            m_Parents.erase(i);
    }
}

void CNumber::DeleteChild(const std::string &child) {
    int j = 0;
    for(const auto& i : m_Children) {
        if (i == child)
            m_Children.erase(m_Children.begin()+j);

        j++;
    }
}

void CNumber::CycleFalse() {
    m_Cycle = false;
}

void CNumber::ErrorTrue() {
    m_Error = true;
}




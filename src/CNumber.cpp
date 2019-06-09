

//
// Created by hung on 12.5.19.
//

#include "CNumber.h"
#include <string>
#include <utility>

CNumber::CNumber(std::string mInput) : m_Input(std::move(mInput)) {
    m_Result = std::stod(m_Input);
    m_Cycle = false;
}

CNumber::CNumber(std::string mInput, int mXPos, int mYPos) : m_Input(std::move(mInput)), m_xPos(mXPos), m_yPos(mYPos) {
    m_Result = std::stod(m_Input);
    m_Cycle = false;
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

int CNumber::getMXPos() const {
    return m_xPos;
}

void CNumber::setMXPos(int mXPos) {
    m_xPos = mXPos;
}

int CNumber::getMYPos() const {
    return m_yPos;
}

void CNumber::setMYPos(int mYPos) {
    m_yPos = mYPos;
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
    m_Cycle = !m_Cycle;
}

std::string CNumber::GetInput() const {
    return m_Input;
}

bool CNumber::InCycle() {
    return m_Cycle;
}




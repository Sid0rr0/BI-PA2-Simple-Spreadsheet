

//
// Created by hung on 12.5.19.
//

#include "CNumber.h"
#include <string>
#include <utility>


CNumber::CNumber(std::string mInput, int mXPos, int mYPos) : m_Input(std::move(mInput)), m_xPos(mXPos), m_yPos(mYPos) {
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

void CNumber::AddChild(const std::string& child) {
    this->childern.push_back(child);
}

bool CNumber::HasChildren() {

    return !this->childern.empty();
}

std::vector<std::string> CNumber::GetChildren() {
    return this->childern;
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


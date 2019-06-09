#include <utility>
#include <iostream>
#include <math.h>
#include <sstream>
#include "COperation.h"

COperation::COperation(std::string mInput): m_Input(std::move(mInput)) {
    m_Cycle = false;
    GetResult();
    ParseInput(m_Input);
    GetResult();
}

COperation::~COperation() = default;

void COperation::Print(std::ostream &os) const {
    os << this->m_Input;
}

CCell::CType COperation::CellType() const {
    return OP;
}

std::ostream &operator<<(std::ostream &os, const COperation &operation) {
    operation.PrintResult(os);
    return os;
}

void COperation::PrintResult(std::ostream &os) const {
    os << this->m_Result;
}

bool COperation::GetResult() {
    if(m_Operator == '+')
        m_Result = m_OperandA + m_OperandB;
    else if (m_Operator == '-')
        m_Result = m_OperandA - m_OperandB;
    else if (m_Operator == '*')
        m_Result = m_OperandA * m_OperandB;
    else if (m_Operator == '/') {
        if(m_OperandB != 0)
            m_Result = m_OperandA /  m_OperandB;
        else
            return false;
    }
    else if (m_Operator == '^')
        m_Result = pow(m_OperandA, m_OperandB);

    return true;
}

bool COperation::ParseInput(const std::string &input) {
    auto start = input.find('=') + 1;


    auto end = input.find('+');
    if(end == std::string::npos) {
        end = input.find('-');
        if(end == std::string::npos) {
            end = input.find('*');
            if(end == std::string::npos) {
                end = input.find('/');
                if(end == std::string::npos) {
                    end = input.find('^');
                    m_Operator = '^';
                } else
                    m_Operator = '/';
            } else
                m_Operator = '*';
        } else
            m_Operator = '-';
    } else
        m_Operator = '+';

    m_OperandA = std::stod(input.substr(start, end - start));
    m_OperandB = std::stod(input.substr(end + 1));

    /*std::cout << "------------------------" << std::endl;
    std::cout << m_Operator << std::endl;
    std::cout << m_OperandA << std::endl;
    std::cout << m_OperandB << std::endl;*/

    return true;
}

std::string COperation::GetOutput() const {
    if(m_Cycle)
        return "Cycle";

    std::ostringstream oss;
    oss << m_Result;
    return oss.str();
}

void COperation::AddChild(const std::string &child) {
    m_Children.push_back(child);
}

bool COperation::HasChildren() {
    return !m_Children.empty();
}

std::vector<std::string> COperation::GetChildren() {
    return m_Children;
}

void COperation::Update(const std::string &content) {
    char* middle;
    m_OperandA = strtod(content.c_str(), &middle);
    m_OperandA = strtod(middle, nullptr);

    GetResult();
}

void COperation::AddParent(const std::string &parent) {
    m_Parents.insert(parent);
}

bool COperation::HasParents() {
    return !m_Parents.empty();
}

std::set<std::string> COperation::GetParents() {
    return m_Parents;
}

void COperation::CycleSwitch() {
    m_Cycle = !m_Cycle;
}

std::string COperation::GetInput() const {
    return m_Input;
}

bool COperation::InCycle() {
    return m_Cycle;
}

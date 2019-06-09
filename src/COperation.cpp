#include <utility>
#include <iostream>
#include <math.h>
#include <sstream>
#include "COperation.h"

COperation::COperation(std::string mInput): m_Input(std::move(mInput)) {
    m_Cycle = false;
    m_Error = false;

    ParseInput(m_Input);

    if(!m_Error)
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

                    if(end == std::string::npos) {
                        m_Error = true;
                        return false;
                    }
                } else
                    m_Operator = '/';
            } else
                m_Operator = '*';
        } else
            m_Operator = '-';
    } else
        m_Operator = '+';

    m_OperandA = std::stod(input.substr(start, end - start));

    char * check;
    m_OperandA = std::strtod(input.substr(start, end - start).c_str(), &check);
    std::string s = std::string(check);
    if(!s.empty()) {
        m_Error = true;
        return false;
    }

    m_OperandB = std::strtod(input.substr(end + 1).c_str(), &check);
    s = std::string(check);
    if(!s.empty()) {
        m_Error = true;
        return false;
    }

    return true;
}

std::string COperation::GetOutput() const {
    if(m_Error)
        return "Error";
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
    m_Cycle = true;
}

std::string COperation::GetInput() const {
    return m_Input;
}

bool COperation::InCycle() {
    return m_Cycle;
}

void COperation::DeleteParent(std::string parent) {
    for(const auto& i : m_Parents) {
        if (i == parent)
            m_Parents.erase(i);
    }
}

void COperation::DeleteChild(const std::string &child) {
    int j = 0;
    for(const auto& i : m_Children) {
        if (i == child)
            m_Children.erase(m_Children.begin()+j);

        j++;
    }
}

void COperation::CycleFalse() {
    m_Cycle = false;
}

void COperation::ErrorTrue() {
    m_Error = true;
}

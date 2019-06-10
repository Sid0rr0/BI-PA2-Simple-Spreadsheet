#include <utility>

#include <utility>

#include <utility>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include "CFunction.h"
#include "CTable.h"
#include "CNumber.h"


CFunction::CFunction(std::string mInput): m_Input(std::move(mInput)){
    if(this->m_Input.at(0) != '=')
        m_Error = true;

    m_Cycle = false;
    m_Error = false;

    ParseInput(this->m_Input);

    if(!isSupportedFunction(this->m_Name)) {
        this->m_Result = 0;
        m_Error = true;
    }
    else
        getResult();
}

CFunction::CFunction(std::string mInput, std::vector<std::string> cells): m_Input(std::move(mInput)), m_Cells(std::move(cells)) {
    /*for(const auto& i : cells) {
        m_Cells.push_back(i);
    }*/

    m_Cycle = false;
    m_Error = false;

    ParseInput(this->m_Input);

    if(!isSupportedFunction(this->m_Name)) {
        this->m_Result = 0;
        m_Error = true;
    }
    else
        getResult();
}

CFunction::CFunction(std::string mInput, CCell *cell): m_Input(std::move(mInput)){
    this->cell = cell;
    //std::cout << "***" << this->cell->GetOutput() << "***" << std::endl;
    m_Cycle = false;
    m_Error = false;

    ParseInput(this->m_Input);

    if(!isSupportedFunction(this->m_Name)) {
        this->m_Result = 0;
        m_Error = true;
    }
    else
        getResult();
}


CFunction::~CFunction() = default;

void CFunction::Print (std::ostream & os) const {
    os << this->m_Input;
}

void CFunction::PrintResult(std::ostream &os) const {
    os << this->m_Result;
}

CCell::CType CFunction::CellType() const {
    return FUNC;
}

bool CFunction::ParseInput(const std::string& input) {
    auto start = input.find('=')+1;
    auto end = input.find('(');

    this->m_Name = input.substr(start, end - start);
    std::transform(this->m_Name.begin(), this->m_Name.end(), this->m_Name.begin(), ::toupper);

    if(input.find(':') != std::string::npos)
        return true;

    start = input.find('(')+1;
    end = input.find(')');

    std::string argument = input.substr(start, end - start);
    char* check;
    std::string s;
    std::strtod(input.substr(start, end - start).c_str(), &check);
    s = std::string(check);
    if(s.empty()) {
        m_Value = std::strtod(input.substr(start, end - start).c_str(), &check);
        s = std::string(check);
        if(!s.empty()) {
            m_Error = true;
        }
    } else {
        m_Value = std::strtod(cell->GetOutput().c_str(), &check);
        s = std::string(check);
        if(!s.empty()) {
            m_Error = true;
        }
        //std::cout << "###" << m_Value << "###" << std::endl;
    }
    return true;
}

bool CFunction::getResult() {
    double tmp = 0;
    char * check;
    std::string s;
    this->m_Result = 0;

    if(this->m_Name == "SIN") {
        this->m_Result = sin(m_Value);
        return true;
    }
    else if(this->m_Name == "COS"){
        this->m_Result = sin(m_Value);
        return true;
    }
    else if(this->m_Name == "ABS"){
        this->m_Result = fabs(m_Value);
        return true;
    }
    else if(this->m_Name == "LOG"){
        this->m_Result = log(m_Value);
        return true;
    }
    else if(this->m_Name == "COS"){
        this->m_Result = cos(m_Value);
        return true;
    }
    else if(this->m_Name == "SUM"){
        for(const auto& i : m_Cells) {
            tmp = std::strtod(i.c_str(), &check);
            s = std::string(check);
            if(!s.empty()) {
                m_Result = 0;
                m_Error = true;
                return false;
            }
            this->m_Result += tmp;
        }
        return true;
    }
    else if(this->m_Name == "COUNT"){
        for(const auto& i : m_Cells) {
            std::strtod(i.c_str(), &check);
            s = std::string(check);
            if(s.empty() && !i.empty()) {
                this->m_Result++;
            }
        }
        return true;
    }
    else if(this->m_Name == "AVG"){
        int count = 0;
        for(const auto& i : m_Cells) {
            tmp = std::strtod(i.c_str(), &check);
            s = std::string(check);
            if(!s.empty()) {
                m_Result = 0;
                m_Error = true;
                return false;
            }
            this->m_Result += tmp;
            if(!i.empty())
                count++;
        }
        this->m_Result /= count;
        return true;

    }

    m_Error = true;
    return false;
}

bool CFunction::isSupportedFunction(const std::string &func) {
    if(func == "SIN")
        return true;
    else if(func == "COS")
        return true;
    else if(func == "ABS")
        return true;
    else if(func == "LOG")
        return true;
    else if(func == "COS")
        return true;
    else if(func == "AVG")
        return true;
    else if(func == "SUM")
        return true;
    else if(func == "COUNT")
        return true;

    m_Error = true;
    return false;
}

std::ostream &operator<<(std::ostream &os, const CFunction &function) {
    function.PrintResult(os);
    return os;
}

std::string CFunction::GetOutput() const {
    if(m_Cycle)
        return "Cycle";

    if(m_Error)
        return "Error";

    std::ostringstream oss;
    oss << m_Result;
    return oss.str();
}

bool CFunction::HasChildren() {

    return !m_Children.empty();
}

std::vector<std::string> CFunction::GetChildren() {
    return m_Children;
}

void CFunction::AddChild(const std::string &child) {
    m_Children.push_back(child);
}

void CFunction::Update(const std::string &content) {
    m_Value = std::stod(content);
    getResult();
}

void CFunction::AddParent(const std::string &parent) {
    m_Parents.insert(parent);
}

bool CFunction::HasParents() {
    return !m_Parents.empty();
}

std::set<std::string> CFunction::GetParents() {
    return m_Parents;
}

void CFunction::CycleSwitch() {
    m_Cycle = true;
}

std::string CFunction::GetInput() const {
    return m_Input;
}

bool CFunction::InCycle() {
    return m_Cycle;
}

void CFunction::DeleteParent(std::string parent) {
    for(const auto& i : m_Parents) {
        if (i == parent)
            m_Parents.erase(i);
    }
}

void CFunction::DeleteChild(const std::string &child) {
    int j = 0;
    for(const auto& i : m_Children) {
        if (i == child)
            m_Children.erase(m_Children.begin()+j);
        j++;
    }
}

void CFunction::CycleFalse() {
    m_Cycle = false;
}

void CFunction::ErrorTrue() {
    m_Error = true;
}









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
    if(this->m_Input.at(0) != '=') {
        std::cout << "Not a function" << std::endl;
    }

    ParseInput(this->m_Input);

    if(!isSupportedFunction(this->m_Name))
        this->m_Result = 0;
    else
        getResult();
}

CFunction::CFunction(std::string mInput, CCell *cell): m_Input(std::move(mInput)){
    this->cell = cell;
    std::cout << "***" << this->cell->GetOutput() << "***" << std::endl;

    ParseInput(this->m_Input);

    if(!isSupportedFunction(this->m_Name))
        this->m_Result = 0;
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

/*bool CFunction::IsNumber() const {
    return false;
}*/

CCell::CType CFunction::CellType() const {
    return FUNC;
}

bool CFunction::ParseInput(const std::string& input) {
    auto start = input.find('=')+1;
    auto end = input.find('(');

    this->m_Name = input.substr(start, end - start);
    std::transform(this->m_Name.begin(), this->m_Name.end(), this->m_Name.begin(), ::toupper);
    //std::cout << m_Name << std::endl;

    start = input.find('(')+1;
    end = input.find(')');

    std::string argument = input.substr(start, end - start);
    char* check;
    if(isdigit(argument.at(0))) {
        m_Value = std::stod(input.substr(start, end - start));
        std::cout << "$$$" << m_Value << "$$$" << std::endl;
        //todo check if number
    } else {
        /*int xCoor = argument.at(0) - 'A';
        argument.erase(0, 1);

        int yCoor = std::strtol(argument.c_str(), &check, 10) - 1;
        std::cout << "============== " << yCoor << " " << xCoor << std::endl;
        std::string s = std::string(check);
        if(!s.empty()) {
            return false;
        }

        CTable t;
        m_Value = std::strtod((t.GetOutput(yCoor, xCoor)).c_str(), &check);*/
        m_Value = std::strtod(cell->GetOutput().c_str(), &check);
        std::cout << "###" << m_Value << "###" << std::endl;
        //todo check if num

    }

    //m_Value = std::stod(input.substr(start, end - start));
    //std::cout << m_Value << std::endl;

    /*while (end != std::string::npos)
    {
        std::cout << input.substr(start, end - start) << std::endl;
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }

    std::cout << input.substr(start, end) << std::endl;*/
    return true;
}

bool CFunction::getResult() {
/*    if(!isSupportedFunction(this->m_Name)) {
        this->m_Result = 0;
        return false;
    }*/

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

    return false;
}

bool CFunction::isSupportedFunction(const std::string &func) const {
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

    return false;
}

std::ostream &operator<<(std::ostream &os, const CFunction &function) {
    if(!function.isSupportedFunction(function.m_Name)) {
        os << "Undefined";
        return os;
    }

    function.PrintResult(os);
    return os;
}

std::string CFunction::GetOutput() const {
    std::ostringstream oss;
    oss << m_Result;
    return oss.str();
}

bool CFunction::HasChildren() {
    return false;
}

std::vector<std::string> CFunction::GetChildren() {
    return std::vector<std::string>();
}

void CFunction::AddChild(const std::string &child) {

}

void CFunction::Update(const std::string &content) {
    m_Value = std::stod(content);
    getResult();
    std::cout << "!!!!!!!!" << m_Result << "!!!!!!!!!!" << std::endl;
}







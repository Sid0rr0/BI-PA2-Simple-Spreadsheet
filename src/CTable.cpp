//
// Created by hung on 2.6.19.
//

#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "CTable.h"
#include "CCursor.h"
#include "CCell.h"
#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"



CTable::CTable(){
    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_WHITE);
    }

    getmaxyx(stdscr, this->m_YMax, this->m_XMax);

    addstr("Input: ");
    mvaddstr(1, 0, "Output: ");
    mvprintw(0, 50, "Max: %d %d", this->m_YMax, this->m_XMax);
    mvprintw(0, 70, "Max Fake: %d %d", (m_YMax - 5) / 2, (m_XMax - 4) / 10);

    DrawHorizontalLines(this->m_YMax, this->m_XMax);
    DrawCoordinates(this->m_YMax, this->m_XMax);
    DrawVerticalLines(this->m_YMax, this->m_XMax);

   /* m_Array.resize((m_YMax - 5) / 2);
    m_Array.reserve((m_YMax - 5) / 2);

    mvprintw(0, 90, "m_Array size: %d", m_Array.size());
    for (auto & i : m_Array) {
        i.resize((m_XMax - 4) / 10);
        i.reserve((m_XMax - 4) / 10);
        i.push_back(new CString(""));

    }
    mvprintw(0, 110, "m_Array FinalSize: %d", m_Array.size());
    mvprintw(0, 140, "m_Array.at(0): %d", m_Array.at(0).size());*/

    m_Array = new CCell**[(m_YMax - 5) / 2];
    for (int j = 0; j < (m_YMax - 5) / 2; ++j) {
        m_Array[j] = new CCell*[(m_XMax - 4) / 10];
    }

    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {
            m_Array[i][j] = new CString("");
        }
    }

}

CTable::~CTable() {
    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {
            delete(m_Array[i][j]);
        }
    }

    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        delete[](m_Array[i]);
    }
    delete[](m_Array);
}


void CTable::DrawCoordinates(int yMax, int xMax) {
    int c = 1;

    m_X = 1;
    m_Y = 6;
    move(m_Y, m_X);
    while(m_Y <= yMax) {
        printw("%d", c);
        c++;
        m_Y += 2;
        move(m_Y, m_X);
    }

    m_X = 8;
    m_Y = 4;
    move(m_Y, m_X);
    c = 'A';
    while(m_X <= xMax) {
        printw("%c", c);
        c++;
        m_X += 10;
        move(m_Y, m_X);
    }
}

void CTable::DrawHorizontalLines(int yMax, int xMax) {
    m_X = 0, m_Y = 5;
    move(m_Y, m_X);
    while(m_Y <= yMax) {
        hline('-', xMax);
        m_Y += 2;
        move(m_Y, m_X);
    }
}

void CTable::DrawVerticalLines(int yMax, int xMax) {
    m_X = 3;
    m_Y = 4;
    move(m_Y, m_X);
    while(m_X <= xMax) {
        vline('|', yMax);
        m_X+=10;
        move(m_Y, m_X);
    }
}

std::pair<int, int> CTable::GetFakeCoordinates(WINDOW *window) {
    getyx(window, m_Y, m_X);
    int x = ((m_X - 2) / 10)-1;
    int y = (m_Y - 6) / 2;

    return std::pair<int, int>(x, y);
}


std::string CTable::GetReadCoord(std::pair<int, int> self) {
    char c = self.first + 'A';
    std::string coord;
    coord.push_back(c);
    coord += std::to_string(self.second + 1);
    return coord;
}
/*bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetFakeCoordinates(window);

    if(content.empty()) {
        m_Array.at(coord.second).at(coord.first) = new CString("");
    }

    if(content.at(0) == '=') {
        if(isdigit(content.at(1))) {
            m_Array.at(coord.second).at(coord.first) = new COperation(content);
            return true;
        }

        m_Array.at(coord.second).at(coord.first) = new CFunction(content);

    } else {
        char* check;
        std::strtod(content.c_str(), &check);
        std::string s = std::string(check);
        if(s.empty()) {
            m_Array.at(coord.second).at(coord.first) = new CNumber(content);
            return true;
        }

        m_Array.at(coord.second).at(coord.first) = new CString(content);
    }

    //m_Array.at(coord.first).push_back(content);

    return true;
}*/

void CTable::UpdateCell(std::pair<int, int> parentCoord) {
    //std::pair<int, int> coord = GetFakeCoordinates(window);

    auto parent = m_Array[parentCoord.second][parentCoord.first];

    if(parent->InCycle())
        return;

    auto children = parent->GetChildren();

    for (const auto & i : children) {
    //for (int i = 0; i < children.size(); ++i) {


        auto childCoord = GetFakeCoordinates(i);
        auto child = m_Array[childCoord.second][childCoord.first];
        /*if(parent->InCycle()) {
            child->CycleSwitch();
            continue;
        } else*/
            child->Update(parent->GetOutput());

        if(child->HasChildren()) {
            UpdateCell(childCoord);
        }
    }

}

bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetFakeCoordinates(window);
    //auto currCell = m_Array[coord.second][coord.first];
    char* check;
    //todo rozdelit na funkce, tahle funkce bude jenom parsovat
    if(content.empty()) {
        //todo jeho childi ?
        m_Array[coord.second][coord.first] = new CString("");
        return true;
    }

    auto children = m_Array[coord.second][coord.first]->GetChildren();

    if(!children.empty())
        mvprintw(1, 170, "HAS CHILDREN");
    else
        mvprintw(1, 170, "NO  CHILDREN");

    if(content.at(0) == '=' && content.find(':') != std::string::npos) {
        auto start = content.find('(')+1;
        auto end = content.find(':');
        std::string startCoordS = content.substr(start, end - start);
        start = content.find(':')+1;
        end = content.find(')');
        std::string endCoordS = content.substr(start, end - start);

        mvprintw(1, 190, "%s %s", startCoordS.c_str(), endCoordS.c_str());

        auto startCoord = GetFakeCoordinates(startCoordS);
        auto endCoord = GetFakeCoordinates(endCoordS);

        std::vector<std::string> cells;
        for (int i = startCoord.second; i <= endCoord.second; ++i) {
            for (int j = startCoord.first; j <= endCoord.first; ++j) {
                cells.push_back(m_Array[i][j]->GetOutput());
            }
        }

        mvprintw(0, 190, "cells: %d", cells.size());

        delete(m_Array[coord.second][coord.first]);
        //m_Array[coord.second][coord.first] = new CString(content);
        m_Array[coord.second][coord.first] = new CFunction(content, cells);
        return true;

    }


    if(content.at(0) == '=') { //is Func or Operation
        if(isdigit(content.at(1))) {
            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new COperation(content);

        } else {
            auto start = content.find('(')+1;
            auto end = content.find(')');
            std::string argument = content.substr(start, end - start);
        mvprintw(0, 110, "value: %s", argument.c_str());
            if(IsNumber(argument)) {
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CFunction(content);
            } else {
                auto parentCoord = GetFakeCoordinates(argument);
                int xParentCoord = parentCoord.first;
                int yParentCoord = parentCoord.second;

                if(GetReadCoord(coord) == GetReadCoord(parentCoord)) {
                    delete(m_Array[coord.second][coord.first]);
                    m_Array[coord.second][coord.first] = new CString(content);
                    m_Array[coord.second][coord.first]->CycleSwitch();
                    return true;
                }

        mvprintw(0, 120, "ss: %d, %d", yParentCoord, xParentCoord);
        mvprintw(0, 130, "co input: %s", (m_Array[yParentCoord][xParentCoord]->GetOutput()).c_str());
        mvprintw(0, 150, "GetReadCoord: %s", GetReadCoord(coord).c_str());

                m_Array[yParentCoord][xParentCoord]->AddChild(GetReadCoord(coord)); //pridam parentovy sebe jako child
                auto currCellParents = m_Array[coord.second][coord.first]->GetParents(); //svoje rodice

                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CFunction(content, m_Array[yParentCoord][xParentCoord]);

                currCellParents.insert(GetReadCoord(coord));

                auto parentCellParents = m_Array[yParentCoord][xParentCoord]->GetParents();
                if(m_Array[yParentCoord][xParentCoord]->HasParents()) {
                    for(const auto& i: parentCellParents) {
                        if(currCellParents.find(i) != currCellParents.end() && !currCellParents.empty()) {
                            mvprintw(1, 120, "ERROR0");
                            m_Array[coord.second][coord.first]->CycleSwitch();
                            //return true;
                        }
                        m_Array[coord.second][coord.first]->AddParent(i);
                        //mvprintw(1, 180, "parent cp: %s", GetReadCoord(parentCoord).c_str());
                    }
                }
                //todo pokud uz tam je tak pomoci funkce prepnout na error a vypsat ho dokud to nespravi

                if(currCellParents.find(GetReadCoord(parentCoord)) != currCellParents.end()) {
                    m_Array[coord.second][coord.first]->CycleSwitch();
                    mvprintw(1, 130, "ERROR");
                }


                m_Array[coord.second][coord.first]->AddParent(GetReadCoord(parentCoord));
                //mvprintw(1, 140, "parent: %s", GetReadCoord(parentCoord).c_str());
            }
        }

    } else {

        std::strtod(content.c_str(), &check);
        std::string s = std::string(check);
        if(s.empty()) { //is number

            /*if(m_Array[coord.second][coord.first]->HasChildren()) {
                auto children = m_Array[coord.second][coord.first]->GetChildren();
                delete(m_Array[coord.second][coord.first]);
                //m_Array[coord.second][coord.first] = new CNumber(content, coord.first, coord.second);
                m_Array[coord.second][coord.first] = new CNumber(content);

                for(const auto &i: children) {
                    m_Array[coord.second][coord.first]->AddChild(i);
                }
                UpdateCell(coord);
            } else {
                delete(m_Array[coord.second][coord.first]);
                //m_Array[coord.second][coord.first] = new CNumber(content, coord.first, coord.second);
                m_Array[coord.second][coord.first] = new CNumber(content);
            }*/

            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new CNumber(content);

        } else {
            //is string
            /*if(m_Array[coord.second][coord.first]->HasChildren()) {
                auto children = m_Array[coord.second][coord.first]->GetChildren();
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CString(content);
                for(const auto &i: children) {
                    m_Array[coord.second][coord.first]->AddChild(i);
                }
                UpdateCell(coord);
            } else {
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CString(content);
            }*/

            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new CString(content);

        }
    }

    if(!children.empty()) {
        for(const auto &i: children) {
            m_Array[coord.second][coord.first]->AddChild(i);
        }
        UpdateCell(coord);
    }

    return true;
}

void CTable::PrintArr() {
    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {

            for (const auto& k : m_Array[i][j]->GetParents()) {
                std::cout << k << "|" ;
            }

            std::cout << (m_Array[i][j]->GetOutput()).c_str() << ", ";
        }
        std::cout << std::endl;
    }
}

void CTable::DisplayContent() {
    int k = 0, l = 0;
    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        k = 0;
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {
            mvprintw(6 + l, 3 + k, "|         ");
            mvprintw(6 + l, 4 + k, (m_Array[i][j]->GetOutput()).c_str());
            k += 10;
        }
        l += 2;
    }
}

std::string CTable::GetOutput(int y, int x) const{
    return m_Array[y][x]->GetOutput();
}

std::string CTable::GetInput(int y, int x) const{
    return m_Array[y][x]->GetInput();
}

bool CTable::IsNumber(const std::string& s) {
    char* check;
    std::strtod(s.c_str(), &check);
    std::string c = std::string(check);

    return c.empty();
}

std::pair<int, int> CTable::GetFakeCoordinates(std::string link) {
    char * check;
    int xCoord = link.at(0) - 'A';
    link.erase(0, 1);
    int yCoord = std::strtol(link.c_str(), &check, 10) - 1;
    return std::pair<int, int>(xCoord, yCoord);
}

bool CTable::SaveToFile(const std::string& destFileName) {
    std::fstream fileOut;
    fileOut.open(destFileName, std::ios::out);

    if(!fileOut.is_open() || fileOut.fail()) {
        mvprintw(1, 180, "Cant open output file");
        fileOut.close();
        return false;
    }

    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {
            fileOut.write(m_Array[i][j]->GetOutput().c_str(), m_Array[i][j]->GetOutput().size());
            fileOut << ",";

        }
        fileOut << std::endl;
    }

    fileOut.close();

    return true;
}

bool CTable::ReadFromFile(const std::string &srcFileName) {
    std::fstream fileIn;
    std::string line, delimiter = ",";
    fileIn.open(srcFileName, std::ios::in);

    if(!fileIn.good()) {
        fileIn.close();
        return false;
    }
    int j = 0, i = 0;

    while ( getline (fileIn, line) ) {
        auto start = 0U;
        auto end = line.find(delimiter);

        while (end != std::string::npos) {
            delete(m_Array[i][j]);
            m_Array[i][j] = new CString(line.substr(start, end - start));
            start = end + delimiter.length();
            end = line.find(delimiter, start);
            j++;
        }
        i++;
    }

    fileIn.close();
    return true;
}











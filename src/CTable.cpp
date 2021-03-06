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
    /*mvprintw(2, 20, "Max: %d %d", this->m_YMax, this->m_XMax);
    mvprintw(2, 30, "Max Fake: %d %d", (m_YMax - 5) / 2, (m_XMax - 4) / 10);*/

    DrawHorizontalLines(this->m_YMax, this->m_XMax);
    DrawCoordinates(this->m_YMax, this->m_XMax);
    DrawVerticalLines(this->m_YMax, this->m_XMax);

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

void CTable::UpdateCell(std::pair<int, int> parentCoord) {
    //std::pair<int, int> coord = GetFakeCoordinates(window);

    auto parent = m_Array[parentCoord.second][parentCoord.first];

    auto children = parent->GetChildren();

    for (const auto & i : children) {
    //for (int i = 0; i < children.size(); ++i) {


        auto childCoord = GetFakeCoordinates(i);
        auto child = m_Array[childCoord.second][childCoord.first];
        if(parent->InCycle()) {
            child->CycleSwitch();
            continue;
        } else {
            child->CycleFalse();
            child->Update(parent->GetOutput());
        }


        if(child->HasChildren()) {
            UpdateCell(childCoord);
        }
    }

}

bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetFakeCoordinates(window);
    //auto currCell = m_Array[coord.second][coord.first];
    char* check;
    if(content.empty()) {
        m_Array[coord.second][coord.first] = new CString("");
        return true;
    }

    auto children = m_Array[coord.second][coord.first]->GetChildren();

    /*if(!children.empty())
        mvprintw(1, 170, "HAS CHILDREN");
    else
        mvprintw(1, 170, "NO  CHILDREN");*/

    if(content.at(0) == '=' && content.find(':') != std::string::npos) {
        auto start = content.find('(')+1;
        auto end = content.find(':');
        std::string startCoordS = content.substr(start, end - start);
        start = content.find(':')+1;
        end = content.find(')');
        std::string endCoordS = content.substr(start, end - start);

        //mvprintw(1, 190, "%s %s", startCoordS.c_str(), endCoordS.c_str());

        auto startCoord = GetFakeCoordinates(startCoordS);
        auto endCoord = GetFakeCoordinates(endCoordS);

        std::vector<std::string> cells;
        for (int i = startCoord.second; i <= endCoord.second; ++i) {
            for (int j = startCoord.first; j <= endCoord.first; ++j) {
                cells.push_back(m_Array[i][j]->GetOutput());
            }
        }

        //mvprintw(0, 190, "cells: %d", cells.size());

        delete(m_Array[coord.second][coord.first]);
        //m_Array[coord.second][coord.first] = new CString(content);
        m_Array[coord.second][coord.first] = new CFunction(content, cells);
        return true;
    }


    if(content.at(0) == '=') { //is Func or Operation
        if(isdigit(content.at(1))) { //is Operation
            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new COperation(content);

        } else { //is Function
            auto start = content.find('(')+1;
            auto end = content.find(')');
            if(start == std::string::npos || end == std::string::npos) {
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CString(content);
            }

            std::string argument = content.substr(start, end - start);
        //mvprintw(0, 110, "value: %s", argument.c_str());
            if(IsNumber(argument)) {
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CFunction(content);
            } else { //function with link
                auto parentCoord = GetFakeCoordinates(argument);
                int xParentCoord = parentCoord.first;
                int yParentCoord = parentCoord.second;

                if(xParentCoord < 0 || yParentCoord < 0) { //self linking
                    delete(m_Array[coord.second][coord.first]);
                    m_Array[coord.second][coord.first] = new CString(content);
                    m_Array[coord.second][coord.first]->ErrorTrue();
                    return true;
                }

                if(GetReadCoord(coord) == GetReadCoord(parentCoord) || xParentCoord < 0 || yParentCoord < 0) { //self linking
                    delete(m_Array[coord.second][coord.first]);
                    m_Array[coord.second][coord.first] = new CString(content);
                    m_Array[coord.second][coord.first]->CycleSwitch();
                    return true;
                }

        /*mvprintw(0, 120, "ss: %d, %d", yParentCoord, xParentCoord);
        mvprintw(0, 130, "co input: %s", (m_Array[yParentCoord][xParentCoord]->GetOutput()).c_str());
        mvprintw(0, 150, "GetReadCoord: %s", GetReadCoord(coord).c_str());*/

                m_Array[yParentCoord][xParentCoord]->AddChild(GetReadCoord(coord)); //add itself to his parent as child
                auto currCellParents = m_Array[coord.second][coord.first]->GetParents(); //gets his parents

                delete(m_Array[coord.second][coord.first]); //delete the original CString
                m_Array[coord.second][coord.first] = new CFunction(content, m_Array[yParentCoord][xParentCoord]);

                //currCellParents.insert(GetReadCoord(coord));
                if(currCellParents.find(GetReadCoord(parentCoord)) != currCellParents.end()) {
                    m_Array[coord.second][coord.first]->CycleSwitch();
                    //mvprintw(1, 130, "ERROR");
                } else
                    m_Array[coord.second][coord.first]->AddParent(GetReadCoord(parentCoord));


                auto parentCellParents = m_Array[yParentCoord][xParentCoord]->GetParents(); //parents of the parent cell A1
                if(m_Array[yParentCoord][xParentCoord]->HasParents()) {
                    for(const auto& i: parentCellParents) {
                        if(currCellParents.find(i) != currCellParents.end() && !currCellParents.empty()) {
                            //mvprintw(1, 120, "ERROR0");
                            m_Array[coord.second][coord.first]->CycleSwitch();
                            //return true;
                        }
                        if(i == GetReadCoord(coord))
                            m_Array[coord.second][coord.first]->CycleSwitch();

                        //mvprintw(1, 140, "f%s|%s", i.c_str(), GetReadCoord(coord).c_str());

                        m_Array[coord.second][coord.first]->AddParent(i);
                        //mvprintw(1, 180, "parent cp: %s", GetReadCoord(parentCoord).c_str());
                    }
                }



                /*mvprintw(1, 140, "f%d,%d|%d,%d", coord.second, coord.first, parentCoord.second, parentCoord.first);
                if(parentCoord == coord) {
                    m_Array[coord.second][coord.first]->CycleSwitch();
                }*/
            }
        }

    } else {

        std::strtod(content.c_str(), &check);
        std::string s = std::string(check);
        if(s.empty()) { //is number

            if(m_Array[coord.second][coord.first]->HasParents()) {
                auto parents = m_Array[coord.second][coord.first]->GetParents();
                for(const auto& i: parents) {
                    auto parentCoord = GetFakeCoordinates(i);
                    m_Array[parentCoord.second][parentCoord.first]->DeleteChild(GetReadCoord(coord));
                }
            }

            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new CNumber(content);

        } else {
            //is string

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

            /*for (const auto& k : m_Array[i][j]->GetParents()) {
                std::cout << k << "|" ;
            }*/

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
    std::string s = std::string(check);
    if(!s.empty())
        std::pair<int, int>(-1, -1);
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
        mvprintw(1, 180, "Cant open input file");
        return false;
    }
    int j = 0, i = 0;

    while ( getline (fileIn, line) ) {
        if(i == (m_YMax - 5) / 2)
            break;
        auto start = 0U;
        auto end = line.find(delimiter);
        j = 0;
        while (end != std::string::npos) {
            if(j == (m_XMax - 4) / 10)
                break;
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











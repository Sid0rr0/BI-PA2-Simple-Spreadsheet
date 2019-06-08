//
// Created by hung on 2.6.19.
//

#include "CTable.h"
#include "CCursor.h"
#include <ncurses.h>
#include <iostream>
#include "CNumber.h"
#include "CString.h"
#include "CFunction.h"
#include "COperation.h"
#include <cstdlib>


CTable::CTable(){
    /*initscr();
    cbreak();*/

    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_CYAN, COLOR_WHITE);
    }

    getmaxyx(stdscr, this->m_YMax, this->m_XMax);
    //getmaxyx(stdscr, m_MaxCoor.first, m_MaxCoor.second);
    //printw("%d %d", this->m_YMax, this->m_XMax);

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

    //getch();
    //endwin();
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

/*void CTable::DrawCoordinates(std::pair<int, int> mMaxCoor) {
    int c = 1;
    m_CurrCoor.second = 1, m_CurrCoor.first = 6;
    move(m_CurrCoor.first , m_CurrCoor.second);
}*/

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
    //if the cell that is updated has children update is aswell

    auto children = parent->GetChildren();

    for (const auto & i : children) {
    //for (int i = 0; i < children.size(); ++i) {
        auto childCoord = GetFakeCoordinates(i);
        auto child = m_Array[childCoord.second][childCoord.first];
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
        return true;
    }

    if(content.at(0) == '=') { //is Func or Operation
        if(isdigit(content.at(1))) {
            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new COperation(content);

        } else {
            delete(m_Array[coord.second][coord.first]);

            auto start = content.find('(')+1;
            auto end = content.find(')');
            std::string argument = content.substr(start, end - start);
        mvprintw(0, 110, "value: %s", argument.c_str());
            if(IsNumber(argument))
                m_Array[coord.second][coord.first] = new CFunction(content);
            else {
                /*int xParentCoord = argument.at(0) - 'A';
                argument.erase(0, 1);
                int yParentCoord = std::strtol(argument.c_str(), &check, 10) - 1;*/
                auto parentCoord = GetFakeCoordinates(argument);
                int xParentCoord = parentCoord.first;
                int yParentCoord = parentCoord.second;

        mvprintw(0, 120, "ss: %d, %d", yParentCoord, xParentCoord);
        mvprintw(0, 130, "co input: %s", (m_Array[yParentCoord][xParentCoord]->GetOutput()).c_str());
                /*std::string newString = content;
                newString.replace(start, end, std::string(m_Array[yParentCoord][xParentCoord]->GetOutput()));
                newString += ")";
        mvprintw(0, 150, "lfsf: %s", newString.c_str());
                m_Array[coord.second][coord.first] = new CFunction(newString);*/

                mvprintw(0, 150, "GetReadCoord: %s", GetReadCoord(coord).c_str());
                m_Array[yParentCoord][xParentCoord]->AddChild(GetReadCoord(coord)); //pridam parentovy child
                m_Array[coord.second][coord.first] = new CFunction(content, m_Array[yParentCoord][xParentCoord]); //vytvorim novou fci a predam *
                // na rodice

                auto parentCellParents = m_Array[yParentCoord][xParentCoord]->GetParents();
                if(m_Array[yParentCoord][xParentCoord]->HasParents()) {
                    for(const auto& i: parentCellParents) {
                        if(m_Array[coord.second][coord.first]->GetParents().find(i) != m_Array[coord.second][coord.first]->GetParents().end()) {
                            mvprintw(1, 120, "ERROR0");
                            m_Array[coord.second][coord.first]->CycleSwitch();
                        }

                        m_Array[coord.second][coord.first]->AddParent(i);
                        mvprintw(1, 180, "parent cp: %s", GetReadCoord(parentCoord).c_str());
                    }
                }
                //todo pokud uz tam je tak pomoci funkce prepnout na error a vypsat ho dokud to nespravi
                auto currCellParents = m_Array[coord.second][coord.first]->GetParents();
                if(currCellParents.find(GetReadCoord(parentCoord)) != currCellParents.end())
                    mvprintw(1, 120, "ERROR");

                m_Array[coord.second][coord.first]->AddParent(GetReadCoord(parentCoord));
                mvprintw(1, 140, "parent: %s", GetReadCoord(parentCoord).c_str());
            }
        }

    } else {

        std::strtod(content.c_str(), &check);
        std::string s = std::string(check);
        if(s.empty()) { //is number

            if(m_Array[coord.second][coord.first]->HasChildren()) {
                auto children = m_Array[coord.second][coord.first]->GetChildren();
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CNumber(content, coord.first, coord.second);

                for(const auto &i: children) {
                    m_Array[coord.second][coord.first]->AddChild(i);
                }
                UpdateCell(coord);
            } else {
                delete(m_Array[coord.second][coord.first]);
                m_Array[coord.second][coord.first] = new CNumber(content, coord.first, coord.second);
            }

        } else {
            //is string
            if(m_Array[coord.second][coord.first]->HasChildren()) {
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
            }

        }
    }

    return true;
}

void CTable::PrintArr() {
    /*for (auto & i : m_Array) {
        for (const auto & j : i) {
            //std::cout << j << ", ";
            (j->GetOutput()).c_str();
        }
        std::cout << std::endl;
    }*/

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
            mvprintw(6 + l, 4 + k, "         ");
            mvprintw(6 + l, 4 + k, (m_Array[i][j]->GetOutput()).c_str());
            k += 10;
        }
        l += 2;
    }
}

std::string CTable::GetOutput(int y, int x) {
    return m_Array[y][x]->GetOutput();
}

bool CTable::IsNumber(const std::string& s) {
    char* check;
    std::strtod(s.c_str(), &check);
    std::string c = std::string(check);

    return c.empty();
}

std::pair<int, int> CTable::GetFakeCoordinates(std::string link) {
    char * check;
    int xCoor = link.at(0) - 'A';
    link.erase(0, 1);
    int yCoor = std::strtol(link.c_str(), &check, 10) - 1;
    return std::pair<int, int>(xCoor, yCoor);
}









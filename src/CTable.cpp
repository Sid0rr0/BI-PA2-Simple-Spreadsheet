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

std::pair<int, int> CTable::GetCoordinates(WINDOW * window) {
    getyx(window, m_Y, m_X);
    int x = ((m_X - 2) / 10)-1;
    int y = (m_Y - 6) / 2;

    return std::pair<int, int>(x, y);
}

/*bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetCoordinates(window);

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

bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetCoordinates(window);

    if(content.empty()) {
        return true;
    }

    if(content.at(0) == '=') {
        if(isdigit(content.at(1))) {
            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new COperation(content);
            return true;
        }

        delete(m_Array[coord.second][coord.first]);
        m_Array[coord.second][coord.first] = new CFunction(content);

    } else {
        char* check;
        std::strtod(content.c_str(), &check);
        std::string s = std::string(check);
        if(s.empty()) {
            delete(m_Array[coord.second][coord.first]);
            m_Array[coord.second][coord.first] = new CNumber(content);
            return true;
        }

        delete(m_Array[coord.second][coord.first]);
        m_Array[coord.second][coord.first] = new CString(content);
    }

    //m_Array.at(coord.first).push_back(content);

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
            std::cout << (m_Array[i][j]->GetOutput()).c_str() << ", ";
        }
        std::cout << std::endl;
    }
}

void CTable::DisplayContent() {
    int k = 0, l = 0;
    /*for (auto & i : m_Array) {
        k = 0;
        for (auto & j : i) {
            //mvprintw(6 + l, 4 + k, j.c_str());
            //mvprintw(6 + l, 4 + k, (j->GetOutput()).c_str());
            //mvprintw(6 + l, 4 + k, (j->GetOutput()).c_str());

            k += 10;
        }
        l += 2;
    }*/

    for (int i = 0; i < (m_YMax - 5) / 2; ++i) {
        k = 0;
        for (int j = 0; j < (m_XMax - 4) / 10; ++j) {
            mvprintw(6 + l, 4 + k, (m_Array[i][j]->GetOutput()).c_str());
            k += 10;
        }
        l += 2;
    }
}



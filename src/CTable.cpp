//
// Created by hung on 2.6.19.
//

#include "CTable.h"
#include "CCursor.h"
#include <ncurses.h>
#include <iostream>

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

    m_Array.resize((m_YMax - 5) / 2);
    //mvprintw(0, 90, "m_Array size: %d", m_Array.size());
    for (auto & i : m_Array)
        i.resize((m_XMax - 4) / 10);

    //getch();
    //endwin();
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

bool CTable::SaveCell(WINDOW * window, const std::string& content) {

    std::pair<int, int> coord = GetCoordinates(window);

    //m_Array.at(coord.first).push_back(content);
    m_Array.at(coord.second).at(coord.first) = content;

    return true;
}

void CTable::PrintArr() {
    for (auto & i : m_Array) {
        for (const auto & j : i) {
            std::cout << j << ", ";
        }
        std::cout << std::endl;
    }
}

void CTable::DisplayContent() {
    int k = 0, l = 0;
    for (auto & i : m_Array) {
        k = 0;
        for (auto & j : i) {
            mvprintw(6 + l, 4 + k, j.c_str());
            k += 10;
        }
        l += 2;
    }
}

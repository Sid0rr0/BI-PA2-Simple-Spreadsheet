//
// Created by hung on 3.6.19.
//

#include "CCursor.h"
#include <ncurses.h>

CCursor::CCursor(char mCursor, WINDOW *mCurrWin) : m_Cursor(mCursor), m_CurrWin(mCurrWin) {
    getmaxyx(m_CurrWin, m_YMax, m_XMax);
    keypad(m_CurrWin, true);
    m_XLoc = 11;
    m_YLoc = 6;
    move(m_YLoc, m_XLoc);
}

void CCursor::MoveRight() {
    m_XLoc += 10;
    if(m_XLoc > m_XMax)
        m_XLoc = 11;
}

void CCursor::MoveLeft() {
    m_XLoc -= 10;
    if(m_XLoc < 3)
        m_XLoc = m_XMax - (m_XMax % 10) + 1;
}

void CCursor::MoveDown() {
    m_YLoc += 2;
    if(m_YLoc > m_YMax)
        m_YLoc = 6;
}

void CCursor::MoveUp() {
    m_YLoc -= 2;
    if(m_YLoc < 6)
        m_YLoc = m_YMax - (m_YMax % 2) + 1;
}

int CCursor::Move() {

    int pressed = wgetch(m_CurrWin);

    switch (pressed) {
        case KEY_UP:
            MoveUp();
            break;
        case KEY_DOWN:
            MoveDown();
            break;
        case KEY_LEFT:
            MoveLeft();
            break;
        case KEY_RIGHT:
            MoveRight();
            break;
        default:
            break;
    }

    return pressed;
}

void CCursor::Display() {
    mvwaddch(m_CurrWin, m_YLoc, m_XLoc, m_Cursor);
}

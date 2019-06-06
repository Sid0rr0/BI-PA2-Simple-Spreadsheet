//
// Created by hung on 3.6.19.
//

#include "CCursor.h"
#include <ncurses.h>

CCursor::CCursor(char mCursor, WINDOW *mCurrWin) : m_Cursor(mCursor), m_CurrWin(mCurrWin) {
    getmaxyx(m_CurrWin, m_YMax, m_XMax);
    keypad(m_CurrWin, true);
    m_X = 12;
    m_Y = 6;
    move(m_Y, m_X);
    m_X = 11;
}

void CCursor::MoveRight() {
    m_X += 10;
    if(m_X > m_XMax)
        m_X = 11;
}

void CCursor::MoveLeft() {
    m_X -= 10;
    if(m_X < 3)
        m_X = m_XMax - (m_XMax % 10) + 1;
}

void CCursor::MoveDown() {
    m_Y += 2;
    if(m_Y > m_YMax)
        m_Y = 6;
}

void CCursor::MoveUp() {
    m_Y -= 2;
    if(m_Y < 6)
        m_Y = m_YMax - (m_YMax % 2);
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
/*        case KEY_ENTER:
            Input();
            break;*/
        default:
            break;
    }

    return pressed;
}

void CCursor::Display() {
    mvwaddch(m_CurrWin, m_Y, m_X, m_Cursor);
}




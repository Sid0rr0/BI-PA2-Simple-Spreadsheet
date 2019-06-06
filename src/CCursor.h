//
// Created by hung on 3.6.19.
//

#ifndef LETHANHH_CCURSOR_H
#define LETHANHH_CCURSOR_H


#include <curses.h>
#include <ncurses.h>
#include <utility>

class CCursor {

public:
    CCursor(char mCursor, WINDOW *mCurrWin);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    int Move();
    void Display();
    //void Input();


private:
    int m_X, m_Y;
    int m_XMax, m_YMax;
    char m_Cursor;
    WINDOW * m_CurrWin;
};


#endif //LETHANHH_CCURSOR_H

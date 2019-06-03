//
// Created by hung on 3.6.19.
//

#ifndef LETHANHH_CCURSOR_H
#define LETHANHH_CCURSOR_H


#include <curses.h>
#include <ncurses.h>

class CCursor {

public:
    CCursor(char mCursor, WINDOW *mCurrWin);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    int Move();
    void Display();

private:
    int m_XLoc, m_YLoc;
    int m_XMax, m_YMax;
    char m_Cursor;
    WINDOW * m_CurrWin;
};


#endif //LETHANHH_CCURSOR_H

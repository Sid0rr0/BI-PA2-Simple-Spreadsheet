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

    /**
     * Moves the cursor up
     */
    void MoveUp();

    /**
     * Moves the cursor down
     */
    void MoveDown();

    /**
     * Moves the cursor left
     */
    void MoveLeft();

    /**
     * Moves the cursor right
     */
    void MoveRight();

    /**
     * Reads the user input and moves the cursor accordingly
     *
     * @return integer value of pressed key
     */
    int Move();

    /**
     * Prints the cursor to the terminal
     */
    void Display();

private:
    int m_X, m_Y;
    int m_XMax, m_YMax;
    char m_Cursor;
    WINDOW * m_CurrWin;
};


#endif //LETHANHH_CCURSOR_H

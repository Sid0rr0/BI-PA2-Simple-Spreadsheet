//
// Created by hung on 2.6.19.
//

#ifndef LETHANHH_CTABLE_H
#define LETHANHH_CTABLE_H

#include <ncurses.h>

class CTable {
public:
    CTable();

    void DrawCoordinates(int yMax, int xMax);
    void DrawHorizontalLines(int yMax, int xMax);
    void DrawVerticalLines(int yMax, int xMax);

private:
    int m_YMax{};
    int m_XMax{};
    int m_Y{};
    int m_X{};
};


#endif //LETHANHH_CTABLE_H

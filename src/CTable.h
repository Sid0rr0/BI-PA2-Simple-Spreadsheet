//
// Created by hung on 2.6.19.
//

#ifndef LETHANHH_CTABLE_H
#define LETHANHH_CTABLE_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "CCell.h"

class CTable {
public:
    CTable();

    virtual ~CTable();

    void DrawCoordinates(int yMax, int xMax);
    void DrawHorizontalLines(int yMax, int xMax);
    void DrawVerticalLines(int yMax, int xMax);

    /*void DrawCoordinates(std::pair<int, int> mMaxCoor);
    void DrawHorizontalLines(std::pair<int, int> mMaxCoor);
    void DrawVerticalLines(std::pair<int, int> mMaxCoor);*/

    std::pair<int, int> GetFakeCoordinates(WINDOW *window);
    std::pair<int, int> GetFakeCoordinates(std::string link);
    std::string GetReadCoord(std::pair<int, int> self);
    bool SaveCell(WINDOW * window, const std::string& content);
    void UpdateCell(WINDOW *window, const std::string& content, std::pair<int, int> parentCoord);
    void PrintArr();
    void DisplayContent();
    std::string GetOutput(int y, int x);

    bool IsNumber(const std::string& s);
private:
    int m_YMax{}, m_XMax{};
    int m_Y{}, m_X{};
    /*std::pair<int, int> m_CurrCoor;
    std::pair<int, int> m_MaxCoor;*/
    //std::vector<std::vector<CCell*>> m_Array;
    CCell*** m_Array;
};


#endif //LETHANHH_CTABLE_H

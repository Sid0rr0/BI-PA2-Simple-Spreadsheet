/**
 * Class for rendering the table and the cell content
 */

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

    /**
     * Renders the coordinate numbers and letters
     * @param yMax number of maximum lines of terminal
     * @param xMax number of maximum columns of terminal
     */
    void DrawCoordinates(int yMax, int xMax);

    /**
     * Renders the horizontal lines
     * @param yMax number of maximum lines of terminal
     * @param xMax number of maximum columns of terminal
     */
    void DrawHorizontalLines(int yMax, int xMax);

    /**
     * Renders the vertical lines
     * @param yMax number of maximum lines of terminal
     * @param xMax number of maximum columns of terminal
     */
    void DrawVerticalLines(int yMax, int xMax);

    /**
     * Returns pair of coordinates of current cell position
     * @param window pointer to the window where the cell is
     * @return pair of coordinates in the 2D array
     */
    std::pair<int, int> GetFakeCoordinates(WINDOW *window);

    /**
     * Returns pair of coordinates of parent cell
     * @param link coordinates of the parent cell
     * @return pair of coordinates in the 2D array
     */
    std::pair<int, int> GetFakeCoordinates(std::string link);

    /**
     * Returns letter-number coordinate of a cell from 2D array
     * @param self pair of coordinates in the 2D array
     * @return letter-number coordinates string
     */
    std::string GetReadCoord(std::pair<int, int> self);

    /**
     * Saves the cell into the 2D array
     * @param window pointer to the window from which to save
     * @param content input string
     * @return true if successfully saved
     */
    bool SaveCell(WINDOW * window, const std::string& content);

    /**
     * Update output of a cell if parent cell was changed
     * @param parentCoord coordinates of parent cell
     */
    void UpdateCell(std::pair<int, int> parentCoord);

    /**
     * Prints the whole 2D array to the terminal
     */
    void PrintArr();

    /**
     * Renders the whole 2D array to the terminal
     */
    void DisplayContent();

    /**
     * Get specific cell contents
     * @param y coordinate
     * @param x coordinate
     * @return output string
     */
    std::string GetOutput(int y, int x) const;

    /**
     * Get cell input
     * @param y coordinate
     * @param x coordinate
     * @return input string
     */
    std::string GetInput(int y, int x) const;

    /**
     * Checks if the whole string can transferred into double
     * @param s string is checked
     * @return true if possible
     */
    bool IsNumber(const std::string& s);

    bool SaveToFile(const std::string& destFileName);

    bool ReadFromFile(const std::string& srcFileName);

private:
    int m_YMax{}, m_XMax{};
    int m_Y{}, m_X{};
    CCell*** m_Array;
};


#endif //LETHANHH_CTABLE_H

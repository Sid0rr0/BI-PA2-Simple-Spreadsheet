/**
 * Parent class
 */

#ifndef SEMESTRAL_CCELL_H
#define SEMESTRAL_CCELL_H


#include <ostream>

class CCell {
public:
    enum CType {FUNC, NUM, STR};

    /**
     * Constructor
     */
    CCell();

    /**
     * Destructor
     */
    virtual ~CCell();

    /**
     * Prints the value of the cell
     *
     * @param os output stream
     */
    virtual void Print (std::ostream & os) const = 0;

    /**
     * Overloaded output operator
     *
     * @param os output stream
     * @param cell CCell that will be printed
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const CCell &cell);

    //virtual bool IsNumber () const = 0;

    /**
     * Returns type of cell
     *
     * @return type of cell
     */
    virtual CType CellType () const = 0;

private:

};


#endif //SEMESTRAL_CCELL_H

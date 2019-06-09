/**
 * Parent class
 */

#ifndef SEMESTRAL_CCELL_H
#define SEMESTRAL_CCELL_H


#include <ostream>
#include <vector>
#include <set>

class CCell {
public:
    /**
     * Enum of various cell types
     */
    enum CType {FUNC, NUM, STR, OP};

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

     * @param os output stream
     * @param cell CCell that will be printed
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const CCell &cell);

    /**
     * Returns type of cell
     *
     * @return type of cell
     */
    virtual CType CellType () const = 0;

    /**
     * Returns string that will be printed to console
     * @return std::string output
     */
    virtual std::string GetOutput () const = 0;

    /**
     * Returns the input string
     * @return std::string output
     */
    virtual std::string GetInput () const = 0;

    /**
     * Adds coordinates of the child cell to vector
     *
     * @param child string coordinate of the child cell
     */
    virtual void AddChild(const std::string& child) = 0;

    /**
     * Checks if cell has children
     *
     * @return true if has one or more children
     */
    virtual bool HasChildren() = 0;

    /**
     * Return vector of coordinates of the children
     *
     * @return vector of strings of children
     */
    virtual std::vector<std::string> GetChildren() = 0;

    /**
     * Updates the cell if parent cell was altered
     *
     * @param content value that the parent cell was changed to
     */
    virtual void Update(const std::string& content) = 0;

    virtual void AddParent(const std::string& parent) = 0;

    virtual bool HasParents() = 0;

    virtual std::set<std::string> GetParents() = 0;

    /**
     * Changes the cycle bool if there is error and otherwise
     */
    virtual void CycleSwitch() = 0;

    virtual bool InCycle() = 0;


private:
};


#endif //SEMESTRAL_CCELL_H

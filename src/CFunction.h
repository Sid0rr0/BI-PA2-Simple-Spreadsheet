//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CFUNCTION_H
#define SEMESTRAL_CFUNCTION_H


#include <ostream>
#include "CCell.h"
#include <string>

class CFunction : public CCell{
public:
    //enum m_Functions{SIN, COS, LOG, SQRT, ABS};

    /**
     * Constructor
     * @param mInput
     */
    explicit CFunction(std::string mInput);

    ~CFunction() override;

    /**
     * Prints the whole string
     * @param os
     */
    void Print(std::ostream & os) const override;

    /**
     * Prints the result of the function
     * @param os
     */
    void PrintResult(std::ostream &os) const;

    //bool IsNumber () const override;

    /**
     * Returns the type of the cell
     * @return CType FUNC
     */
    CType CellType() const override;

    /**
     * Parses the input string
     * @param input
     * @return bool
     */
    bool ParseInput(const std::string& input);

    /**
     * Computes the result of the function
     * @return
     */
    bool getResult();

    /**
     * Checks if the funtions is supported
     * @param func
     * @return bool
     */
    bool isSupportedFunction(const std::string &func) const;

    /**
     * Overloaded output operator
     * @param os
     * @param function
     * @return std::ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const CFunction &function);

private:
    std::string m_Input;
    std::string m_Name;
    double m_Value{};
    double m_Result{};
};


#endif //SEMESTRAL_CFUNCTION_H

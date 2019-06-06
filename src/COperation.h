//
// Created by hung on 28.5.19.
//

#ifndef LETHANHH_COPERATION_H
#define LETHANHH_COPERATION_H


#include <ostream>
#include "CCell.h"

class COperation : public CCell{

public:
    explicit COperation(std::string mInput);

    ~COperation() override;

    /**
     * Prints the whole string
     * @param os
     */
    void Print(std::ostream &os) const override;

    /**
     * Prints the result of the function
     * @param os
     */
    void PrintResult(std::ostream &os) const;

    /**
     * Returns the type of the cell
     * @return CType FUNC
     */
    CType CellType() const override;

    /**
     * Computes the result of the function
     * @return
     */
    bool getResult();

    /**
     * Parses the input string
     * @param input
     * @return bool
     */
    bool ParseInput(const std::string& input);

    /**
     * Overloaded output operator
     * @param os
     * @param function
     * @return std::ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const COperation &operation);


    std::string GetOutput() const override;

private:
    std::string m_Input;
    char m_Operator{};
    double m_OperandA{};
    double m_OperandB{};
    double m_Result{};
};


#endif //LETHANHH_COPERATION_H

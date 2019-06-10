/**
 * Class for handling binary operations
 */

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
    bool GetResult();

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

    std::string GetInput() const override;

    void AddChild(const std::string &child) override;

    void DeleteChild(const std::string &child) override;

    bool HasChildren() override;

    std::vector<std::string> GetChildren() override;

    /**
     * Updates both operands
     * @param content both operands separated by whitespace
     */
    void Update(const std::string &content) override;

    void AddParent(const std::string &parent) override;

    bool HasParents() override;

    std::set<std::string> GetParents() override;

    void CycleSwitch() override;

    void CycleFalse() override;

    bool InCycle() override;

    void DeleteParent(std::string parent) override;

    void ErrorTrue() override;

private:
    std::string m_Input;
    char m_Operator{};
    double m_OperandA{};
    double m_OperandB{};
    double m_Result{};
    std::vector<std::string> m_Children;
    std::set<std::string> m_Parents;
    bool m_Cycle;
    bool m_Error;
};


#endif //LETHANHH_COPERATION_H

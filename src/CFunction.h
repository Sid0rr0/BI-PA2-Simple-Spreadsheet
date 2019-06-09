//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CFUNCTION_H
#define SEMESTRAL_CFUNCTION_H


#include <ostream>
#include "CCell.h"
#include "CNumber.h"
#include <string>
#include <vector>
#include <set>

class CFunction : public CCell{
public:
    //enum m_Functions{SIN, COS, LOG, SQRT, ABS};

    /**
     * Constructor
     * @param mInput
     */
    explicit CFunction(std::string mInput);

    CFunction(std::string mInput, CCell* cell);

    CFunction(std::string mInput, std::vector<std::string>   cells);

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
    bool isSupportedFunction(const std::string &func);

    /**
     * Overloaded output operator
     * @param os
     * @param function
     * @return std::ostream
     */
    friend std::ostream &operator<<(std::ostream &os, const CFunction &function);

    std::string GetOutput() const override;

    std::string GetInput() const override;

    void AddChild(const std::string& child) override;

    void DeleteChild(const std::string &child) override;

    bool HasChildren() override;

    std::vector<std::string> GetChildren() override;

    void Update(const std::string &content) override;

    void AddParent(const std::string &parent) override;

    void DeleteParent(std::string parent) override;

    bool HasParents() override;

    std::set<std::string> GetParents() override;

    void CycleSwitch() override;

    void CycleFalse() override;

    bool InCycle() override;

    void ErrorTrue() override;


private:
    std::string m_Input;
    std::string m_Name;
    double m_Value{};
    double m_Result{};
    std::vector<std::string> m_Children;
    std::set<std::string> m_Parents;
    std::vector<std::string> m_Cells;
    CCell * cell{};
    bool m_Cycle;
    bool m_Error;
};


#endif //SEMESTRAL_CFUNCTION_H

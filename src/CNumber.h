/**
 * Class for handling number cells
 */

#ifndef SEMESTRAL_CNUMBER_H
#define SEMESTRAL_CNUMBER_H

#include <ostream>
#include "CCell.h"

class CNumber : public CCell{
public:
    explicit CNumber(std::string mInput);

    ~CNumber() override;

    void Print (std::ostream & os) const override;

    CType CellType() const override;

    friend std::ostream &operator<<(std::ostream &os, const CNumber &number);

    std::string GetOutput() const override;

    std::string GetInput() const override;

    void AddChild(const std::string& child) override;

    void DeleteChild(const std::string &child) override;

    bool HasChildren() override;

    std::vector<std::string> GetChildren() override;

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
    double m_Result{};
    std::string m_Input;
    std::vector<std::string> m_Children;
    std::set<std::string> m_Parents;
    bool m_Cycle;
    bool m_Error;
};


#endif //SEMESTRAL_CNUMBER_H

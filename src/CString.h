/**
 * Class for handling strings
 */
#ifndef SEMESTRAL_CSTRING_H
#define SEMESTRAL_CSTRING_H

#include <string>
#include <ostream>
#include "CCell.h"

class CString : public CCell{
public:
    explicit CString(std::string mVal);

    ~CString() override;

    void Print (std::ostream & os) const override;

    CType CellType() const override;

    friend std::ostream &operator<<(std::ostream &os, const CString &string);

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
    std::string m_Input;
    std::vector<std::string> m_Children;
    std::set<std::string> m_Parents;
    bool m_Cycle;
    bool m_Error;
};


#endif //SEMESTRAL_CSTRING_H

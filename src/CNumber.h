//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CNUMBER_H
#define SEMESTRAL_CNUMBER_H

#include <ostream>
#include "CCell.h"

class CNumber : public CCell{
public:
    CNumber(std::string mInput, int mXPos, int mYPos);

    ~CNumber() override;

    void Print (std::ostream & os) const override;

    //bool IsNumber () const override;

    CType CellType() const override;

    friend std::ostream &operator<<(std::ostream &os, const CNumber &number);

    std::string GetOutput() const override;

    void AddChild(const std::string& child) override;

    bool HasChildren() override;

    std::vector<std::string> GetChildren() override;

    int getMXPos() const;

    void setMXPos(int mXPos);

    int getMYPos() const;

    void setMYPos(int mYPos);

    void Update(const std::string &content) override;

    void AddParent(const std::string &parent) override;

    bool HasParents() override;

    std::set<std::string> GetParents() override;

    void CycleSwitch() override;

private:
    double m_Result{};
    std::string m_Input;
    std::vector<std::string> m_Children;
    std::set<std::string> m_Parents;
    int m_xPos, m_yPos;
};


#endif //SEMESTRAL_CNUMBER_H

//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CNUMBER_H
#define SEMESTRAL_CNUMBER_H

#include <ostream>
#include <set>
#include "CCell.h"

class CNumber : public CCell{
public:
    CNumber(std::string mInput);

    ~CNumber() override;

    void Print (std::ostream & os) const override;

    //bool IsNumber () const override;

    CType CellType() const override;

    friend std::ostream &operator<<(std::ostream &os, const CNumber &number);

    std::string GetOutput() const override;

    void AddChild(const std::string& child) override;

    bool HasChildren() override;

    std::set<std::string> GetChildren() override;

private:
    double m_Result{};
    std::string m_Input;
    std::set<std::string> childern;
};


#endif //SEMESTRAL_CNUMBER_H

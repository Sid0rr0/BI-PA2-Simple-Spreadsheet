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
    //CFunction(std::string mOperation, double mVal);
    CFunction(std::string  mInput);

    ~CFunction() override;

    void Print (std::ostream & os) const override;

    void PrintValue (std::ostream & os) const;

    //bool IsNumber () const override;

    CType CellType () const override;

    int ParseInput(const std::string& input);

    friend std::ostream &operator<<(std::ostream &os, const CFunction &function);

private:
    std::string m_Input;
    std::string m_Operation;
    double m_Value;
    double m_Result;
};


#endif //SEMESTRAL_CFUNCTION_H

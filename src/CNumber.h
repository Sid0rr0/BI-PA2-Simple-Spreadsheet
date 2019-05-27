//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CNUMBER_H
#define SEMESTRAL_CNUMBER_H

#include <ostream>
#include "CCell.h"

class CNumber : public CCell{
public:
    CNumber(double mVal);

    ~CNumber() override;

    void Print (std::ostream & os) const override;

    //bool IsNumber () const override;

    CType CellType() const override;

    friend std::ostream &operator<<(std::ostream &os, const CNumber &number);

private:
    double m_Val;
};


#endif //SEMESTRAL_CNUMBER_H

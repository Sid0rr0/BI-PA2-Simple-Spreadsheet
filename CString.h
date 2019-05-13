//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CSTRING_H
#define SEMESTRAL_CSTRING_H

#include <string>
#include <ostream>
#include "CCell.h"

class CString : public CCell{
public:
    CString(std::string mVal);

    virtual ~CString();

    void Print (std::ostream & os) const override;

    bool isNumber () const override;

    friend std::ostream &operator<<(std::ostream &os, const CString &string);

private:
    std::string m_Val;
};


#endif //SEMESTRAL_CSTRING_H

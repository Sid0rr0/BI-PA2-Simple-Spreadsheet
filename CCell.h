//
// Created by hung on 12.5.19.
//

#ifndef SEMESTRAL_CCELL_H
#define SEMESTRAL_CCELL_H


#include <ostream>

class CCell {
public:
    CCell();

    virtual ~CCell();

    virtual void Print (std::ostream & os) const = 0;

    friend std::ostream &operator<<(std::ostream &os, const CCell &cell);

    virtual bool isNumber () const = 0;

};


#endif //SEMESTRAL_CCELL_H

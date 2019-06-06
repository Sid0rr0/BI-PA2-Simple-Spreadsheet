//
// Created by hung on 12.5.19.
//

#include "CCell.h"

CCell::CCell() {}

CCell::~CCell() {

}

std::ostream &operator<<(std::ostream &os, const CCell &cell) {
    cell.Print(os);
    return os;
}

std::string CCell::GetOutput() const {
    return "";
}

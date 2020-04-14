#pragma once

#include "NumberSetOperand.h"

NumberSetOperand::NumberSetOperand(set<long double> value) : BaseOperand(OperandTypeEnum::NUMBER_SET) {
    this->value = value;
}

bool NumberSetOperand::contains(Number number) {   
    for (set<long double>::iterator it = value.begin(); it != value.end(); ++it) {
        if (number == *it) {
            return true;
        }
    }
    return false;
}

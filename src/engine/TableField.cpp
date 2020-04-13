#pragma once

#include "TableField.h"

TableField::TableField(string name, DataTypeEnum type) {
    this->name = name;
    this->type = type;
}

string TableField::getName() {
    return this->name;
}

DataTypeEnum TableField::getType() {
    return this->type;
}

bool TableField::operator ==(const TableField &tableField) const {
    return this->name == tableField.name && this->type == tableField.type;
}
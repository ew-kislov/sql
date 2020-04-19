#include "RelationCondition.h"

#include "NumberOperand.cpp"
#include "StringOperand.cpp"
#include "TableFieldOperand.cpp"
#include "../../engine/Varchar.cpp"
#include "../../engine/Number.cpp"
#include "../../engine/DataTypeFactory.cpp"

#include <string>


RelationCondition::RelationCondition(BaseOperand* operand1, BaseOperand* operand2, string relationType) : BinaryCondition(operand1, operand2) {
    if (!relationType.compare("=")) {
        this->relationType = RelationTypeEnum::EQ;
    } else if (!relationType.compare("!=")) {
        this->relationType = RelationTypeEnum::NEQ;
    } else if (!relationType.compare(">")) {
        this->relationType = RelationTypeEnum::GREATER;
    } else if (!relationType.compare(">=")) {
        this->relationType = RelationTypeEnum::EGREATER;
    } else if (!relationType.compare("<")) {
        this->relationType = RelationTypeEnum::LESS;
    } else if (!relationType.compare("<=")) {
        this->relationType = RelationTypeEnum::ELESS;
    }
}

bool RelationCondition::calculate(vector<TableField> fields, vector<DataType*> row) {
    int fieldIndex1 = -1, fieldIndex2 = -1;
    vector<string> fieldNames;
    
    for (TableField it: fields) {
        fieldNames.push_back(it.getName());
    }
    
    if (
        operand1->getType() == OperandTypeEnum::TABLE_FIELD &&
        operand2->getType() == OperandTypeEnum::TABLE_FIELD
    ) {
        TableFieldOperand* fieldOperand;
        
        fieldOperand = dynamic_cast<TableFieldOperand*>(operand1);
        fieldIndex1 = VectorHelper::findInVector(fieldNames, fieldOperand->getValue());
        
        fieldOperand = dynamic_cast<TableFieldOperand*>(operand2);
        fieldIndex2 = VectorHelper::findInVector(fieldNames, fieldOperand->getValue());
        
        if (fieldIndex1 == -1 || fieldIndex2 == -1) {
            cout << "Couldn't find field";
            // TODO: throw exception
        }
            
    } else if (operand1->getType() == OperandTypeEnum::TABLE_FIELD ||
               operand2->getType() == OperandTypeEnum::TABLE_FIELD
    ) {
        BaseOperand* fieldBase;
        BaseOperand* nonFieldBase;
        int* fieldIndex;
        
        if (operand1->getType() == OperandTypeEnum::TABLE_FIELD) {
            fieldBase = operand1;
            nonFieldBase = operand2;
            fieldIndex = &fieldIndex1;
        } else {
            fieldBase = operand2;
            nonFieldBase = operand1;
            fieldIndex = &fieldIndex2;
        }
        
        TableFieldOperand* fieldOperand = dynamic_cast<TableFieldOperand*>(fieldBase);
        TableField* field;
        
        if (nonFieldBase->getType() == OperandTypeEnum::NUMBER) {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::NUMBER);
        } else {
            field = new TableField(fieldOperand->getValue(), DataTypeEnum::VARCHAR);
        }
        
        *fieldIndex = VectorHelper::findInVector(fields, *field);
        
        if (*fieldIndex == -1) {
            cout << "Couldn't find field with this type" << endl;
            // TODO: throw exception
        }
    }
    
    DataType* dataTypeOperand1 = DataTypeFactory::getDataTypeOperand(fieldIndex1, row, operand1);
    DataType* dataTypeOperand2 = DataTypeFactory::getDataTypeOperand(fieldIndex2, row, operand2);
    
    if (dataTypeOperand1->getType() != dataTypeOperand2->getType()) {
        cout << "Relation operand types don't match" << endl;
        // TODO: throw exception
    }
    
    switch (relationType) {
        case EQ: return operand1 == operand2;
        case NEQ: return operand1 != operand2;
        case GREATER: return operand1 > operand2;
        case EGREATER: return operand1 >= operand2;
        case LESS:  return operand1 < operand2;
        case ELESS:  return operand1 <= operand2;
    }
}

string RelationCondition::toString() {
    string message;     
    message += "RelationCondition ";
    return message;
}

//
// Created by nono on 04/02/24.
//

#include <utility>
#include "../../../include/interpreter/values/ReturnedString.h"

ReturnedString::ReturnedString(std::string value) {
    this->value = std::move(value);
    this->type = String;
}

void ReturnedString::display() {

}

#pragma once
#ifndef FACTORY_BOX
#define FACTORY_BOX
#include "Box.h"
#include "Factory.h"
#include "Figure.h"
class FactoryBox : public Factory {
public:
    FactoryBox() {};
    Figure* Create() override {
        return new Box();
    }
    ~FactoryBox() {};
};
#endif
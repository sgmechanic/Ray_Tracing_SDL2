#pragma once
#ifndef FACTORY_BOX
#define FACTORY_BOX
#include "Box.h"
#include "Factory.h"
#include "Figure.h"
class FactoryBox : public Factory {
public:
    FactoryBox() {};
    std::shared_ptr<Figure> Create() override {
        return std::make_shared<Box>();
    }
    ~FactoryBox() {};
};
#endif 
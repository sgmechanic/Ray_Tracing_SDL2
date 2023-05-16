#ifndef FACTORY_PYRAMID
#define FACTORY_PYRAMID
#include "Pyramid.h"
#include "Factory.h"
#include "Figure.h"
class FactoryPyramid : public Factory {
public:
    FactoryPyramid() {};
    Figure* Create() override {
        return  new Pyramid();
    }
    ~FactoryPyramid() {};
};
#endif
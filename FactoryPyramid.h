#ifndef FACTORY_PYRAMID
#define FACTORY_PYRAMID
#include "Pyramid.h"
#include "Factory.h"
#include "Figure.h"
class FactoryPyramid : public Factory {
public:
    FactoryPyramid() {};
    std::shared_ptr<Figure> Create() override {
        return  std::make_shared<Pyramid>();
    }
    ~FactoryPyramid() {};
};
#endif
#ifndef FACTORY_SPHERE
#define FACTORY_SPHERE
#include "Sphere.h"
#include "Factory.h"
#include "Figure.h"
class FactorySphere : public Factory {
public:
    FactorySphere() {};
    Figure* Create() override {
        return new Sphere();
    }
    ~FactorySphere() {};
};
#endif
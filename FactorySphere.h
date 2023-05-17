#ifndef FACTORY_SPHERE
#define FACTORY_SPHERE
#include "Sphere.h"
#include "Factory.h"
#include "Figure.h"
class FactorySphere : public Factory {
public:
    FactorySphere() {};
    std::shared_ptr<Figure> Create() override {
        return std::make_shared<Sphere>();
    }
    ~FactorySphere() {};
};
#endif
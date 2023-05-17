#ifndef FACTORY_H
#define FACTORY_H
#include "Figure.h"
//Modern C++ Factory Pattern
class Factory {
public:
    Factory() {};
    virtual std::shared_ptr<Figure> Create() = 0;
    virtual ~Factory() {};
};
#endif
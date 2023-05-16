#ifndef FACTORY_H
#define FACTORY_H
#include "Figure.h"
class Factory {
public:
    Factory() {};
    virtual Figure* Create() = 0;
    virtual ~Factory() {};
};
#endif
//
// Created by G on 5/29/2018.
//

#ifndef SIGNAGE_SHAPE_H
#define SIGNAGE_SHAPE_H

#include "Element.h"

class Shape: public Element {
public:
    Shape(shared_ptr<screenManager> screenMng);

    void tick(float tSecs) override;
    void render() override;


    ~Shape();
};

#endif //SIGNAGE_SHAPE_H

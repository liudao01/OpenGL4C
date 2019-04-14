//
// Created by liuml on 2019/4/14.
//

#ifndef OPENGL4C_FILTERONE_H
#define OPENGL4C_FILTERONE_H


#include "BaseOpengl.h"

class FilterOne : public BaseOpengl {
public:
    FilterOne();

    ~FilterOne();

public:

    void onCreate();//虚函数virtual
    void onChange(int width, int height);//虚函数virtual
    void onDraw();
};


#endif //OPENGL4C_FILTERONE_H

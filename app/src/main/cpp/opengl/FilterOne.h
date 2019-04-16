//
// Created by liuml on 2019/4/14.
//

#ifndef OPENGL4C_FILTERONE_H
#define OPENGL4C_FILTERONE_H


#include "BaseOpengl.h"

class FilterOne : public BaseOpengl {
public:

    GLint vPosition;
    GLint fPosition;
    GLint sampler;
    GLuint textureId;
    GLint u_matrix;


    int w;
    int h;
    void *pixels = NULL;

//自己建立的矩阵
    float matrix[16];

public:
    FilterOne();

    ~FilterOne();

    void onCreate();//虚函数virtual
    void onChange(int width, int height);//虚函数virtual
    void onDraw();

    void setMatrix(int width, int height);

    void setPilex(void *data, int widht, int height, int length);
};


#endif //OPENGL4C_FILTERONE_H

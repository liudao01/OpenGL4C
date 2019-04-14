//
// Created by liuml on 2019/4/14.
//

#ifndef OPENGL4C_BASEOPENGL_H
#define OPENGL4C_BASEOPENGL_H

#include <cstring>
#include <GLES2/gl2.h>

class BaseOpengl {
public :
    int surface_width;
    int surface_height;

    char *vertex;
    char *fragment;

    float *vertexs;
    float *fragments;

    GLuint program;
public:
    BaseOpengl();

    ~BaseOpengl();

    virtual void onCreate();//虚函数virtual
    virtual void onChange(int width, int height);//虚函数virtual
    virtual void onDraw();

};

#endif //OPENGL4C_BASEOPENGL_H

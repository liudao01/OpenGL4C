//
// Created by liuml on 2019/4/14.
//


#include "BaseOpengl.h"

BaseOpengl::BaseOpengl() {

    vertexs = new float[8];//4个点所以是8个空间
    fragments = new float[8];

    float v[] = {1, -1,
                 1, 1,
                 -1, -1,
                 -1, 1};

    //内存拷贝
    memcpy(vertexs, v, sizeof(v));

    //同理

    float f[] = {
            1, 1,
            1, 0,
            0, 1,
            0, 0
    };
    memcpy(fragments, f, sizeof(f));


}

BaseOpengl::~BaseOpengl() {

    delete[]vertexs;
    delete[]fragments;

}

void BaseOpengl::onCreate() {

}

void BaseOpengl::onChange(int width, int height) {
}

void BaseOpengl::onDraw() {

}

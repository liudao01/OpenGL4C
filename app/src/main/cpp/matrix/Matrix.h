//
// Created by liuml on 2019/4/8.
//

#ifndef OPENGL4C_MATRIX_H
#define OPENGL4C_MATRIX_H

#include <math.h>

/**
 *
 * float matrix[16]={
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    }

 */
static void initMatrix(float *matrix) {
    //上面的矩阵 1的位置 是 位置数量除以5 余0
    for (int i = 0; i < 16; ++i) {
        if (i % 5 == 0) {
            matrix[i] = 1;
        } else {
            matrix[i] = 0;
        }
    }

}


//旋转
static void rotateMatrix(double angle, float *matrix) {
    //角度转弧度
    angle = angle * (M_PI / 180.0);

    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);

}

//缩放
static void scaleMatrix(double scale, float *matrix) {
    matrix[0] = scale;
    matrix[5] = scale;
}


//平移  这里对2d 图片平移 只用了xy 如果是3d 那么可以加上z
static void transMatrix(double x, double y, float *matrix){
    matrix[3] = x;
    matrix[7] = y;
}

//正交投影
static  void orthoM(float left, float right, float bottom, float top,float *matrix){
    matrix[0] = 2 / (right - left);
    matrix[3] = (right + left)/(right - left) * -1;
    matrix[5] = 2 / (top - bottom);
    matrix[7] = (top + bottom) / (top - bottom) * -1;
    matrix[10] = 1;
    matrix[11] = 1;
}

#endif //OPENGL4C_MATRIX_H









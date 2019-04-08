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
static void rotateMatrix(double angle,float *matrix){
    //角度转弧度
    angle = angle * (M_PI / 180.0);

    matrix[0] = cos(angle);
    matrix[1] = -sin(angle);
    matrix[4] = sin(angle);
    matrix[5] = cos(angle);


}
#endif //OPENGL4C_MATRIX_H

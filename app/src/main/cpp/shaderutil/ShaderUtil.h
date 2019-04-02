//
// Created by liuml on 2019/3/28.
//

#ifndef OPENGL4C_SHADERUTIL_H
#define OPENGL4C_SHADERUTIL_H

#include <GLES2/gl2.h>

static int loadShaders(int shaderType, const char *code) {

    //1. 创建shader
    int shader = glCreateShader(shaderType);
    //加载
    glShaderSource(shader, 1, &code, 0);
    //编译
    glCompileShader(shader);
    return shader;
}

static int createProgram(const char *vertex, const char *fragment) {
    //2. 根据shader源码并比那一shader
    int vertexShader = loadShaders(GL_VERTEX_SHADER, vertex);
    int fragmentShader = loadShaders(GL_FRAGMENT_SHADER, fragment);
    //3. 创建一个渲染程序
    int program = glCreateProgram();
    LOGD("program = %d", program)

    //4. 将着色器程序添加到渲染程序中
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    //5. 链接源程序
    glLinkProgram(program);

    return program;
}

#endif //OPENGL4C_SHADERUTIL_H

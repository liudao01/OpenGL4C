//
// Created by liuml on 2019/4/14.
//

#include "FilterOne.h"


FilterOne::FilterOne() {

}

FilterOne::~FilterOne() {

}

void FilterOne::onCreate() {

    vertex = "attribute vec4 v_Position;\n"
             "attribute vec2 f_Position;\n"
             "varying vec2 ft_Position;\n"
             "uniform mat4 u_Matrix;\n"
             "void main() {\n"
             "    ft_Position = f_Position;\n"
             "    gl_Position = v_Position * u_Matrix;\n"
             "}";

    fragment = "precision mediump float;\n"
               "varying vec2 ft_Position;\n"
               "uniform sampler2D sTexture;\n"
               "void main() {\n"
               "    gl_FragColor=texture2D(sTexture, ft_Position);\n"
               "}";

    LOGD("callback_SurfaceCreate")


    program = createProgram(vertex, fragment);
    LOGD("opengl program %d", program)

    //顶点坐标
    vPosition = glGetAttribLocation(program, "v_Position");
    //纹理坐标
    fPosition = glGetAttribLocation(program, "f_Position");
    //2d 纹理
    sampler = glGetUniformLocation(program, "sTexture");

    //矩阵
    u_matrix = glGetUniformLocation(program, "u_Matrix");


    //生成纹理
    glGenTextures(1, &textureId);

    //绑定纹理
    glBindTexture(GL_TEXTURE_2D, textureId);

    //环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //解绑
    glBindTexture(GL_TEXTURE_2D, 0);//0就是解绑
}

void FilterOne::onChange(int width, int height) {


    glViewport(0, 0, width, height);

    setMatrix(width, height);


}

void FilterOne::onDraw() {

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //使用program  赋值的操作 数据传递的操作都在这个useProgram之后
    glUseProgram(program);

    //使用矩阵
    glUniformMatrix4fv(u_matrix, 1, GL_FALSE, matrix);

    //激活纹理
    glActiveTexture(GL_TEXTURE5);
    //给uniformli 变量赋值 sampler
    glUniform1i(sampler, 5);

    //绑定纹理id
    glBindTexture(GL_TEXTURE_2D, textureId);

    //根据指定的参数，生成一个2D纹理（Texture）
    if (pixels != NULL) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    //启用顶点
    glEnableVertexAttribArray(vPosition);//可用
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, false, 8, vertexs);//赋值

    //启用纹理
    glEnableVertexAttribArray(fPosition);
    glVertexAttribPointer(fPosition, 2, GL_FLOAT, false, 8, fragments);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);//两个三角形
//    glDrawArrays(GL_TRIANGLES, 0, 3);

    //绘制完成后解绑
    glBindTexture(GL_TEXTURE_2D, 0);//0就是解绑

}

void FilterOne::setMatrix(int width, int height) {
    //初始化矩阵
    initMatrix(matrix);

    //根据比例 看根据宽还是高进行动态缩放
    //屏幕宽除以屏幕高
    float screen_r = 1.0 * width / height;
    //图片的宽高比
    float picture_r = 1.0 * w / h;

    if (screen_r > picture_r) {
        //图片宽度缩放

        //根据屏幕宽度和图片宽度的比值 得到图片高度缩放的比值
        float r = width / (1.0 * height / h * w);
        orthoM(-r, r, -1, 1, matrix);
    } else {
        //图片高度缩放

        //根据屏幕宽度和图片宽度的比值 得到图片高度缩放的比值
        float r = height / (1.0 * width / w * h);
        orthoM(-1, 1, -r, r, matrix);
    }
}

void FilterOne::setPilex(void *data, int widht, int height, int length) {

    w = widht;
    h = height;
    pixels = data;
    if (surface_height > 0 && surface_width > 0) {
        LOGD("FilterOne setPilex surface_height" )
        setMatrix(surface_width, surface_height);
    }

}

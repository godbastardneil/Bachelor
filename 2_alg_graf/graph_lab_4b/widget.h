#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>
#include <QKeyEvent>
#include <GL/glu.h>
#include "objloader.h" // загрузчик моделей в формате obj

class MyWidget : public QOpenGLWidget
{
    Q_OBJECT
    QTimer *paintTimer; // таймер

    GLubyte mc = 0;
    GLuint model[2]; // номер display list для вывода нужной модели

    GLuint torus;

    GLubyte tc = 0;
    GLuint texture[2]; // текстуры

    GLfloat a = 0; // угол

    void initTexture(uint index, QImage &texture1); // поставить настройки для текстуры
    void LoadGLTextures(); // загрузить текстуры
    GLuint drawCube(); // нарисовать куб
    void initLight(); // включить свет
    virtual void keyPressEvent(QKeyEvent *event);

public:
    MyWidget(QWidget *parent = nullptr);
protected:
   void initializeGL();
   void resizeGL(int nWidth, int nHeight);
   void paintGL();
};
#endif // WIDGET_H

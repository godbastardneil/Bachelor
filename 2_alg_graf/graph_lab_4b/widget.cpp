#include "widget.h"

MyWidget::MyWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,600); // задаем размеры окна
    paintTimer = new QTimer(this); // создаю таймер
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start();
}

void MyWidget::initTexture(uint index, QImage &texture1)
{
    texture1.convertTo(QImage::Format_RGBA8888); // формат текстуры OpenGL
    glBindTexture(GL_TEXTURE_2D, texture[index]); // привязываю текстуру GL_Texture_2d к участку памяти texture[index]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // параметры фильтрации
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()), GLsizei(texture1.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits()); // заливаю текстуру
}

void MyWidget::LoadGLTextures()
{
    // Создание текстур
    glGenTextures(3, texture);

    // Загрузка картинки
    QImage texture1;
    texture1.load(":/files/marble.jpg");
    initTexture(0, texture1); // инициализация и настройки для текстуры

    texture1.load(":/files/metal.jpg");
    initTexture(1, texture1);
}

GLuint MyWidget::drawCube()
{
    GLuint num = glGenLists(1);
    glNewList(num,GL_COMPILE);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх лево

                    // Задняя грань
    glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ лево

                    // Верхняя грань
    glNormal3f( 0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право

                    // Нижняя грань
    glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право

                    // Правая грань
    glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево

                    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
    glEnd();

    glEndList();
    return num;
}

void MyWidget::initLight()
{
    GLfloat light_ambient[] = { 0, 0, 0, 0.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 2.0, 1.0 };

    /* устанавливаем параметры источника света */
    glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

    /* включаем освещение и источник света */
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void MyWidget::initializeGL()
{
    glEnable(GL_MULTISAMPLE); // сглаживание MSAA вкл
    LoadGLTextures();			// Загрузка текстур
    glEnable(GL_TEXTURE_2D);		// Разрешение наложение текстуры
    glClearColor(1,1,1,1); // заливаем белым цветом
    glClearDepth(1.0); // Разрешить очистку буфера глубины
    glEnable(GL_DEPTH_TEST); // Разрешить тест глубины
    glDepthFunc(GL_LESS); // Тип теста глубины
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Улучшение в вычислении перспективы
    initLight(); // включаем свет
    model[0] = objloader::Instance().load(":/files/teapot.obj");
    model[1] = drawCube();
    torus = objloader::Instance().load(":/files/copel.obj");
}

void MyWidget::resizeGL(int nWidth, int nHeight)
{
    // установка точки обзора
    glViewport(0, 0, nWidth, nHeight);
    qreal aspectratio = qreal(nWidth) / qreal(nHeight);

    // инициализация матрицы проекций
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // сброс матрицы проекции
    gluPerspective( 90.0, aspectratio, 0.1, 100.0 );

    // инициализация матрицы вида модели
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); // сброс матрицы вида модели
}

void MyWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key()==Qt::Key_T) {
        ++tc%=2;
    }
    if (event->key()==Qt::Key_M) {
        ++mc%=2;
    }
}

void MyWidget::paintGL() // рисование
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очистка экрана и буфера глубины
    glLoadIdentity();           // сбросить текущую матрицу
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[1-tc]);
    glTranslatef(0, -3, -3.5);
    glDeleteLists(torus, 1);
    torus = objloader::Instance().draw(a/100);
    glCallList(torus);
    glTranslatef(0, 3, 0.1f);
    glRotatef(a, 0.0f, 1.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, texture[tc]);
    glCallList(model[mc]);
    glDisable(GL_TEXTURE_2D);

    a += 0.1f;
}

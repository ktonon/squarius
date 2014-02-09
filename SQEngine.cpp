/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"
#include "Game/SQPuzzleEngine.h"
#include <locale.h>

const int SQEngine::FRAMES_PER_SECOND = 30;

SQEngine::SQEngine(QWidget *parent) :
    QGLWidget(parent),
    _shaderProgram(),
    _renderTimer(),
    _puzzleEngine(NULL),
    _height(-1),
    _width(-1)
{
    // TODO: replace this with real level loader
    _puzzleEngine = new SQPuzzleEngine(SQPuzzle::load(0, 0), this);
}

SQEngine::~SQEngine()
{
}

void SQEngine::initializeGL()
{
    initializeGLFunctions();

    qDebug() << "Initializing shaders";
    initShaders();

    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.1f, 0.15f, 0.2f, 1.0f);

    _puzzleEngine->activate();

    // using QBasicTimer because its faster that QTimer
    _renderTimer.start(1000.0f / FRAMES_PER_SECOND, this);
}

void SQEngine::initShaders()
{
    // Overriding system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compiling vertex shader
    if (!_shaderProgram.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.vsh"))
        close();

    // Compiling fragment shader
    if (!_shaderProgram.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.fsh"))
        close();

    // Linking shader pipeline
    if (!_shaderProgram.link())
        close();

    // Binding shader pipeline for use
    if (!_shaderProgram.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");

}

void SQEngine::timerEvent(QTimerEvent *)
{
    _puzzleEngine->updateModelView();

    // Update scene
    updateGL();
}

void SQEngine::paintGL()
{
    // Set modelview-projection matrix
    _shaderProgram->setUniformValue("mvp_matrix", _puzzleEngine->mvpMatrix());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    _puzzleEngine->renderModel();
    glPopMatrix();
}

void SQEngine::resizeGL(int w, int h)
{
    glViewport(0, 0, _width, _height);
    GLfloat aspect = (GLfloat) w / ((GLfloat)h?h:1);
    _width = w;
    _height = h;
    _puzzleEngine->setRatio(aspect);
}

void SQEngine::togglePerspective()
{
    _puzzleEngine->perspectiveSwitchBegin();
}

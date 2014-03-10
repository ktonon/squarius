/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "SQEngine.h"
#include "Game/SQPuzzleEngine.h"
#include "Utilities/Matrix.h"
#include "Utilities/SQPrimitives.h"
#include "Utilities/SQStack.h"
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
    connect(_puzzleEngine, SIGNAL(perspectedSwitchEnded()), SIGNAL(perspectiveChanged()));
}

SQEngine::~SQEngine()
{
    deleteTexture(_texture);
}

void SQEngine::initializeGL()
{
    initializeGLFunctions();
    qglClearColor(Qt::black);
    initShaders();
    initTextures();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    SQStack::instance()->init(&_shaderProgram, _puzzleEngine);
    SQPrimitives::instance()->init(&_shaderProgram);
    _puzzleEngine->activate();
    _puzzleEngine->updateModelView();
    emit perspectiveChanged();

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

void SQEngine::initTextures()
{
    // Load cube.png image
    glEnable(GL_TEXTURE_2D);
    _texture = bindTexture(QImage(":/cube.png"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void SQEngine::timerEvent(QTimerEvent *)
{
    _puzzleEngine->updateModelView();

    // Update scene
    updateGL();
}

QString SQEngine::toString() const
{
    return sqMatrixToString(SQStack::instance()->mvpMatrix());
}

void SQEngine::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use texture unit 0 which contains cube.png
    _shaderProgram.setUniformValue("texture", 0);

    // Draw the puzzle geometry
    _puzzleEngine->renderModel();
}

void SQEngine::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);
    _width = w;
    _height = h;

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

//    _puzzleEngine->setRatio(aspect);
    _puzzleEngine->setShape(w, h);
}

void SQEngine::togglePerspective()
{
    _puzzleEngine->perspectiveSwitchBegin();
}

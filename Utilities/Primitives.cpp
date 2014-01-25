/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#include "Primitives.h"
#include <QtOpenGL>

void drawCube() {
    static GLshort tubeVertices[] = {
        0, 0, 0,
        1, 0, 0,
        0, 0, 1,
        1, 0, 1,

        0, 1, 1,
        1, 1, 1,

        0, 1, 0,
        1, 1, 0,

        0, 0, 0,
        1, 0, 0,
    };
    static GLshort topVertices[] = {
        1, 0, 0,
        1, 1, 0,
        1, 0, 1,
        1, 1, 1,
    };
    static GLshort bottomVertices[] = {
        0, 1, 0,
        0, 0, 0,
        0, 1, 1,
        0, 0, 1,
    };
    static GLubyte tubeColors[] = {
        255, 255, 0, 255,
        0, 255, 255, 255,
        255, 0, 255, 255,
        0, 0, 0, 0,

        255, 255, 0, 255,
        0, 255, 255, 255,

        255, 0, 255, 255,
        0, 0, 0, 0,

        255, 255, 0, 255,
        0, 255, 255, 255,
    };
    static GLubyte topColors[] = {
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
        255, 255, 255, 255,
    };
    static GLubyte bottomColors[] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };

    glVertexPointer(3, GL_SHORT, 0, tubeVertices);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, tubeColors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);

    glVertexPointer(3, GL_SHORT, 0, topVertices);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, topColors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glVertexPointer(3, GL_SHORT, 0, bottomVertices);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, bottomColors);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

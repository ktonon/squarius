/**
 * @file
 * @author Kevin Tonon <kevin@betweenconcepts.com>
 * @section LICENSE
 * 2013 Kevin Tonon
 * All Rights Reserved
 */

#ifndef SQOPENGL_H
#define SQOPENGL_H

#include <QtOpenGL>

#if defined(Q_OS_IOS)
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#define glFrustum glFrustumf
#define glOrtho glOrthof
#endif

#endif // SQOPENGL_H

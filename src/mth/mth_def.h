/* FILE NAME   : mth_def.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               Definition math types.
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#include <cmath>
#include <cassert>

#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */

typedef DOUBLE DBL;
typedef FLOAT FLT;

template<typename Type> class vec3;
template<typename Type> class matr;
template<typename Type> class vec2;
template<typename Type> class vec4;
template<typename Type> class ray;
template<typename Type> class camera;

#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */
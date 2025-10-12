/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_def.h
 * PURPOSE     : Ray tracing.
 *               Default math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#include <cmath>

#ifndef WIN32
#define WIN32
#include <COMMONDF.H>
#undef WIN32
#else
#include <COMMONDF.H>
#endif

/* Pi const */
#define PI 3.1415926535897932846

/* From degree to radian*/
#define D2R(A) ((A) * (PI / 180.0))

/* From radian to degree */
#define R2D(A) ((A) * (180.0 / PI))

/* Based float type */
typedef FLOAT FLT;

/* Based double type */
typedef DOUBLE DBL;

/* Project namespace */
namespace mth
{
  template<typename Type> class vec3;
  template<typename Type> class vec2;
  template<typename Type> class vec4;
  template<typename Type> class matr;
  template<typename Type> class ray;
  template<typename Type> class camera;
} /* End of 'mth' namespace */

#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */

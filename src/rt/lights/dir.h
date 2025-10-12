/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt.cpp
 * PURPOSE     : Ray tracing.
 *               Ray tracing handle direction light module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __dir_h_
#define __dir_h_

#include "rt/rt_def.h"
#include "lights.h"

/* Project namespace */
namespace vart
{
  class dir : public light
  {
  public:
    vec3 
      Color,     // Color light
      Dir;       // Direction light

    /* Direction constructor.
     * ARGUMENTS:
     *   - direction:
     *       const vec3 &dir;
     *   - color:
     *       const vec3 &color;
     */
    dir( const vec3 &dir, const vec3 &color ) : Dir(dir.Normalizing()), Color(color)
    {
    } /* End of 'dir' constructor */

    /* Get shadow function.
     * ARGUMENTS:
     *   - position:
     *       const vec3 &P;
     *   - light:
     *       light_infor *L;
     * RETURNS:
     *   - (DBL) result.
     */
    DBL Shadow( const vec3 &P, light_info *L ) override
    {
      L->L = Dir;
      L->Dist = 10000;
      L->Color = Color;

      return 1;
    } /* End of 'Shadow' function */
  }; /* End of 'dir' class */
} /* End of 'vart' namespace*/

#endif /* __dir_h_ */

/* END OF 'dir.h' FILE*/

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt.cpp
 * PURPOSE     : Ray tracing.
 *               Ray tracing handle point light module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __point_h_
#define __point_h_

#include "rt/rt_def.h"
#include "lights.h"

/* Project namespace */
namespace vart
{
  class point : public light
  {
  public:
    vec3 
      Color,     // Color light
      Position;  // Point light position
    DBL Power;   // Power of light

    /* pointection constructor.
     * ARGUMENTS:
     *   - pointection:
     *       const vec3 &pos;
     *   - color:
     *       const vec3 &color;
     */
    point( const vec3 &pos, const vec3 &color, DBL power ) : Position(pos), Color(color), Power(power)
    {
    } /* End of 'point' constructor */

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
      L->L = (Position - P).Normalizing();
      L->Dist = !(P - Position);
      L->Color = Color;

      auto min = 
      [] ( DBL x, DBL y ) -> DBL
      {
        if (x < y)
          return x;
        return y;
      };
      return min(1, 1 / Position.X + Position.Y * L->Dist + Position.Z * L->Dist * L->Dist); // Power / L->Dist;
    } /* End of 'Shadow' function */
  }; /* End of 'point' class */
} /* End of 'vart' namespace*/

#endif /* __point_h_ */

/* END OF 'point.h' FILE*/

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* Ray tracing representation Type */
  template<typename Type>
    class ray
    {
    public:
      vec3<Type> Org, Dir; // Origin and direction vectors

      /* Default ray constructor */
      ray( VOID )
      {
      } /* End of 'ray' constructor */

      /* Ray constructor.
       * ARGUMENTS:
       *   - vec org:
       *       const vec3<Type> &O;
       *   - vec direction:
       *       const vec3<Type> &D;
       */
      ray( const vec3<Type> &O, const vec3<Type> &D ) : Org(O), Dir(D.Normalizing())
      {
      } /* End of 'ray' function */

      /* Operator() function.
       * ARGUMENTS:
       *   - coef:
       *       Type T;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */
    }; /* End of 'ray' class */
} /* End of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */

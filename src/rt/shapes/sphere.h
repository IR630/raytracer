/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing sphere handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "rt/rt_def.h"

/* Project namespace */
namespace vart
{
  /* Plane representation type */
  class sphere : public shape
  {
    DBL 
      R,    // Radius
      R2;   // Radius square
    vec3 C; // Vector of centre sphere

  public:
    /* Sphere constructor.
      * ARGUMENTS:
      *   - coordinates of centre sphere:
      *       vec3 o;
      *   - radius;
      *       DBL R;
      */
    sphere( const vec3 &o, DBL r ) : C(o), R(r), R2(r * r)
    {
    } /* End of 'sphere' contructor */

    /* Sphere constructor.
      * ARGUMENTS:
      *   - coordinates of centre sphere:
      *       vec3 o;
      *   - radius;
      *       DBL R;
      */
    sphere( const vec3 &o, DBL r, surface s ) : C(o), R(r), R2(r * r), shape(s)
    {
    } /* End of 'sphere' contructor */

    /* Bool intersection function.
    * ARGUMENTS:
    *   - ray:
    *       const vart::ray &R;
    *   - intersection:
    *       intr *Intr;
    * RETURN:
    *   - (BOOL) TRUE if we need to draw, FALSE otherwise.
    */
    BOOL Intersect( const ray &R, intr *Intr ) const override
    {
      vec3 a = C - R.Org;
      DBL 
        OC2 = a & a,
        OK = a & R.Dir,
        OK2 = OK * OK,
        h2 = R2 - (OC2 - OK2);

      if (OC2 < R2)
      {
        Intr->T = OK + sqrt(h2);
        Intr->Shp = (shape *)this;
        return TRUE;
      }
      if (OK < Threshold)
        return FALSE;
      if (h2 < Threshold)
        return FALSE;
      Intr->T = OK - sqrt(h2);
      Intr->Shp = (shape *)this;

      return TRUE;
    } /* End of 'Intersect' function */

    /* Getting normal function.
      * ARGUMENTS:
      *   - intersection:
      *       const intr *Intr;
      * RETURNS: None.
      */
    VOID GetNormal( intr *Intr ) const override
    {
      Intr->N = (Intr->P - C) / R;
    } /* End of 'GetNormal' function */

    /* Getting number of all intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - list:
     *       intr_list *Il;
     * RETURNS:
     *   - (INT) result number of all intersect.
     */
    INT AllIntersect( const ray &R, intr_list &Il ) const override
    {
      intr T;
      // Ray leaves sphere behind
      vec3 OC = C - R.Org;
      DBL
        OC2 = OC & OC,
        OK = OC & R.Dir,
        OK2 = OK * OK,
        h2 = R2 - (OC2 - OK2);

      T.Shp = (shape *)this;
      if (OK < 0)
      {
        // Check for ray starts outside sphere
        if (h2 < OK2)
          return 0;
        // Ray starts inside sphere
        T.T = OK + sqrt(h2);
        Il << T;
        return 1;
      }

      // Ray starts before sphere
      if (h2 < Threshold)
        return 0;

      DBL h = sqrt(h2);
      if (h < OK)
      {
        // Ray starts outside sphere
        T.T = OK - h;
        Il << T;
        T.T = OK + h;
        Il << T;
        return 2;
      }
      // Ray starts inside sphere
      T.T = OK + h;
      Il << T;
      return 1;
    } /* End of 'AllIntersect' function */

    /* Check inside of shape point function.
     * ARGUMENTS:
     *   - point:
     *       const vec3 &P;
     * RETURNS:
     *   - (BOOL) TRUE if inside, FALSE otherwise.
     */
    BOOL IsInside( const vec3 &P ) const override
    {
      return ((P - C) & (P - C)) - R2 <= Threshold;
    } /* End of 'IsInside' function */

    /* Check is intersecte or not function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     * RETURNS:
     *   - (BOOL) TRUE if intersect, FALSE otherwise.
     */
    BOOL IsIntersect( const ray &R ) const override
    {
      return TRUE;
    } /* End of 'IsIntersect' function */
  }; /* End of 'sphere' class */
} /* End of 'vart' namespace */

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */

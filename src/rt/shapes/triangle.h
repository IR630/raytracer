/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : triangle.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing triangle handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "rt/rt_def.h"

/* Project namespace */
namespace vart
{
  /* triangle represenation type */
  class triangle : public shape
  {
    vec3 P0, P1, P2; // Vertex of triangle
    vec3 N;          // Normal
    vec3 U1, V1;
    DBL u0, v0;

  public:
    /* Triangle constructor.
     * ARGUMENTS:
     *   - coordinate of triangles vertex:
     *       vec3 v1, v2, v3;
     */
    triangle( vec3 v1, vec3 v2, vec3 v3 ) : P0(v1), P1(v2), P2(v3)
    {
      vec3 s1 = P1 - P0, s2 = P2 - P0;
      U1 = (s1 * (s2 & s2) - s2 * (s1 & s2)) / ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      V1 = (s2 * (s1 & s1) - s1 * (s2 & s1)) / ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1;
      v0 = P0 & V1;
      N = ((P1 - P0) % (P2 - P0)).Normalizing();
    } /* End of 'triangle' contructor */

    /* Triangle constructor.
     * ARGUMENTS:
     *   - coordinate of triangles vertex:
     *       vec3 v1, v2, v3;
     *   - material:
     *       surface s;
     */
    triangle( vec3 v1, vec3 v2, vec3 v3, surface s ) : P0(v1), P1(v2), P2(v3), shape(s)
    {
      vec3 s1 = P1 - P0, s2 = P2 - P0;
      U1 = (s1 * (s2 & s2) - s2 * (s1 & s2)) / ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      V1 = (s2 * (s1 & s1) - s1 * (s2 & s1)) / ((s1 & s1) * (s2 & s2) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1;
      v0 = P0 & V1;
      N = ((P1 - P0) % (P2 - P0)).Normalizing();
    } /* End of 'triangle' contructor */

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
      DBL a = N & R.Dir;

      if (fabs(a) < Threshold)
        return FALSE;

      Intr->T = ((P0 & N) - (N & R.Org)) / a;
      if (Intr->T < Threshold)
        return FALSE;

      Intr->P = R(Intr->T);

      DBL u = (Intr->P & U1) - u0;
      DBL v = (Intr->P & V1) - v0;
      Intr->Shp = (shape *)this;
      if (v >= 0 && u >= 0 && (u + v <= 1))
        return TRUE;
      return FALSE;
    } /* End of 'Intersect' function */

    /* Getting normal function.
      * ARGUMENTS:
      *   - intersection:
      *       const intr *Intr;
      * RETURNS: None.
      */
    VOID GetNormal( intr *Intr ) const override
    {
      Intr->N = N;
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
      DBL a = N & R.Dir;
      intr P;

      if (fabs(a) < Threshold)
        return FALSE;

      P.T = ((P0 & N) - (N & R.Org)) / a;
      if (P.T < Threshold)
        return FALSE;

      P.P = R(P.T);

      DBL u = (P.P & U1) - u0;
      DBL v = (P.P & V1) - v0;
      P.Shp = (shape *)this;
      if (v >= 0 && u >= 0 && (u + v <= 1))
      {
        Il << P;
        return 1;
      }
      return 0;
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
      return (N & (P - P0)) <= Threshold;
    } /* End of 'IsInside' function */
  }; /* End of 'triangle' class */
} /* End of 'vart' namespace */

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */

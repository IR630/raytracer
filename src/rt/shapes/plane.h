/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : plane.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing plane handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_

#include "rt/rt_def.h"

/* Project namespace */
namespace vart
{
  /* Plane representation type */
  class plane : public shape
  {
    vec3 
      P,   // Vector of position
      N;   // Vector of normal
    DBL D; // Plane number const

  public:
    /* plane constructor.
      * ARGUMENTS:
      *   - coordinates of centre plane:
      *       vec3 pos;
      *   - normal;
      *       vec3 n;
      */
    plane( const vec3 &pos, const vec3 &n ) : P(pos), N(n.Normalizing()), D(P & (N.Normalizing()))
    {
    } /* End of 'plane' contructor */

    /* plane constructor.
      * ARGUMENTS:
      *   - coordinates of centre plane:
      *       vec3 pos;
      *   - normal;
      *       vec3 n;
      *   - material:
      *       surface s;
      */
    plane( const vec3 &pos, const vec3 &n, surface s ) : P(pos), N(n.Normalizing()), D(P & (N.Normalizing())), shape(s)
    {
    } /* End of 'plane' contructor */

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
      DBL T;

      if (abs(a) < Threshold)
        return FALSE;

      T = (D - (N & R.Org)) / a;
      if (T < Threshold)
        return FALSE;

      Intr->T = T;
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
      DBL Ta;
      intr T;

      if (abs(a) < Threshold)
        return 0;

      Ta = (D - (N & R.Org)) / a;
      if (Ta < Threshold)
        return 0;

      T.T = Ta;
      T.Shp = (shape *)this;
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
    BOOL IsInside( const vec3 &P1 ) const override
    {
      return (N & (P1 - P)) <= Threshold;
    } /* End of 'IsInside' function */
  }; /* End of 'plane' class */
} /* End of 'vart' namespace */

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */

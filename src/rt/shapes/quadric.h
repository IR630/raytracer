/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : quadric.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing quadric handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __quadric_h_
#define __quadric_h_

#include "rt/rt_def.h"

/* Project namespace */
namespace vart
{
  /* quadric represenation type */
  class quadric : public shape
  {
    DBL 
      A, B, C, D, E, // Coefficients
      F, G, H, I, J;

  public:
    /* Quadric constructor.
     * ARGUMENTS:
     *   - coefficients:
     *       DBL a, b, c, d, e
     *           f, g, h, i, j;
     *   - material:
     *       surface s;
     */
    quadric( DBL a, DBL b, DBL c, DBL d, DBL e, DBL f, DBL g, DBL h, DBL i,  DBL j, surface s ) :A(a), B(b), C(c), D(d), E(e), 
                                                                                                 F(f), G(g), H(h), I(i), J(j), shape(s)
    {
    } /* End of 'quadric' constructor */

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
      DBL a = A * R.Dir.X * R.Dir.X + 
              2 * B * R.Dir.X * R.Dir.Y +
              2 * C * R.Dir.X * R.Dir.Z +
              E * R.Dir.Y * R.Dir.Y +
              2 * F * R.Dir.Y * R.Dir.Z +
              H * R.Dir.Z * R.Dir.Z;

      DBL b = 2 * (A * R.Org.X * R.Dir.X + 
              B * (R.Org.X * R.Dir.Y + R.Dir.X * R.Org.Y) +
              C * (R.Org.X * R.Dir.Z + R.Dir.X * R.Org.Z) + 
              D * R.Dir.X +
              E * R.Org.Y * R.Dir.Y +
              F * (R.Org.Y * R.Dir.Z + R.Dir.Y * R.Org.Z) +
              H * R.Org.Z * R.Dir.Z +
              I * R.Dir.Z);

      DBL c = A * R.Org.X * R.Org.X +
              2 * B * R.Org.X * R.Org.Y +
              2 * C * R.Org.X * R.Org.Z +
              2 * D * R.Org.X +
              E * R.Org.Y * R.Org.Y + 
              2 * F * R.Org.Y * R.Org.Z +
              2 * G * R.Org.Y +
              H * R.Org.Z * R.Org.Z + 
              2 * I * R.Org.Z + J;

      DBL d = sqrtf(b * b - 4 * a * c);
      if (d < 0)
        return FALSE;
      else if (d == 0)
      {
        Intr->Shp = (shape *)this;
        Intr->T = -b / (2 * a);
        Intr->V[0] = R.Org + R.Dir * Intr->T;
        if (Intr->T > 0)
          return TRUE;
        return FALSE;
      }
      else
      {
        DBL t1 = (-b - d) / (2 * a);
        DBL t0 = (-b + d) / (2 * a);
        if (t1 > 0)
        {
          Intr->Shp = (shape *)this;
          Intr->T = t1;
          Intr->V[0] = R.Org + R.Dir * t1;
          return TRUE;
        }
        else if (t0 > 0)
        {
          Intr->Shp = (shape *)this;
          Intr->T = t0;
          Intr->V[0] = R.Org + R.Dir * t0;
          return TRUE;
        }
        return FALSE;
      }
    } /* End of 'Intersect' function */

    /* Getting normal function.
      * ARGUMENTS:
      *   - intersection:
      *       const intr *Intr;
      * RETURNS: None.
      */
    VOID GetNormal( intr *Intr ) const override
    {
      Intr->N = vec3(2 * A * Intr->V[0].X + 2 * B * Intr->V[0].Y + 2 * C * Intr->V[0].Z + 2 * D,
                     2 * E * Intr->V[0].Y + 2 * F * Intr->V[0].Z + 2 * G,
                     2 * H * Intr->V[0].Z + 2 * I).Normalizing();
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
      return FALSE;
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
  }; /* End of 'quadric' class */
} /* End of 'vart' namespace */

#endif /* __quadric_h_ */

/* END OF 'quadric.h' FILE */

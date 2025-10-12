/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : box.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing box handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __box_h_
#define __box_h_

#include "rt/rt_def.h"

/* Project namespace */
namespace vart
{
  /* Box represenation type */
  class box : public shape
  {
  public:
    vec3 P0, P1; // Bound box

    /* box constructor.
      * ARGUMENTS:
      *   - coordinate of angle box:
      *       vec3 pos1;
      *   - coordinates of angle box:
      *       vec3 pos2;
      */
    box( vec3 pos1, vec3 pos2 ) : P0(pos1), P1(pos2)
    {
    } /* End of 'box' contructor */

    /* box constructor.
      * ARGUMENTS:
      *   - coordinate of angle box:
      *       vec3 pos1;
      *   - coordinates of angle box:
      *       vec3 pos2;
      *   - material:
      *       surface s;
      */
    box( vec3 pos1, vec3 pos2, surface s ) : P0(pos1), P1(pos2), shape(s)
    {
    } /* End of 'box' contructor */

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
      DBL tnear = -1, tfar = -1, t;
      INT tnear_no = -1, tfar_no = -1;

      for (INT i = 0; i < 3; i++)
      {
        if (fabs(R.Dir[i]) < Threshold)
        {
          if (R.Org[i] < P0[i] || R.Org[i] > P1[i])
            return FALSE;
        }
        else
        {
          if (R.Dir[i] > Threshold)
          {
            if (R.Org[i] > P1[i])
              return FALSE;
            if (R.Org[i] < P0[i])
            {
              t = (P0[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2 + 0, tnear = t;
            }
            t = (P1[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
          else
          {
            if (R.Org[i] < P0[i])
              return FALSE;
            if (R.Org[i] > P1[i])
            {
              t = (P1[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2 + 0, tnear = t;
            }
            t = (P0[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
        }
      }
      if (tnear_no != -1)
        if (tnear > tfar)
          return FALSE;
        else
        {
          Intr->T = tnear;
          Intr->Shp = (shape *)this;
          Intr->I[0] = tnear_no;
          return TRUE;
        }
      else
      {
        Intr->T = tfar;
        Intr->Shp = (shape *)this;
        Intr->I[0] = tfar_no;
        return TRUE;
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
      static vec3 normals[6]
      {
        vec3(-1, 0 ,0), vec3(1, 0, 0),
        vec3(0, -1 ,0), vec3(0, 1, 0),
        vec3(0, 0, -1), vec3(0, 0, 1)
      };

      Intr->N = normals[Intr->I[0]];
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
      DBL tnear = -1, tfar = -1, t;
      INT tnear_no = -1, tfar_no = -1;

      for (INT i = 0; i < 3; i++)
      {
        if (fabs(R.Dir[i]) < Threshold)
        {
          if (R.Org[i] < P0[i] || R.Org[i] > P1[i])
            return 0;
        }
        else
        {
          if (R.Dir[i] > Threshold)
          {
            if (R.Org[i] > P1[i])
              return 0;
            if (R.Org[i] < P0[i])
            {
              t = (P0[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2 + 0, tnear = t;
            }
            t = (P1[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
          else
          {
            if (R.Org[i] < P0[i])
              return 0;
            if (R.Org[i] > P1[i])
            {
              t = (P1[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2 + 0, tnear = t;
            }
            t = (P0[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
        }
      }

      T.Shp = (shape *)this;
      if (tnear_no != -1)
        if (tnear > tfar)
          return 0;
        else
        {
          T.T = tnear;
          T.I[0] = tnear_no;
          Il << T;
        }
      T.T = tfar;
      T.I[0] = tfar_no;
      Il << T;

      return Il.size();
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
      return (P.X - P0.X >= Threshold && P.X - P1.X < Threshold &&
              P.Y - P0.Y >= Threshold && P.Y - P1.Y < Threshold && 
              P.Z - P0.Z >= Threshold && P.Z - P1.Z < Threshold);
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
  }; /* End of 'box' class */
} /* End of 'vart' namespace */

#endif /* __box_h_ */

/* END OF 'box.h' FILE */

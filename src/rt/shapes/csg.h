/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : csg.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing csg handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __csg_h_
#define __csg_h_

#include "rt/rt_def.h"

/* CSG namespace */
namespace csg
{
  /* Intersection representation type */
  class intersection : public vart::shape
  {
    shape *ShpA, *ShpB; // Two shapes

  public:
    /* Intersetion constructor.
     * ARGUMENTS:
     *   - first shape:
     *       shape *A;
     *   - second shape:
     *       shape *B
     */
    intersection( shape *A, shape *B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'intersection' contructor*/

    /* Intersection detructor */
    ~intersection( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~intersection' destructor */

    /* Intersection function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const vart::ray &R, vart::intr *I ) const override
    {
      vart::intr_list il1, il2;

      if (ShpA->AllIntersect(R, il1) > 0 &&
          ShpB->AllIntersect(R, il2) > 0)
      {
        vart::intr best_in(0, nullptr);
        for (auto &i : il1)
        {
          i.P = R(i.T);
          if (ShpB->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }
        for (auto &i : il2)
        {
          i.P = R(i.T);
          if (ShpA->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }
        *I = best_in;
        return best_in.Shp != nullptr;
      }

      return FALSE;
    } /* End of 'intersect' function */

  }; /* End of 'intersection' class */

  /* Subtrack representation type */
  class subtrack : public vart::shape
  {
  public:
    shape *ShpA, *ShpB; // Two shapes

    /* Intersetion constructor.
     * ARGUMENTS:
     *   - first shape:
     *       shape *A;
     *   - second shape:
     *       shape *B
     */
    subtrack( shape *A, shape *B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'subtrack' contructor*/

    /* Subtrack detructor */
    ~subtrack( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~subtrack' destructor */

    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const vart::ray &R, vart::intr *I ) const override
    {
      vart::intr_list il1, il2;

      ShpA->AllIntersect(R, il1);
      ShpB->AllIntersect(R, il2);

      vart::intr best_in(0, nullptr);
      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P))
          if (best_in.Shp == nullptr || best_in.T > i.T)
            best_in = i;
      }
      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (ShpA->IsInside(i.P))
          if (best_in.Shp == nullptr || best_in.T > i.T)
            best_in = i;
      }
      *I = best_in;
      return best_in.Shp != nullptr;

      return FALSE;
    } /* End of 'Intersect' function */
  }; /* End of 'subtrack' class*/

  /* Clip representation type */
  class clip : public vart::shape
  {
  public:
    shape *ShpA, *ShpB; // Two shapes

    /* Clipping constructor.
     * ARGUMENTS:
     *   - first shape:
     *       shape *A;
     *   - second shape:
     *       shape *B
     */
    clip( shape *A, shape *B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'clip' contructor*/

    /* clip detructor */
    ~clip( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~clip' destructor */

    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const vart::ray &R, vart::intr *I ) const override
    {
      vart::intr_list il1, il2;

      ShpA->AllIntersect(R, il1);

      vart::intr best_in(0, nullptr);
      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P))
          if (best_in.Shp == nullptr || best_in.T > i.T)
            best_in = i;
      }
      *I = best_in;
      return best_in.Shp != nullptr;

      return FALSE;
    } /* End of 'Intersect' function */
  }; /* End of 'clip' class */

  /* Union representation type */
  class myunion : public vart::shape
  {
  public:
    shape *ShpA, *ShpB; // Two shapes

    /* Union constructor.
     * ARGUMENTS:
     *   - first shape:
     *       shape *A;
     *   - second shape:
     *       shape *B
     */
    myunion( shape *A, shape *B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'myunion' contructor*/

    /* union detructor */
    ~myunion( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~myunion' destructor */

    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const vart::ray &R, vart::intr *I ) const override
    {
      vart::intr_list il1, il2;

      ShpA->AllIntersect(R, il1);
      ShpB->AllIntersect(R, il2);

      vart::intr best_in(0, nullptr);
      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (best_in.Shp == nullptr || best_in.T > i.T)
          best_in = i;
      }
      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (best_in.Shp == nullptr || best_in.T > i.T)
          best_in = i;
      }
      *I = best_in;
      return best_in.Shp != nullptr;

      return FALSE;
    } /* End of 'Intersect' function */
  }; /* End of 'myunion' class*/

  /* Merge representation type */
  class merge : public vart::shape
  {
  public:
    shape *ShpA, *ShpB; // Two shapes

    /* Union constructor.
     * ARGUMENTS:
     *   - first shape:
     *       shape *A;
     *   - second shape:
     *       shape *B
     */
    merge( shape *A, shape *B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'merge' contructor*/

    /* Merge detructor */
    ~merge( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~merge' destructor */

    /* Intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const vart::ray &R, vart::intr *I ) const override
    {
      vart::intr_list il1, il2;

      ShpA->AllIntersect(R, il1);
      ShpB->AllIntersect(R, il2);

      vart::intr best_in(0, nullptr);

      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P))
          if (best_in.Shp == nullptr || best_in.T > i.T)
            best_in = i;
      }
      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (!ShpA->IsInside(i.P))
          if (best_in.Shp == nullptr || best_in.T > i.T)
            best_in = i;
      }
      *I = best_in;
      return best_in.Shp != nullptr;

      return FALSE;
    } /* End of 'Intersect' function */
  }; /* End of 'merge' class*/
} /* End of 'csg' namespace */

#endif /* __csg_h_ */

/* END OF 'csg.h' FILE */

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt.cpp
 * PURPOSE     : Ray tracing.
 *               Ray tracing handle default module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include "win/win.h"
#include "frame.h"
#include "lights/lights.h"

/* Project namespace */
namespace vart
{
  /* Declaration class */
  class intr; 
  typedef stock<intr> intr_list;

  /* Shape representation type */
  class shape
  {
  public:
    surface Surf {}; // Surfing
    stock <modifier *> Mods; // Stock of modifiers

    /* Default constructor */
    shape( VOID )
    {
    } /* End of 'shape' constructor */

    /* Shape contructor. 
     * ARGUMENTS:
     *   - surface:
     *       const surface &s;
     */
    shape( surface s ) : Surf(s)
    {
    } /* End of 'shape' constructor */

    /* Operator<< to draw object function.
     * ARGUMENTS:
     *   - modifiers:
     *       modifier *Mod;
     * RETURNS:
     *   - (shape &) result.
     */
    shape & operator<<( modifier *Mod )
    {
      Mods << Mod;
      return *this;
    } /* End of 'operator<<' function */

    /* Shape destructor */
    virtual ~shape( VOID )
    {
      for (auto m : Mods)
        delete m;
    } /* End of '~shape' destructor */

    /* Bool intersection function.
     * ARGUMENTS:
     *   - ray:
     *       const vart::ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURN:
     *   - (BOOL) TRUE if we need to draw, FALSE otherwise.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr ) const
    {
      return 47;
    } /* End of 'Intersect' function */

    /* Getting normal function.
     * ARGUMENTS:
     *   - intersection:
     *       const intr *Intr;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr ) const
    {
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
    virtual INT AllIntersect( const ray &R, intr_list &Il ) const
    {
      return 47;
    } /* End of 'AllIntersect' function */

    /* Check inside of shape point function.
     * ARGUMENTS:
     *   - point:
     *       const vec3 &P;
     * RETURNS:
     *   - (BOOL) TRUE if inside, FALSE otherwise.
     */
    virtual BOOL IsInside( const vec3 &P ) const
    {
      return TRUE;
    } /* End of 'IsInside' function */

    /* Check is intersecte or not function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     * RETURNS:
     *   - (BOOL) TRUE if intersect, FALSE otherwise.
     */
    virtual BOOL IsIntersect( const ray &R ) const
    {
      return TRUE;
    } /* End of 'IsIntersect' function */
  }; /* End of 'shape' class */

  /* Intersection representation type */
  class intr
  {
  public:
    DBL T = 0;     // Intersection ray distance
    shape *Shp {}; // Intersected shape
    vec3 P {};        // Intersection point
    //BOOL IsP;    // Check is intersection point
    vec3 N {};        // Normal at intersection point
    //BOOL IsN;    // Check if normalized

    INT I[8] {};   // Int Addon
    DBL D[8] {};   // Double Addon 
    vec3 V[8] {};  // Vector Addon
  }; /* End of 'intr' class */

  /* Scene representation type */
  class scene
  {
  public:
    // Sync flags
    std::atomic_bool IsRenderActive = FALSE;
    std::atomic_bool IsToBeStop = FALSE;
    std::atomic_bool IsReadyToFinish = TRUE;
    // Store rendering line
    std::atomic_int StartRow = 0;

    stock<shape *> Shapes;   // Shape stock

    INT RecLevel = 0, MaxRecLevel = 4;          // Recursive levels
    envi Air = {1, 0};                          // Air environment
    vec3 
      AmbientColor = vec3(0.3, 0.3, 0.3),       // Ambient color
      BackgroundColor = vec3(0.01, 0.01, 0.01); // Background color
    DBL ColorThreshold = 0.0039;                // Treshod of color

    stock<light *> Lights; // Stock of lights

    /* Add to light scene operator function.
     * ARGUMENTS:
     *   - light:
     *       light *Lgh;
     * RETURNS: 
     *   - (scene &) result scene.
     */
    scene & operator<<( light *Lgh )
    {
      Lights << Lgh;
      return *this;
    } /* End of 'operator<<' function */

    /* Scene destructor */
    ~scene( VOID )
    {
      for (auto x : Shapes)
        delete x;
      for (auto x : Lights)
        delete x;
    } /* End of '~scene' destructor */

    /* Operator<< to draw object function.
     * ARGUMENTS:
     *   - shape *Shp;
     *       shape *Shp;
     * RETURNS:
     *   - (scene &) result.
     */
    scene & operator<<( shape *Shp )
    {
      Shapes << Shp;
      return *this;
    } /* End of 'operator<<' function */

    /* Render scene function.
     * ARGUMENTS:
     *   - camera:
     *       camera &Cam;
     *    - frame:
     *        frame &Frm;
     * RETURNS: None.
     */
    VOID Render( camera &Cam, frame &Frm );

    /* Tracing ray function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - environments:
     *       const envi &Media;
     *   - weight:
     *       DBL Weight;
     *   - recursive level:
     *       INT RecLevel;
     * RETURNS:
     *   - (vec3) result ray.
     */
    vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel );

    /* Shade function.
     * ARGUMENTS:
     *   - vector:
     *       const vec3 &V;
     *   - environment:
     *       const envi &Media;
     *   - recursive level:
     *       INT RecLevel;
     *   - shade parameters:
     *       shade_info si;
     * RETURNS:
     *   - (vec3) result vector.
     */
    vec3 Shade( const vec3 &V, const envi &Media, intr *I, DBL Weight, INT RecLevel, shade_info si );

    /* Bool intersection function.
     * ARGUMENTS:
     *   - ray:
     *       const vart::ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURN:
     *   - (BOOL) TRUE if we need to draw, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intr *Intr ) const
    {
      intr best_intr;
      best_intr.T = -1;

      for (auto shp : Shapes )
      {
        intr current_intr;
        Intr->Shp = (shape *)this;
        if (shp->Intersect(R, &current_intr) &&
            (best_intr.T == -1 || current_intr.T < best_intr.T))
          best_intr = current_intr;
      }
      if (best_intr.T == -1)
        return FALSE;
      *Intr = best_intr;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Getting number of all intersect function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - list:
     *       intr_list *Il;
     * RETURNS:
     *   - (INT) result number of all intersect.
     */
    INT AllIntersect( const ray &R, intr_list *Il ) const
    {
      intr in;
      for (auto shd : Shapes )
      {
        if (shd->Intersect(R, &in))
          *Il << (in);
      }
      return (*Il).size();
    } /* End of 'AllIntersect' function */
  }; /* End of 'scene' class */
} /* End of 'vart' namespace */

#endif /* __rt_def_h_ */

/* END OF 'rt_def.h' FILE */

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_scene.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing scene handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_scene_h_
#define __rt_scene_h_

#include "rt_def.h"

#if 0
/* Project namespace */
namespace vart
{
  /* Scene representation type */
  class scene
  {
  public:
    stock<shape *> Shapes; // Shape stock

    /* Intersection function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Intersect( const ray &R, intr *Intr );

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
     *       const camera &Cam;
     *    - frame:
     *        frame &Frm;
     * RETURNS: None.
     */
    VOID Render( const camera &Cam, frame &Frm );

    /* Tracing ray function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     * RETURNS:
     *   - (vec3) result ray.
     */
    vec3 Trace( const ray &R );

    /* Shade function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &R;
     *   - intersection:
     *       intr *Intr;
     * RETURNS:
     *   - (vec3) result vector.
     */
    vec3 Shade( const ray &R, intr *In );

  }; /* End of 'scene' class */
} /* End of 'vart' namespace */
#endif /* 0 */

#endif /* __rt_scene_h_ */

/* END OF 'rt_scene.h' FILE */

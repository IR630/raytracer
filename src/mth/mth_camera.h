/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth.h
 * PURPOSE     : Ray tracing.
 *               Camera math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename Type>
    class camera
    {
    public:
      vec3<Type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point
      Type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
      INT
        FrameW, FrameH; // camera frame size in pixels
      matr<Type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production

      /* Camera default constructor.
       * ARGUMENTS: None.
       */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      } /* End of 'camera' constructor */

      /* Ray tracing frame function.
       * ARGUMENTS:
       *   - coordinates:
       *       Type Xs, Ys;
       * RETURNS:
       *   - (ray) result vector.
       */
      ray<Type> FrameRay( Type Xs, Type Ys ) const
      {
        vec3<Type> Q =
          Dir * ProjDist +
          Right * ((Xs - FrameW / 2) * Wp / FrameW) +
          Up * ((FrameH / 2 - Ys) * Hp / FrameH);

        return ray<Type>(Loc + Q, Q);
      } /* End of 'FrameRay' function */

      /* Camera setting projection function.
       * ARGUMENTS:
       *   - new projection size:
       *       Type NewSize;
       *   - new projection distance:
       *       Type NewProjDist;
       *   - new far clip:
       *       Type NewFarClip;
       * RETURNS:
       *   - (camera &) result camera projection.
       */
      camera & SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
      {
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;

        UpdateProj();
        return *this;
      } /* End of 'SetProj' function */

      /* Resize projection function. 
       * ARGUMENTS:
       *   - new frame width and height:
       *       INT NewFrameW, NewFrameH;
       * RETURNS:
       *   - (camera &) result camera projection.
       */
      camera & Resize( INT NewFrameW, INT NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;

        UpdateProj();
        return *this;
      } /* End of 'Resize' function */

      /* Setting location camera function. 
       * ARGUMENTS:
       *   - new vector location:
       *       const vec3<Type> &L;
       *   - new vector at:
       *       const vec3<Type> &A;
       *   - new vector up:
       *       const vec3<Type> &U;
       * RETURNS:
       *   - (camera &) result camera projection.
       */
      camera & SetLocAtUp( const vec3<Type> &L, const vec3<Type> &A, const vec3<Type> &U = vec3<Type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;

        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;

        UpdateProj();
        return *this;
      } /* End of 'SetLocAtUp' function */

    private:
      /* Update projection function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        Type rx = Size / 2, ry = Size / 2;

        if (FrameW > FrameH)
          rx *= (Type)FrameW / FrameH;
        else
          ry *= (Type)FrameH / FrameW;
        Wp = rx * 2;
        Hp = ry * 2;
        // Proj = matr<Type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
      } /* End of 'UpdateProj' function */
     }; /* End of 'camera' class */
} /* End of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */

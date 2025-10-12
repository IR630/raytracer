/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Ray tracing.
 *               Matrix math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* Matrix representation type */
  template<typename Type>
    class matr
    {
    private:
      Type M[4][4] {};                 // Matrix
      mutable Type InvM[4][4];         // Inverse field of matrix
      mutable BOOL IsInverseEvaluated; // Flag of inverse matrix

    public:

      /* Inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID EvaluatedInverseMatrix( VOID ) const
      {
        if (IsInverseEvaluated)
          return;
        IsInverseEvaluated = TRUE;

        DBL det = Determ();

        if (det == 0)
        {
          InvM = Identity();
          return;
        }

        /* build adjoint matrix */
        InvM[0][0] =
          +MatrDeterm3x3(M[1][1], M[1][2], M[1][3],
                         M[2][1], M[2][2], M[2][3],
                         M[3][1], M[3][2], M[3][3]) / det;
 
        InvM[1][0] =
          -MatrDeterm3x3(M[1][0], M[1][2], M[1][3],
                         M[2][0], M[2][2], M[2][3],
                         M[3][0], M[3][2], M[3][3]) / det;
 
        InvM[2][0] =
          +MatrDeterm3x3(M[1][0], M[1][1], M[1][3],
                         M[2][0], M[2][1], M[2][3],
                         M[3][0], M[3][1], M[3][3]) / det;
 
        InvM[3][0] =
          -MatrDeterm3x3(M[1][0], M[1][1], M[1][2],
                         M[2][0], M[2][1], M[2][2],
                         M[3][0], M[3][1], M[3][2]) / det;
 
        InvM[0][1] =
          -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                         M[2][1], M[2][2], M[2][3],
                         M[3][1], M[3][2], M[3][3]) / det;
 
        InvM[1][1] =
          +MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                         M[2][0], M[2][2], M[2][3],
                         M[3][0], M[3][2], M[3][3]) / det;
 
        InvM[2][1] =
          -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                         M[2][0], M[2][1], M[2][3],
                         M[3][0], M[3][1], M[3][3]) / det;
 
        InvM[3][1] =
          +MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                         M[2][0], M[2][1], M[2][2],
                         M[3][0], M[3][1], M[3][2]) / det;
 
 
        InvM[0][2] =
          +MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                         M[1][1], M[1][2], M[1][3],
                         M[3][1], M[3][2], M[3][3]) / det;
 
        InvM[1][2] =
          -MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                         M[1][0], M[1][2], M[1][3],
                         M[3][0], M[3][2], M[3][3]) / det;
 
        InvM[2][2] =
          +MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                         M[1][0], M[1][1], M[1][3],
                         M[3][0], M[3][1], M[3][3]) / det;
 
        InvM[3][2] =
          -MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                         M[1][0], M[1][1], M[1][2],
                         M[3][0], M[3][1], M[3][2]) / det;
 
 
        InvM[0][3] =
          -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                         M[1][1], M[1][2], M[1][3],
                         M[2][1], M[2][2], M[2][3]) / det;
 
        InvM[1][3] =
          +MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                         M[1][0], M[1][2], M[1][3],
                         M[2][0], M[2][2], M[2][3]) / det;
 
        InvM[2][3] =
          -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                         M[1][0], M[1][1], M[1][3],
                         M[2][0], M[2][1], M[2][3]) / det;
 
        InvM[3][3] =
          +MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                         M[1][0], M[1][1], M[1][2],
                         M[2][0], M[2][1], M[2][2]) / det;
      } /* End of 'EvaluatedInverseMatrix' function */

      /* Default constructor of matrix. */
      matr<Type>( VOID ) : IsInverseEvaluated(FALSE)
      {
      } /* End of 'matr' constructor */

      /* Constructor of matrix.
       * ARGUMENTS:
       *   - components of matrix:
       *       Type a00, Type a01, Type a02, Type a03
       *       Type a10, Type a11, Type a12, Type a13
       *       Type a20, Type a21, Type a22, Type a23
       *       Type a30, Type a31, Type a32, Type a33
       */
      matr<Type>( Type a00, Type a01, Type a02, Type a03,
                  Type a10, Type a11, Type a12, Type a13,
                  Type a20, Type a21, Type a22, Type a23,
                  Type a30, Type a31, Type a32, Type a33 ) : 
        M {
            {a00, a01, a02, a03},
            {a10, a11, a12, a13},
            {a20, a21, a22, a23}, 
            {a30, a31, a32, a33}
        }
      {
      } /* End of 'matr' constructor */

      /* Constructor massive to matrix.
       * ARGUMENTS:
       *   - massive:
       *       Type A[4][4];
       */
      matr<Type>( Type A[4][4] ) :
        M {
          {A[0][0], A[0][1], A[0][2], A[0][3]},
          {A[1][0], A[1][1], A[1][2], A[1][3]},
          {A[2][0], A[2][1], A[2][2], A[2][3]},
          {A[3][0], A[3][1], A[3][2], A[3][3]},
        }
      {
      } /* End of 'matr' constructor */

      /* Operator* to multiply matrix by matrix function.
       * ARGUMENTS:
       *   - matrix to multiply:
       *       matr<Type> A;
       * RETURNS:
       *   - (matr<Type>) result matrix.
       */
      matr<Type> operator*( matr<Type> A )
      {
        matr<Type> r = {};

        r.M[0][0] = M[0][0] * A.M[0][0] +
                    M[0][1] * A.M[1][0] +
                    M[0][2] * A.M[2][0] +
                    M[0][3] * A.M[3][0];
        r.M[0][1] = M[0][0] * A.M[0][1] +
                    M[0][1] * A.M[1][1] +
                    M[0][2] * A.M[2][1] +
                    M[0][3] * A.M[3][1];
        r.M[0][2] = M[0][0] * A.M[0][2] +
                    M[0][1] * A.M[1][2] +
                    M[0][2] * A.M[2][2] +
                    M[0][3] * A.M[3][2];
        r.M[0][3] = M[0][0] * A.M[0][3] +
                    M[0][1] * A.M[1][3] +
                    M[0][2] * A.M[2][3] +
                    M[0][3] * A.M[3][3];
        r.M[0][4] = M[0][0] * A.M[0][4] +
                    M[0][1] * A.M[1][4] +
                    M[0][2] * A.M[2][4] +
                    M[0][3] * A.M[3][4];
        r.M[1][0] = M[1][0] * A.M[0][0] +
                    M[1][1] * A.M[1][0] +
                    M[1][2] * A.M[2][0] +
                    M[1][3] * A.M[3][0];
        r.M[1][1] = M[1][0] * A.M[0][1] +
                    M[1][1] * A.M[1][1] +
                    M[1][2] * A.M[2][1] +
                    M[1][3] * A.M[3][1];
        r.M[1][2] = M[1][0] * A.M[0][2] +
                    M[1][1] * A.M[1][2] +
                    M[1][2] * A.M[2][2] +
                    M[1][3] * A.M[3][2];
        r.M[1][3] = M[1][0] * A.M[0][3] +
                    M[1][1] * A.M[1][3] +
                    M[1][2] * A.M[2][3] +
                    M[1][3] * A.M[3][3];
        r.M[2][0] = M[2][0] * A.M[0][0] +
                    M[2][1] * A.M[1][0] +
                    M[2][2] * A.M[2][0] +
                    M[2][3] * A.M[3][0];
        r.M[2][1] = M[2][0] * A.M[0][1] +
                    M[2][1] * A.M[1][1] +
                    M[2][2] * A.M[2][1] +
                    M[2][3] * A.M[3][1];
        r.M[2][2] = M[2][0] * A.M[0][2] +
                    M[2][1] * A.M[1][2] +
                    M[2][2] * A.M[2][2] +
                    M[2][3] * A.M[3][2];
        r.M[2][3] = M[2][0] * A.M[0][3] +
                    M[2][1] * A.M[1][3] +
                    M[2][2] * A.M[2][3] +
                    M[2][3] * A.M[3][3];
        r.M[3][0] = M[3][0] * A.M[0][0] +
                    M[3][1] * A.M[1][0] +
                    M[3][2] * A.M[2][0] +
                    M[3][3] * A.M[3][0];
        r.M[3][1] = M[3][0] * A.M[0][1] +
                    M[3][1] * A.M[1][1] +
                    M[3][2] * A.M[2][1] +
                    M[3][3] * A.M[3][1];
        r.M[3][2] = M[3][0] * A.M[0][1] +
                    M[3][1] * A.M[1][1] +
                    M[3][2] * A.M[2][1] +
                    M[3][3] * A.M[3][1];
        r.M[3][3] = M[3][0] * A.M[0][3] +
                    M[3][1] * A.M[1][3] +
                    M[3][2] * A.M[2][3] +
                    M[3][3] * A.M[3][3];

        return r;
      } /* End of 'operator*' function */

      /* Identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (matr<Type>) result matrix
       */
      static matr<Type> Identity( VOID )
      {
        return matr<Type>(1, 0, 0, 1,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Matr translate function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &T;
       * RETURNS:
       *   - (matr<Type>) result matr
       */
      static matr<Type> Translate( const vec3<Type> &T )
      {
        return matr<Type>(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            T.X, T.Y, T.Z, 1);
      } /* End of 'Translate' function */

      /* Matrix scale function.
       * ARGUMENTS:
       *   - any vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> Scale( const vec3<Type> &V )
      {
        return matr<Type>(
            V.X, 0, 0, 0,
            0, V.Y, 0, 0,
            0, 0, V.Z, 0,
            0, 0,   0, 1);
        } /* End of 'Scale' function */

      /* Matrix rotate relative X function.
       * ARGUMENTS:
       *   - angle in degree:
       *       Type A;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> RotateX( Type A )
      {
        Type ar = D2R(A);

        return matr<Type>(
            1,       0,        0,   0,
            0,  cos(ar), sin(ar), 0,
            0, -sin(ar), cos(ar), 0,
            0,        0,       0, 1);
      } /* End of 'RotateX' function */

      /* Matrix rotate relative Y function.
       * ARGUMENTS:
       *   - angle in degree:
       *       Type A;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> RotateY( Type A )
      {
        Type ar = D2R(A);

        return matr<Type>(
            cos(ar), 0, -sin(ar), 0,
                  0, 1,        0, 0,
            sin(ar), 0,  cos(ar), 0,
                  0, 0,        0, 1);
      } /* End of 'RotateY' function */

      /* Matrix rotate relative Z function
       * ARGUMENTS:
       *   - angle in degree:
       *       Type A;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> RotateZ( Type A )
      {
        Type ar = D2R(A);

        return matr<Type>(
             cos(ar), sin(ar), 0, 0,
            -sin(ar), cos(ar), 0, 0,
                   0,       0, 1, 0,
                   0,       0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Matrix rotate relative vector function
       * ARGUMENTS:
       *   - angle in degree:
       *       Type A;
       *   - Vector:
       *       const vec3<Type> &R;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      matr<Type> Rotate( Type A, const vec3<Type> &R ) const
      {
        Type
          An = D2R(A),
          si = sin(An), co = cos(An);
        vec3 V = R.Normalizing;

        return matr<Type>(
            co + V.X * V.X * (1 - co), V.X * V.Y * (1 - co) + V.Z * si, V.X * V.Z * (1 - co) - V.Y * si, 0,
            V.Y * V.X * (1 - co) - V.Z * si, co + V.Y * V.Y * (1 - co), V.Y * V.Z * (1 - co) + V.X * si, 0,
            V.Z * V.X * (1 - co) + V.Y * si, V.Z * V.Y * (1 - co) - V.X * si, co + V.Z * V.Z * (1 - co), 0,
            0, 0, 0, 1);
      } /* End of 'Rotate' function */

      /* Matrix transposition function
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<Type>) result matrix.
       */
      matr<Type> Transpose( VOID ) const
      {
        return matr<Type>(M[0][0], M[1][0], M[2][0], M[3][0], 
                          M[0][1], M[1][1], M[2][1], M[3][1], 
                          M[0][2], M[1][2], M[2][2], M[3][2], 
                          M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transpose' function */

      /* Vector by matrix multiplication (with homogenious devide) function.
       * ARGUMENTS:
       *   - source vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> MulVec( const vec3<Type> &V ) const
      {
        Type w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];
 
        return vec3<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w,
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w,
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w);
      } /* End of 'MulVec' function */

      /* Matrix (3x3) determined function.
       * ARGUMENTS:
       *   - value elements of matrix:
       *       Type A11, A12, A13,
       *            A21, A22, A23
       *            A31, A32, A33;
       * RETURNS:
       *   (Type) determination of matrix.
       */
      static Type Determ3x3( Type A11, Type A12, Type A13,
                             Type A21, Type A22, Type A23,
                             Type A31, Type A32, Type A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'Determ3x3' function */

      /* Determined by matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) determination of matrix.
       */
      Type Determ( VOID ) const
      {
        return (
          +M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                               M[2][1], M[2][2], M[2][3],
                               M[3][1], M[3][2], M[3][3]) +
          -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                               M[2][0], M[2][2], M[2][3],
                               M[3][0], M[3][2], M[3][3]) +
          +M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                               M[2][0], M[2][1], M[2][3],
                               M[3][0], M[3][1], M[3][3]) +
          -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                               M[2][0], M[2][1], M[2][2],
                               M[3][0], M[3][1], M[3][2]));
      } /* End of 'Determ' function */

      /* View frustum function.
       * ARGUMENTS:
       *   - Type arguments:
       *       Type l, r, b, t, n, f;
       * RETURNS:
       *   - (matr<Type>) result matrix.
       */
      static matr<Type> Frustum( Type l, Type r, Type b, Type t, Type n, Type f )
      {
        return matr<Type>(
            2 * n / (r - l), 0, 0, 0,
            0, 2 * n / (t - b), 0, 0,
            (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
            0, 0, -2 * n * f / (f - n), 0);
      } /* End of 'Frustum' function */

      /* Matr ortho function.
       * ARGUMENTS:
       *   - parameters of draw:
       *       Type Left, Right, Bottom, Top, Near, Far;
       * RETURNS:
       *   - (matr<Type>) result matr.
       */
      static matr<Type> Ortho( Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far )
      {
        return matr<Type>(
            2 / (Right - Left), 0, 0, 0,
            0, 2 / (Top - Bottom), 0, 0,
            0, 0, -2 /(Far - Near), 0,
            -(Right + Left) / (Right + Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1);
      } /* End of 'Ortho' function */

      /* Matrix look-at viewer setup function.
       * ARGUMENTS:
       *   - viewer position, look-at point, approximate up direction:
       *       vec3 Loc, At, Up;
       * RETURNS:
       *   (matr<Type>) result matrix.
       */
      static matr<Type> View( vec3<Type> Loc, vec3<Type> At, vec3<Type> Up )
      {
        vec3<Type> 
          Dir = (At - Loc).Normalizing(),
          Right = (Dir % Up).Normalizing(),
          Up = (Right % Dir).Normalizing();

        return matr<Type>(
            Right.X, Up.X, -Dir.X, 0, 
            Right.Y, Up.Y, -Dir.Y, 0,
            Right.Z, Up.Z, -Dir.Z, 0,
            -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
      } /* End of 'View' function */
    }; /* End of 'matr' class */
} /* End of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray tracing.
 *               4D vector math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec4
    {
      // template<typename Type1>
        // friend class matr<Type1>;
    public:
      Type X, Y, Z, W;

      /* Default constructor of vec4.
       * ARGUMENTS: None.
       */
      vec4( VOID ) : X({}), Y({}), Z({}), W({})
      {
      } /* End of 'vec4' constructor */

      /* Constructor of vec4 of 3 component.
       * ARGUMENTS:
       *   - new x, y, z, w:
       *       Type x, y, z;
       */
      vec4( Type x, Type y, Type z, Type w ) : X(x), Y(y), Z(z), W(w)
      {
      } /* End of 'vec4' constructor */

      /* Costructor of vec4 of one component.
       * ARGUMENTS:
       *   - new a:
       *       Type a;
       */
      explicit vec4( Type a ) : X(a), Y(a), Z(a), W(a)
      {
      } /* End of 'vec4' constructor */

      /* Operator+ to sum vectors function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 operator+( const vec4 &V ) const
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Operator- to negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec4) lenght.
       */
      vec4 operator-( VOID ) const
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Operator- to negative vector function.
       * ARGUMENTS:
       *   - vector to neg:
       *       const vec4 &V;
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Operator* to multiply vectors function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec4 &V;
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      } /* End of 'operator*' function */

      /* Operator* to multiply vector by number function.
       * ARGUMENTS:
       *   - number to multiply:
       *       Type A;
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 operator*( Type A ) const
      {
        return vec4(X * A, Y * A, Z * A, W * A);
      } /* End of 'operator*' function */

      /* Operator* to multiply vectors function.
       * ARGUMENTS:
       *   - vector devide:
       *       Type A;
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 operator/( Type A ) const
      {
        return vec4(X / A, Y / A, Z / A);
      } /* End of 'operator/' function */

      /* Operator! to count length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (Type) length.
       */
      Type operator!( VOID ) const
      {
        Type len = *this & *this;

        return len;
      } /* End of 'operator!' function */

      /* Operator& to vec4 dot vec4 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS:
       *   - (Type) result number;
       */
      Type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
      } /* End of 'operator&' function */

      /* Square length of vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (Type) result length.
       */
      Type Length2( VOID ) const
      {
        DBL len = *this & *this;

        return len;
      } /* End of 'Length2' function */

      /* Operator+= add vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS:
       *   - (vec4 &) result vector.
       */
      vec4 & operator+=( const vec4 &V )
      {
        *this = *this + V;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator-= negative vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS:
       *   - (vec4 &) result vector.
       */
      vec4 & operator-=( const vec4 &V )
      {
        *this = *this - V;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator*= multiply vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &V;
       * RETURNS:
       *   - (vec4 &) result vector.
       */
      vec4 & operator*=( const vec4 &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator*= multiply vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec4 &) result vector.
       */
      vec4 & operator*=( Type A )
      {
        *this = *this * A;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator/= devide vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec4 &) result vector.
       */
      vec4 & operator/=( Type A )
      {
        *this = *this / A;

        return *this;
      } /* End of 'operator/=' function */

      /* Zero vector function. 
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec4) result vector.
       */
      vec4 & Zero( VOID )
      {
        X = 0, Y = 0, Z = 0, W = 0;

        return *this;
      } /* End of 'Zero' function */

    private:
      /* Random numbers from 0 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (Type) result number
       */
      static Type rnd0( VOID ) 
      {
        return (Type)rand() / RAND_MAX;;
      } /* End of 'rnd0' function */

      /* Random numbers from -1 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (Type) result number
       */
      static Type rnd1( VOID ) 
      {
        return (Type)rand() / RAND_MAX * 2 - 1;
      } /* End of 'rnd1' function */

    public:
      /* Vector with random components from 0 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec4 &) result number
       */
      vec4 & Rnd0( VOID )
      {
        X = rnd0(), Y = rnd0(), Z = rnd0(), W = rnd0();

        return *this;
      } /* End of 'Rnd0' function */

      /* Vector with random components from -1 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec4 &) result number
       */
      vec4 & Rnd1( VOID )
      {
        X = rnd1(), Y = rnd1(), Z = rnd1(), W = rnd1();

        return *this;
      } /* End of 'Rnd1' function */

      /* Distance between 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec4 &P;
       * RETURNS:
       *   - (Typ) distance.
       */
      Type Distance( const vec4 &P )
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Normalize vec4 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec4) result vec4;
       */
      vec4 & Normalize( VOID )
      {
        *this /= !*this;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vec4 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec4) new result vector;
       */
      vec4 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

    }; /* End of 'vec4' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */

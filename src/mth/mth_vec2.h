/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray tracing.
 *               2D vector math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec2
    {
    public:
      Type X, Y;

      /* Default constructor of vec2.
       * ARGUMENTS: None.
       */
      vec2<Type>( VOID ) : X({}), Y({})
      {
      } /* End of 'vec2' constructor */

      /* Constructor of vec2 of 2 component.
       * ARGUMENTS:
       *   - new x, y, z:
       *       Type x, y;
       */
      vec2<Type>( Type x, Type y ) : X(x), Y(y)
      {
      } /* End of 'vec2' constructor */

      /* Costructor of vec2 of one component.
       * ARGUMENTS:
       *   - new a:
       *       Type a;
       */
      explicit vec2<Type>( Type a ) : X(a), Y(a)
      {
      } /* End of 'vec2' constructor */

      /* Operator+ to sum vectors function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec2) result vector.
       */
      vec2<Type> operator+( const vec2 &V ) const
      {
        return vec2<Type>(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Operator- to negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec2<Type>) lenght.
       */
      vec2<Type> operator-( VOID ) const
      {
        return vec2<Type>(-X, -Y);
      } /* End of 'operator-' function */

      /* Operator- to negative vector function.
       * ARGUMENTS:
       *   - vector to neg:
       *       const vec2 &V;
       * RETURNS:
       *   - (vec2<Type>) result vector.
       */
      vec2<Type> operator-( const vec2 &V ) const
      {
        return vec2<Type>(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Operator* to multiply vectors function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec2 &V;
       * RETURNS:
       *   - (vec2<Type>) result vector.
       */
      vec2<Type> operator*( const vec2 &V ) const
      {
        return vec2<Type>(X * V.X, Y * V.Y);
      } /* End of 'operator*' function */

      /* Operator* to multiply vector by number function.
       * ARGUMENTS:
       *   - number to multiply:
       *       Type A;
       * RETURNS:
       *   - (vec2<Type>) result vector.
       */
      vec2<Type> operator*( Type A ) const
      {
        return vec2<Type>(X * A, Y * A);
      } /* End of 'operator*' function */

      /* Operator* to multiply vectors function.
       * ARGUMENTS:
       *   - vector devide:
       *       Type A;
       * RETURNS:
       *   - (vec2) result vector.
       */
      vec2 operator/( Type A ) const
      {
        return vec2(X / A, Y / A);
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

      /* Operator& to vec2 dot vec2 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   - (Type) result number;
       */
      Type operator&( const vec2 &V ) const
      {
        return X * V.X + Y * V.Y;
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
       *       const vec2 &V;
       * RETURNS:
       *   - (vec2 &) result vector.
       */
      vec2 & operator+=( const vec2 &V )
      {
        *this = *this + V;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator-= negative vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   - (vec2 &) result vector.
       */
      vec2 & operator-=( const vec2 &V )
      {
        *this = *this - V;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator*= multiply vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &V;
       * RETURNS:
       *   - (vec2 &) result vector.
       */
      vec2 & operator*=( const vec2 &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator*= multiply vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec2 &) result vector.
       */
      vec2 & operator*=( Type A )
      {
        *this = *this * A;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator/= devide vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec2 &) result vector.
       */
      vec2 & operator/=( Type A )
      {
        *this = *this / A;

        return *this;
      } /* End of 'operator/=' function */

      /* Zero vector function. 
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec2) result vector.
       */
      vec2 & Zero( VOID )
      {
        X = 0, Y = 0;

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
       *   - (vec2 &) result number
       */
      vec2 & Rnd0( VOID )
      {
        X = rnd0(), Y = rnd0();

        return *this;
      } /* End of 'Rnd0' function */

      /* Vector with random components from -1 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec2 &) result number
       */
      vec2 & Rnd1( VOID )
      {
        X = rnd1(), Y = rnd1();

        return *this;
      } /* End of 'Rnd1' function */

      /* Distance between 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &P;
       * RETURNS:
       *   - (Type) distance.
       */
      Type Distance( const vec2 &P )
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Normalize vec2 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec2) result vec2;
       */
      vec2 & Normalize( VOID )
      {
        *this /= !*this;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vec2 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec2) new result vector;
       */
      vec2 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

    }; /* End of 'vec2' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */

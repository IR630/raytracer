/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray tracing.
 *               3D vector math handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"
#include "stdlib.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec3
    {
      // friend class matr<Type>;
    public:
      Type X {}, Y {}, Z {};

      /* Default constructor of vec3. */
      vec3<Type>( VOID )
      {
      } /* End of 'vec3' constructor */

      /* Constructor of vec3 of 3 component.
       * ARGUMENTS:
       *   - new x, y, z:
       *       Type x, y, z;
       */
      vec3<Type>( Type x, Type y, Type z ) : X(x), Y(y), Z(z)
      {
      } /* End of 'vec3' constructor */

      /* Costructor of vec3 of one component.
       * ARGUMENTS:
       *   - new a:
       *       Type a;
       */
      explicit vec3<Type>( Type a ) : X(a), Y(a), Z(a)
      {
      } /* End of 'vec3' constructor */

      /* Operator+ to sum vector and number function.
       * ARGUMENTS:
       *   - number:
       *       DBL A;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator+( DBL A ) const
      {
        return vec3<Type>(X + A, Y + A, Z + A);
      } /* End of 'operator+' function */

      /* Operator+ to subtrac vector and number function.
       * ARGUMENTS:
       *   - number:
       *       DBL A;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator-( DBL A ) const
      {
        return vec3<Type>(X - A, Y - A, Z - A);
      } /* End of 'operator-' function */

      /* Operator* to multiply vector by number function.
       * ARGUMENTS:
       *   - number to multiply:
       *       Type A;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator*( Type A ) const
      {
        return vec3<Type>(X * A, Y * A, Z * A);
      } /* End of 'operator*' function */

      /* Operator/ to devide vector by number function.
       * ARGUMENTS:
       *   - number to multiply:
       *       Type A;
       * RETURNS:
       *   - (vec3<Type>) result vector.
       */
      vec3<Type> operator/( Type A ) const
      {
        return vec3<Type>(X / A, Y / A, Z / A);
      } /* End of 'operator/' function */

      /* Operator- to negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec3) lenght.
       */
      vec3<Type> operator-( VOID ) const
      {
        return vec3<Type>(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Operator+ to sum vectors function.
       * ARGUMENTS:
       *   - vector to sum:
       *       const vec3<Type> &V;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator+( const vec3<Type> &V ) const
      {
        return vec3<Type>(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Operator- to negative vector function.
       * ARGUMENTS:
       *   - vector to neg:
       *       const vec3<Type> &V;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator-( const vec3<Type> &V ) const
      {
        return vec3<Type>(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Operator* to multiply vectors function.
       * ARGUMENTS:
       *   - vector to multiply:
       *       const vec3<Type> &V;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator*( const vec3<Type> &V ) const
      {
        return vec3<Type>(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* Operator/ to devide vectors function.
       * ARGUMENTS:
       *   - vector devide:
       *       const vec3<Type> &V;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator/( const vec3<Type> &V ) const
      {
        return vec3<Type>(X / V.X, Y / V.Y, Z / V.Z);
      } /* End of 'operator/' function */

      /* Operator! to count length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (Type) length.
       */
      Type operator!( VOID ) const
      {
        Type len = *this & *this;

        if (len != 0 && len != 1)
          return sqrtf(len);

        return len;
      } /* End of 'operator!' function */

      /* Operator& to vec3 dot vec3 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (Type) result number;
       */
      Type operator&( const vec3<Type> &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Operator% vec cross vec function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (vec3) result vector.
       */
      vec3<Type> operator%( const vec3<Type> &V ) const
      {
        return vec3<Type>(Y * V.Z - Z * V.Y,
                          Z * V.X - X * V.Z,
                          X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

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

      /* Operator+= add vector by number function. 
       * ARGUMENTS:
       *   - number:
       *       DBL V;
       * RETURNS:
       *   - (vec3<Type> &) result vector.
       */
      vec3<Type> & operator+=( Type A )
      {
        *this = (*this + A);

        return *this;
      } /* End of 'operator+=' function */

      /* Operator+= subtract vector by number function. 
       * ARGUMENTS:
       *   - number:
       *       DBL V;
       * RETURNS:
       *   - (vec3<Type> &) result vector.
       */
      vec3<Type> & operator-=( Type A )
      {
        *this = (*this + A);

        return *this;
      } /* End of 'operator-=' function */

      /* Operator*= multiply vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator*=( Type A )
      {
        *this = *this * A;

        return *this;
      } /* End of 'operator*=' function */

      /* Operator/= devide vector by number function. 
       * ARGUMENTS:
       *   - multiplying number:
       *       Type A;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator/=( Type A )
      {
        *this = *this / A;

        return *this;
      } /* End of 'operator/=' function */

      /* Operator+= add vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator+=( const vec3<Type> &V )
      {
        *this = *this + V;

        return *this;
      } /* End of 'operator+=' function */

      /* Operator-= negative vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator-=( const vec3<Type> &V )
      {
        *this = *this - V;

        return *this;
      } /* End of 'operator-=' function */

      /* Operator/= devide vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator/=( const vec3<Type> &V )
      {
        *this = *this - V;

        return *this;
      } /* End of 'operator/=' function */

      /* Operator*= multiply vector by vector function. 
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   - (vec3 &) result vector.
       */
      vec3<Type> & operator*=( const vec3<Type> &V )
      {
        *this = *this * V;

        return *this;
      } /* End of 'operator*=' function */

      /* Zero vector function. 
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec3<Type>) result vector.
       */
      static vec3<Type> Zero( VOID )
      {
        return vec3<Type>(0);
      } /* End of 'Zero' function */

    private:
      /* Random numbers from 0 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec3) result number
       */
      static Type Helprnd0( VOID ) 
      {
        return (Type)rand() / RAND_MAX;
      } /* End of 'rnd0' function */

      /* Random numbers from -1 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (DBL) result number
       */
      static Type Helprnd1( VOID ) 
      {
        return (Type)rand() / RAND_MAX * 2 - 1;
      } /* End of 'rnd1' function */

    public:
      /* Vector with random components from 0 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec3) result vector.
       */
      static vec3<Type> Rnd0( VOID )
      {
        return vec3<Type>(Helprnd0(), Helprnd0(), Helprnd0());
      } /* End of 'Rnd0' function */

      /* Vector with random components from -1 to 1 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec3) result vector.
       */
      static vec3<Type> Rnd1( VOID )
      {
        return vec3<Type>(Helprnd1(), Helprnd1(), Helprnd1());
      } /* End of 'Rnd1' function */

      /* Distance between 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &P;
       * RETURNS:
       *   - (Type) distance.
       */
      Type Distance( const vec3<Type> &P )
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Normalize vec3 function.
       * ARGUMENTS: None
       * RETURNS:
       *   - (vec3) result vec3;
       */
      vec3<Type> & Normalize( VOID )
      {
        *this /= !*this;

        return *this;
      } /* End of 'Normalize' function */

      /* Normalizing vec3 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   - (vec3) new result vector.
       */
      vec3<Type> Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Operator[] helper function.
       * ARGUMENTS:
       *   - number:
       *       INT a;
       * RETURNS:
       *   - (Type) result number.
       */
      Type operator[]( INT a ) const
      {
        return a == 0 ? X : a == 1 ? Y : Z;
      } /* End of 'operator[]' function*/
    }; /* End of 'vec3' class */
} /* End of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */

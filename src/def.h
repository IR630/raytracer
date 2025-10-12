/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Ray tracing.
 *               Main function module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

#include "mth/mth.h"

#include <vector>

#ifndef WIN32
#define WIN32
#include <COMMONDF.H>
#undef WIN32
#else
#include <COMMONDF.H>
#endif

/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

#define Threshold 0.001

/* Project namespace */
namespace vart
{
  /* Math type definitions */
  typedef mth::vec2<DBL> vec2;
  typedef mth::vec3<DBL> vec3;
  typedef mth::vec4<DBL> vec4;
  typedef mth::matr<DBL> matr;
  typedef mth::ray<DBL> ray;
  typedef mth::camera<DBL> camera;
} /* End of 'vart' namespace */ 

/* Class of stock */
template<typename Type>
  class stock : public std::vector<Type>
  {
  public:
    /* Operator<< to print object.
     * ARGUMENTS:
     *   - type of object:
     *       const Type &X;
     * RETURNS:
     *   - (stock &) result.
     */
    stock & operator<<( const Type &X )
    {
      this->push_back(X);
      return *this;
    } /* End of 'operator<<' function */

    /* Walk all stock function.
     * ARGUMENTS:
     *   - type of arguments:
     *       WalkType Walk
     * RETURNS: None.
     */
    template<class WalkType>
      void Walk( WalkType Walk )
      {
        for (auto &x : *this)
          Walk(x);
      } /* End of 'Walk' function */
  }; /* End of 'stock' class */


/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static struct __Dummy
{
  /* Structure constructor */
  __Dummy(void)
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */

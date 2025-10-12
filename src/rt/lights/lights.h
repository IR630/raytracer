/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing lights module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __lights_h_
#define __lights_h_

#include "rt/rt_def.h"

/* Structure of materials */
static struct 
{
  std::string Name;
  vart::vec3 Ka, Kd, Ks;
  DBL Ph;
} MatLib[] =
{
    {"Black Plastic",   {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
    {"Brass",           {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
    {"Bronze",          {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
    {"Chrome",          {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
    {"Copper",          {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
    {"Gold",            {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
    {"Peweter",         {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
    {"Silver",          {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
    {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
    {"Turquoise",       {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
    {"Ruby",            {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
    {"Polished Gold",   {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
    {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
    {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
    {"Jade",            {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
    {"Obsidian",        {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
    {"Pearl",           {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
    {"Emerald",         {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
    {"Black Plastic",   {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
    {"Black Rubber",    {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
};


/* Project namespace */
namespace vart
{
  /* Declaration type */
  class shape;

  /* Environment representation type */
  class envi
  {
  public:
    DBL
      RefractionCoef,  // Refraction coefficient
      Decay;           // Environment media decay coefficient
  }; /* End of 'envi' class */

  /* Environment representation type */
  class light_info
  {
  public:
    vec3 L {};     // Light source direction
    vec3 Color {}; // Light source color
    DBL Dist = 0;  // Distance to light source
  }; /* End of 'light_info' class */

  /* Light representation type */
  class light
  {
  public:
    DBL Cc = 0, Cl = 0, Cq = 0; // Attenuation coefficients
    vec3 Color {};     // Light source color

    /* Get shadow function.
     * ARGUMENTS:
     *   - position:
     *       const vec3 &P;
     *   - light:
     *       light_infor *L;
     * RETURNS:
     *   - (DBL) result.
     */
    virtual DBL Shadow( const vec3 &P, light_info *L )
    {
      return 1;
    } /* End of 'Shadow' function */

    /* Default constructor */
    light( VOID )
    {
    } /* End of 'light' contructor */

    light( const vec3 &C, const vec3 &color ) : Color(color), Cc(C.X), Cl(C.Y), Cq(C.Z)
    {
    } /* End of 'light' constructor */
  }; /* End of 'light' class */

  ///FogColor(?);                             
  ///DBL FogStart(?), FogEnd(?);

  /* Shading coefficient store class */
  class coef
  {
  public:
    // Coefficient color value
    vec3 K;
    // Coefficient usage flag
    BOOL IsUsage;

    /* Class constructor */
    coef( VOID ) : IsUsage(FALSE)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color all components value:
     *       DBL C;
     */
    coef( DBL C ) : K(C, C, C), IsUsage(C > Threshold)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color component values:
     *       DBL X, Y, Z;
     */
    coef( DBL X, DBL Y, DBL Z ) :
      K(X, Y, Z),
      IsUsage(X > Threshold ||
              Y > Threshold ||
              Z > Threshold)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     */
    coef( const vec3 &C ) :
      K(C),
      IsUsage(C.X > Threshold ||
              C.Y > Threshold ||
              C.Z > Threshold)
    {
    } /* End of 'coef' function */

    /* Coefficient set from vec3 function.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     * RETURNS:
     *   (coef &) self reference.
     */
    coef & operator=( const vec3 &C )
    {
      K = C;
      IsUsage = C.X > Threshold ||
                C.Y > Threshold ||
                C.Z > Threshold;
      return *this;
    } /* End of 'operator=' constructor */

    /* Coefficient to vec3 color conversion function.
     * AGUMENTS: None.
     * RETURNS:
     *   (vec3) color value.
     */
    operator vec3( VOID ) const
    {
      return K;
    } /* End of 'operator color' function */

    /* Maximal component function.
     * ARGUMENTS: None;
     * RETURNS:
     *   - (DBL) result max component.
     */
    DBL MaxComponent( VOID )
    {
      if (K[0] > K[1])
        if (K[0] > K[2])
          return K[0];
        else
          return K[2];
      else
        if (K[1] > K[2])
          return K[1];
        else
          return K[2];
    } /* End of'MaxComponent' function */
  }; /* End of 'coef' class */

  /* Surface material store class */
  class surface
  {
  public:
    // Illumination coefficients
    coef Ka {0.1}, Kd {0.9}, Ks {0.0};
    // Bui Tong Phong coefficient
    DBL Ph = 47;
    // Secondary rays coefficients
    coef Kr {0}, Kt {0.9};

    /* Default contructor */
    surface( VOID )
    {
    } /* End of 'surface' contructor */

    /* Surface contructor. 
     * ARGUMENTS:
     *   - name of material:
     *       std::string Name;
     *   - reflection ray:
     *       vec3 kr;
     *   - refraction ray:
     *       vec3 kt;
     */
    surface( std::string Name, vec3 kr, vec3 kt ) : Kr(kr), Kt(kt)
    {
      for (auto i : MatLib)
      {
        if (i.Name == Name)
        {
          Ka = i.Ka;
          Kd = i.Kd;
          Ks = i.Ks;
          Ph = i.Ph;
        }
      }
    } /* End of 'surface' constructor */
  }; /* End of 'surface' class */

  /* Shading store info type */
  struct shade_info
  {
    vec3 P {};          // Point of shading evaluation
    vec3 N {};          // Point normal
    shape *Shp {};      // Shape pointer
    surface Surf {};    // Surface material
    envi Media {};      // Object media environment
    vec3 Du {}, Dv {};  // Tangent vectors
  }; /* End of 'shade_info' structure */

  /* Modifier representation type */
  class modifier
  {
  public:
    virtual ~modifier( VOID )
    {
    }

    /* Apply checker function.
     * ARGUMENTS:
     *   - shade arguments:
     *       shade_info *sh;
     * RETURNS: None.
     */
    virtual VOID Apply( shade_info *sh )
    {
    } /* End of 'Apply' function */
  };

  /* Modifier representation type */
  class checker : public modifier
  {
  public:
    /* Default contructor */
    checker( VOID )
    {
    } /* End of 'checker' constructor */

    /* Apply checker function.
     * ARGUMENTS:
     *   - shade arguments:
     *       shade_info *sh;
     * RETURNS: None.
     */
    VOID Apply( shade_info *sh ) override
    {
      sh->Surf.Kd.K += ((INT(sh->P.X + 1000) ^ INT(sh->P.Y + 1000) ^ INT(sh->P.Z + 1000)) & 1) ? 1 : 0.3;
    } /* End of 'Apply' function */
  }; /* End of 'checker ' class */
} /* End of 'vart' namespace */

#endif /* __lights_h_ */

/* END OF 'light.h' FILE */

/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "vart.h"

#include "rt_def.h"

/* Render scene function.
  * ARGUMENTS:
  *   - camera:
  *       camera &Cam;
  *    - frame:
  *        frame &Frm;
  * RETURNS: None.
  */
VOID vart::scene::Render( camera &Cam, frame &Frm )
{
  Cam.Resize(Frm.W, Frm.H);
  INT n = std::thread::hardware_concurrency() - 1;
#ifndef NDEBUG
  n = 3;
#endif /* NDEBUG */
  std::vector<std::thread> Ths;
  Ths.resize(n);
  StartRow = 0;

  auto r1 = 
  []( VOID ) -> DBL
  {
    return rand() / (DBL)RAND_MAX;
  };

  for (INT i = 0; i < n; i++)
  {
    Ths[i] = std::thread(
      [&]( VOID )
      {
        INT y = 0;
        while (y < Frm.H)
        {
          y = StartRow++;
          for (INT x = 0; x < Frm.W; x++)
          {
            INT Sub = 5; // 5
            DBL ss = 1.0 / Sub;
            INT n = 0;
            vec3 c(0), c2;
            while (n < 300)
            {
              for (INT kx = 0; kx < Sub; kx++)
                for (INT ky = 0; ky < Sub; ky++)
                {
                  ray r = Cam.FrameRay(x + kx * ss + ss * r1(), y + ky * ss + ss * r1());
                  vec3 c1 = Trace(r, Air, 1, 0);
                  c += c1;
                  c2 += c1 * c1;
                  n++;
                }
              vec3 disp2c = c2 / n - (c / n) * (c / n);
              DBL disp2 = 
                COM_SQR(disp2c.X) +
                COM_SQR(disp2c.Y) +
                COM_SQR(disp2c.Z);
              if (disp2 < 0.00001)
                break;
            }
            c /= n;
            Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
                /*
          ray r = Cam.FrameRay(x + 0.5, y + 0.5);
          vec3 c = Trace(r, Air, 1, 0);
          Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
          */
          }
        }
      });
  }
  for (INT i = 0; i < n; i++)
    Ths[i].join();
} /* End of 'vart::scene::Render' function*/

/* Tracing ray function.
  * ARGUMENTS:
  *   - ray:
  *       const ray &R;
  *   - environments:
  *       const envi &Media;
  *   - weight:
  *       DBL Weight;
  * RETURNS:
  *   - (vec3) result ray.
  */
vart::vec3 vart::scene::Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel )
{
  vec3 color = BackgroundColor;
  intr best_intr;

  if (RecLevel < MaxRecLevel)
  {
    RecLevel++;
    intr best_intr;

    if (Intersect(R, &best_intr))
    {
      best_intr.P = R(best_intr.T);
      best_intr.Shp->GetNormal(&best_intr);
      //color = Shade(R.Dir, Media, &best_intr, Weight, RecLevel);
      // color *= exp(-best_intr.T * Media.Decay);

      shade_info sh {best_intr.P, best_intr.N, best_intr.Shp, best_intr.Shp->Surf, Media, {1, 0, 0}, {0, 1, 0}};

      for (auto m : sh.Shp->Mods)
        m->Apply(&sh);
      color = Shade(R.Dir, Media, &best_intr, Weight, RecLevel, sh);
    }
    RecLevel--;
  }
  return color;
  /*
  intr in;

  if (IsToBeStop)
    return vec3(0);

  if (Intersect(R, &in))
  {
    in.P = R(in.T);
    in.Shp->GetNormal(&in);
    color = Shade(R, &in);
  }
  else
    color = vec3(0.8, 0.47, 0.3);
  return color;
  */
} /* End of 'vart::scene::Trace' function*/

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
vart::vec3 vart::scene::Shade( const vec3 &V, const envi &Media, intr *I, DBL Weight, INT RecLevel, shade_info si )
{
  //shade_info si {I->P, I->N, I->Shp, I->Shp->Surf, Media, {1, 0, 0}, {0, 1, 0}};
  /// modifiers (now)
  // face forward (si.N):
  DBL vn = V & si.N;
  BOOL IsEnter = TRUE;
  if (vn > 0)
  {
    vn = -vn;
    si.N = -si.N;
    IsEnter = FALSE;
  }

  vec3 color = si.Surf.Ka.K * AmbientColor;
  vec3 R = V - si.N * (2 * (V & si.N));

  for (auto Lgh : Lights)
  {
    light_info li;
    DBL sh = Lgh->Shadow(si.P, &li);
    // cast shadow
    intr_list il;
    if (AllIntersect(ray(si.P + li.L * Threshold, li.L), &il) > 0 && 
        il[0].T < li.Dist)
      continue; // point in shadow
    // diffuse
    if (DBL nl = si.N & li.L; nl > Threshold)
    {
      color += si.Surf.Kd.K * li.Color * nl * sh; // ??? * sh

      // specular
      if (DBL rl = R & li.L; rl > Threshold)
        color += si.Surf.Ks.K * li.Color * pow(rl, si.Surf.Ph) * sh; // ??? * sh
    }
  }

  // Reflection other scene shapes
  if (DBL w = si.Surf.Kr.MaxComponent() * Weight; w > ColorThreshold)
    // или si.Surf.Kr.IsUsage && coef(si.Surf.Kr.K * Weight).IsUsage
    color += si.Surf.Kr.K * Trace(ray(si.P + R * Threshold, R), Media, w, RecLevel);

  // Refracted ray accounting
  if (DBL w = si.Surf.Kt.MaxComponent() * Weight; w > ColorThreshold)
  {
    DBL eta = IsEnter ?
              si.Media.RefractionCoef / Media.RefractionCoef :
              Air.RefractionCoef / Media.RefractionCoef;
    vec3 T = (V - si.N * (V & si.N)) * eta - (si.N * sqrtf(1 - (1 - (si.N & -V) * (si.N & -V)) * eta * eta));

    color += si.Surf.Kt.K * Trace(ray(si.P + T * Threshold, T),
                                  IsEnter ? si.Media : Air, w, RecLevel);
  }

  return color;
} /* End of 'vart::scene::Shade' function */

/* END OF 'rt_scene.cpp' FILE */

/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : scehe.h
 * PURPOSE     : Raytracing project.
 *               Scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __scene_h_
#define __scene_h_

#include "../../def.h"
#include "shape/shape.h"
#include "lights/light.h"

// #include "../obj/shape/triangle.h"
// #include "../obj/shape/box.h"

/* Projec namespace */
namespace acrtx
{
  /* Scene representation class */
  class scene
  {
  private:
    std::vector<shape *> Shapes; // Shapes stock
    std::vector<light *> Lights; // Lights stock
    INT MaxRecLevel = 10;        // Maximal recursion level
    DBL Threshold = .1e-3;       // Geometry fault
    vec3 BackGround = vec3(0);   // BackGround color

  public:

    /* Read scene from stream in ac1 format function.
     * ARGUMENTS:
     *   - Stream to read from:
     *       std::iostream &Stream;
     *   - Error string:
     *       std::string * const Error;
     * RETURNS:
     *   (BOOL) True if success;
     */
    BOOL ReadFromStream( std::iostream &Stream, std::string * const Error );

    /* Set backgroun color function.
     * ARGUMENTS:
     *   - Background color:
     *       const vec3 &Color;
     * RETURNS: None.
     */
    VOID SetBGColor( const vec3 &Color )
    {
      BackGround = Color;
    } /* End of 'SetBGColor' function */

    /* Add element to scene by name function.
     * ARGUMENTS:
     *   - Name of light to add:
     *       const std::string &Name;
     * RETURNS: None.
     */
    template<typename Type>
      VOID Add( Type * const Entry )
      {
        if constexpr 
          (std::is_same_v<Type, light_point> || 
           std::is_same_v<Type, light_dir>)
          Lights.push_back(Entry);
        else /*if constexpr
          (std::is_same_v<Type, sphere> ||
           std::is_same_v<Type, plane>  ||
           std::is_same_v<Type, box>)*/
          Shapes.push_back(Entry);
      } /* End of 'Add' function */
      
    /* Is intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect:
     *       const ray &R;
     *   - Intersection info to fill:
     *       inter * const I;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL IsIntersect( const ray &R ) const
    {
      for (auto i : Shapes)
        if (i->IsIntersect(R))
          return TRUE;
      return FALSE;
    } /* End of 'IsIntersect' function */

    /* Intersection finding function.
     * ARGUMENTS:
     *   - Ray to intersect:
     *       const ray &R;
     *   - Intersection info to fill:
     *       inter * const I;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL Intersect( const ray &R, inter * const I ) const
    {
      BOOL IsInter = FALSE;
      inter Tmp, Res;
      Res.T = HUGE_VAL;

      for (auto i : Shapes)
        if (i->Intersect(R, &Tmp))
        {
          IsInter = TRUE;
          if (Tmp.T < Res.T)
            Res = Tmp;
        }
      *I = Res;
      return IsInter;
    } /* End of 'Intersect' function */

    ///* Shade point by light sources function.
    // * ARGUMENTS:
    // *   - Intersection info:
    // *       const inter &I;
    // *   - Reflected ray direction:
    // *      const ray &Refl;
    // * RETURNS:
    // *   (vec3) Color shaded by lights;
    // */
    //vec3 Shade( const inter &I, const vec3 &Refl, const INT RecLevel, const DBL Weight )
    //{
    //  shade Sh;
    //  vec3 Color = vec3(0);

    //  for (auto i : Lights)
    //  {
    //    i->Light(I, &Sh);
    //    if (!IsIntersect(ray(I.P + Sh.L * Threshold, Sh.L)))
    //    {
    //      Color +=
    //        Sh.C * 
    //         (I.Sh->Mtl->Ka + 
    //          I.Sh->Mtl->Kd * acmath::ClampHigh0(Sh.L & I.N) +
    //          I.Sh->Mtl->Ks * pow(acmath::ClampHigh0(Refl & Sh.L), I.Sh->Mtl->Ph));
    //    }
    //    else
    //      Color += Sh.C * 
    //        I.Sh->Mtl->Ka;
    //      // Color += 
    //      //   Trace(ray(I.P + Sh.L * Threshold, Sh.L), 
    //      //         Weight * I.Sh->Mtl->Kt, 
    //      //         I.IsIn ? *I.Sh->Envi : envi::Air(), 
    //      //         RecLevel + 1);
    //    // if (I.Sh->)
    //  }
    //  return Color;
    //} /* End of 'Shade' function */

    /* Trace ray by scene function.
     * ARGUMENTS:
     *   - Ray to trace:
     *       const ray &R;
     *   - Color weight: 
     *       const DBL Weight;
     *   - Recursion level:
     *       const INT RecLevel;
     * RETURNS:
     *   (vec3) result color.
     */
    vec3 Trace( const ray &R, const DBL Weight = 1, const envi &Around = envi::Air(), const INT RecLevel = 0 ) const
    {
      shade Sh;
      inter Info;
      vec3 Color = BackGround;
      ray Refl, Refr;
      envi Env;
      DBL Scalar, Nu, XXX; // cos2, XXX;

      if (RecLevel < MaxRecLevel && Weight > 0.1 && Intersect(R, &Info))
      {
        Info.Sh->GetAdvInfo(R, &Info);
        Scalar = (Info.N & R.Dir);
        Env = Info.IsIn ? *Info.Sh->Envi : Around;

        Color = Info.Sh->GetTex(Info.P);
        if (Scalar > 0)
        {
          Info.N = -Info.N;
          Scalar = -Scalar;
        }
        Refl.Dir = (R.Dir - (Info.N * (2 * Scalar)));
        Refl.Org = Info.P + Refl.Dir * Threshold;
        // Shade
        // cColor = Shade(Info, Refl.Dir, RecLevel, Weight):
        for (auto i : Lights)
        {
          i->Light(Info, &Sh);
          if (!IsIntersect(ray(Info.P + Sh.L * Threshold, Sh.L)))
          {
            Color +=
              Sh.C * 
               (Info.Sh->Mtl->Ka + 
                Info.Sh->Mtl->Kd * mth::ClampHigh0(Sh.L & Info.N) +
                Info.Sh->Mtl->Ks * pow(mth::ClampHigh0(Refl.Dir & Sh.L), Info.Sh->Mtl->Ph));
          }
          else
            Color += Sh.C * 
              Info.Sh->Mtl->Ka;
            //Color += 
            //  Trace(ray(Info.P + Sh.L * Threshold, Sh.L), 
            //        Weight * I.Sh->Mtl->Kt, 
            //        I.IsIn ? *I.Sh->Envi : envi::Air(), 
            //        RecLevel + 1);
        }
        // End of shading 
        // Reflection 
        Color += 
          Trace (Refl, Weight * Info.Sh->Mtl->Kr, Env, RecLevel + 1) * 
            exp(-Info.T * Env.DecK);
        // Refraction 
        assert(Around.N != 0);
        Nu = Env.N / Around.N;
        if ((XXX = 1 - ((1 - Scalar * Scalar) * Nu * Nu)) > 0)
        {
          Refr.Dir = ((R.Dir - (Info.N * Scalar)) * (Nu) - 
            (Info.N * sqrt(XXX)));// .Normalize();
          Refr.Org = Info.P + Refr.Dir * Threshold;
          Color +=
            Trace(Refr, Weight * Info.Sh->Mtl->Kt, Env, RecLevel + 1) *
              exp(-Info.T * Env.RefK);
        }
        else
        {
          Color += 
            Trace(Refl, Weight * Info.Sh->Mtl->Kt, Env, RecLevel + 1) * 
              exp(-Info.T * Env.RefK);
        }
      }
      return Color * Weight;
    } /* End of 'Trace' function */
  }; /* End of 'scene' class */ 
} /* end of 'acrtx' namespace */

#endif /* __scene_h_ */

/* END OF 'scene.h' FILE */
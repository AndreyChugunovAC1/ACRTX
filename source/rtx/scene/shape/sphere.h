/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.h
 * PURPOSE     : Raytracing project.
 *               Shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Sphere representation class */
  class sphere : public shape
  {
  public:
    DBL R, R2; // Sphere radius, squared radius
    vec3 C;    // Sphere center

    /* Base class constructor 
     * ARGUMENTS:
     *   - Sphere radius:
     *       const DBL R;
     *   - Sphere center:
     *       const vec3 &C;
     *   - Sphere material:
     *       material * const Mtl;
     *    - Sphere environment:
     *       envi * const Envi;
     */
    sphere( const vec3 &C = vec3(0), const DBL R = 1,
            material * const Mtl = nullptr, envi * const Envi = nullptr,
            texture * const Tex = nullptr ) :
      R(R), R2(R * R), C(C), shape(Mtl, Envi, Tex)
    {
    } /* End of 'sphere' function */

    /* Copying constructor. */
    sphere( const sphere& S )
    {
      Mtl = S.Mtl;
      Envi = S.Envi;
      R = S.R;
      R2 = R * R;
      C = S.C;
    } /* End of 'sphere' function */

    /* Second base class constructor.
     * ARGUMENTS:
     *   - Sphere material:
     *       material * const Mtl;
     *    - Sphere environment:
     *       envi * const Envi;
     *   - Sphere radius:
     *       const DBL R;
     *   - Sphere center:
     *       const vec3 &C;
     */
    sphere( material * const Mtl, envi * const Envi = nullptr, texture * const Tex = nullptr,
            const vec3 &C = vec3(0), const DBL R = 1 ) :
      R(R), R2(R * R), C(C), shape(Mtl, Envi, Tex)
    {
    } /* End of 'sphere' function */

    /* Virtual intersection with sphere function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL Intersect( const ray &R, inter * const I ) const final
    {
      vec3 a = C - R.Org;
      DBL oc2 = a & a,
        oh = a & R.Dir,
        oh2 = oh * oh,
        h2 = R2 - (oc2 - oh2);

      // Ray inside sphere
      if (oc2 < R2)
      {
        I->T = oh + sqrt(h2);
        I->IsIn = TRUE;
        I->Sh = this;
        return TRUE;
      }
      // Ray in front of sphere
      if (oh < 0)
        return FALSE;

      // Ray does not intersect shere
      if (h2 < 0)
        return FALSE;

      // Ray intersect sphere, and outside it
      I->T = oh - sqrt(h2);
      I->IsIn = FALSE;
      I->Sh = this;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL IsIntersect( const ray &R ) const final
    {
      vec3 a = C - R.Org;
      DBL oc2 = a & a,
        oh = a & R.Dir,
        oh2 = oh * oh,
        h2 = R2 - (oc2 - oh2);

      // Ray inside sphere
      if (oc2 < R2)
        return TRUE;

      // Ray in front of sphere
      if (oh < 0)
        return FALSE;

      // Ray does not intersect shere
      if (h2 < 0)
        return FALSE;

      // Ray intersect sphere, and outside it
      return TRUE;
    } /* End of 'IsIntersect' function */

    /* Get advanced intersection info about object function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS: None.
     */
    VOID GetAdvInfo( const ray &R, inter * const I ) const final
    {
      I->P = R(I->T);
      I->N = (I->P - C).Normalize();
      //if ((I->N & R.Dir) > 0)
      //  I->N = -I->N;
    } /* End of 'GetAdvInfo' function */

    /* Read sphere from stream in ac1 format function.
     * ARGUMENTS:
     *   - Stream to read from:
     *       std::iostream &Stream;
     *   - Error string:
     *       std::string * const Error;
     * RETURNS:
     *   (BOOL) True if success;
     */
    BOOL ReadFromStream( std::iostream &Stream, std::string * const Error );
  }; /* End of 'shape' class */ 
} /* end of 'acrtx' namespace */

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */
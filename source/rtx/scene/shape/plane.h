/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : plane.h
 * PURPOSE     : Raytracing project.
 *               Plane module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_

#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Sphere representation class */
  class plane : public shape
  {
  public:  
    DBL D;  // Plane special value
    vec3 N; // Plane normal

    /* Base class constructor 
     * ARGUMENTS:
     *   - Point on plane:
     *       const vec3 &C;
     *   - Plane normal:
     *       const vec3 &N;
     */
    plane( const vec3 &C = vec3(0), const vec3 &N = vec3(0, 1, 0),
           material * const Mtl = nullptr, envi * const Envi = nullptr,
           texture * const Tex = nullptr) :
      D(N & C), N(N), shape(Mtl, Envi, Tex)
    {
    } /* End of 'plane' function */

    /* Base class constructor 
     * ARGUMENTS:
     *   - Point on plane:
     *       const vec3 &C;
     *   - Plane normal:
     *       const vec3 &N;
     */
    plane( material * const Mtl, envi * const Envi = nullptr, texture * const Tex = nullptr,
           const vec3 &C = vec3(0), const vec3 &N = vec3(0, 1, 0) ) :
      D(N & C), N(N), shape(Mtl, Envi, Tex)
    {
    } /* End of 'plane' function */

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
      DBL X = R.Dir & N;

      if (X == 0)
        return FALSE;
      I->T = (D - (R.Org & N)) / X;
      if (I->T < 0)
        return FALSE;
      I->IsIn = X > 0;
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
      DBL X = R.Dir & N;

      if (X == 0 || (D - (R.Org & N)) / X < 0)
        return FALSE;
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
      I->N = N;//(N & R.Dir) > 0 ? -N : N;
    } /* End of 'GetAdvInfo' function */

    /* Get texture color function. (means get with spec. coords) 
     * ARGUMENTS:
     *   - Point on object:
     *       const vec3 &P;
     * RETURNS:
     *   (vec3) Color;
     */
    vec3 GetTex( const vec3 &P ) const final
    {
      vec3 n2 = vec3(0, 0, -1), n1;
      
      n2 = (N % (n1 = (n2 % N).Normalize())).Normalize();
      return Tex->Get((P & n1) / 10, (P & n2) / 10);
    } /* End of 'Color' function */
  }; /* End of 'shape' class */ 
} /* end of 'acrtx' namespace */

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */
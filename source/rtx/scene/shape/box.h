/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : box.h
 * PURPOSE     : Raytracing project.
 *               Box module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __box_h_
#define __box_h_

#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Sphere representation class */
  class box : public shape
  {
  private:
    friend class parser;
    vec3 B1, B2; // Bound box vectors

  public:
    /* Base class constructor 
     * ARGUMENTS:
     *   - Point on plane:
     *       const vec3 &C;
     *   - Plane normal:
     *       const vec3 &N;
     */
    box( const vec3 &B1 = vec3(0), const vec3 &B2 = vec3(1),
           material * const Mtl = nullptr, envi * const Envi = nullptr,
           texture * const Tex = nullptr) :
      B1(B1), B2(B2), shape(Mtl, Envi, Tex)
    {
    } /* End of 'plane' function */

    /* Base class constructor 
     * ARGUMENTS:
     *   - Point on plane:
     *       const vec3 &C;
     *   - Plane normal:
     *       const vec3 &N;
     */
    box( material * const Mtl, envi * const Envi = nullptr, texture * const Tex = nullptr,
           const vec3 &B1 = vec3(0), const vec3 &B2 = vec3(1) ) :
      B1(B1), B2(B2), shape(Mtl, Envi, Tex)
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
      vec3 D = R.Dir,
        O = R.Org;
      DBL t0, t1, tn = -_HUGE_ENUF, tf = _HUGE_ENUF;
      INT in = 0, f = 0;
      vec3 Norm[6] =
      {
        vec3(-1, 0, 0),
        vec3(1, 0, 0),
        vec3(0, -1, 0),
        vec3(0, 1, 0),
        vec3(0, 0, -1),
        vec3(0, 0, 1)
      };

      // X
      if (abs(D.X) < .1e-5 && (O.X < B1.X || O.X > B2.X))
        return FALSE;
      t0 = (B1.X - O.X) / D.X;
      t1 = (B2.X - O.X) / D.X;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 1;
        else
          in = 0;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      f = 0;
      // Y
      if (abs(D.Y) < .1e-5 && (O.Y < B1.Y || O.Y > B2.Y))
        return FALSE;
      t0 = (B1.Y - O.Y) / D.Y;
      t1 = (B2.Y - O.Y) / D.Y;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 3;
        else 
          in = 2;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      f = 0;
      // Z
      if (abs(D.Z) < .1e-5 && (O.Z < B1.Z || O.Z > B2.Z))
        return FALSE;
      t0 = (B1.Z - O.Z) / D.Z;
      t1 = (B2.Z - O.Z) / D.Z;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 5;
        else
          in = 4;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      I->T = tn;
      // I->P = R(I->T);
      I->Sh = this;
      I->N = Norm[in];
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
      vec3 D = R.Dir,
        O = R.Org;
      DBL t0, t1, tn = -_HUGE_ENUF, tf = _HUGE_ENUF;

      // X
      if (abs(D.X) < .1e-5 && (O.X < B1.X || O.X > B2.X))
        return FALSE;
      t0 = (B1.X - O.X) / D.X;
      t1 = (B2.X - O.X) / D.X;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
      }
      if (t0 > tn)
        tn = t0;
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      // Y
      if (abs(D.Y) < .1e-5 && (O.Y < B1.Y || O.Y > B2.Y))
        return FALSE;
      t0 = (B1.Y - O.Y) / D.Y;
      t1 = (B2.Y - O.Y) / D.Y;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
      }
      if (t0 > tn)
        tn = t0;
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      // Z
      if (abs(D.Z) < .1e-5 && (O.Z < B1.Z || O.Z > B2.Z))
        return FALSE;
      t0 = (B1.Z - O.Z) / D.Z;
      t1 = (B2.Z - O.Z) / D.Z;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
      }
      if (t0 > tn)
        tn = t0;
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
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
      I->IsIn = ((I->N & R.Dir) > 0);
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'shape' class */ 
} /* end of 'acrtx' namespace */

#endif /* __box_h_ */

/* END OF 'box.h' FILE */

/*
     vec3 D = R.Dir,
        O = R.Org;
      DBL t0, t1, tn = -_HUGE_ENUF, tf = _HUGE_ENUF;
      INT in = 0, f = 0;
      vec3 Norm[6] =
      {
        vec3(-1, 0, 0),
        vec3(1, 0, 0),
        vec3(0, -1, 0),
        vec3(0, 1, 0),
        vec3(0, 0, -1),
        vec3(0, 0, 1)
      };

      // X
      if (abs(D.X) < Threshold && (O.X < B1.X || O.X > B2.X))
        return FALSE;
      t0 = (B1.X - O.X) / D.X;
      t1 = (B2.X - O.X) / D.X;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 1;
        else
          in = 0;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      f = 0;
      // Y
      if (abs(D.Y) < Threshold && (O.Y < B1.Y || O.Y > B2.Y))
        return FALSE;
      t0 = (B1.Y - O.Y) / D.Y;
      t1 = (B2.Y - O.Y) / D.Y;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 3;
        else 
          in = 2;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      f = 0;
      // Z
      if (abs(D.Z) < Threshold && (O.Z < B1.Z || O.Z > B2.Z))
        return FALSE;
      t0 = (B1.Z - O.Z) / D.Z;
      t1 = (B2.Z - O.Z) / D.Z;
      if (t0 > t1)
      {
        DBL T = t0;

        t0 = t1;
        t1 = T;
        f = 1;
      }
      if (t0 > tn)
      {
        if (f == 1)
          in = 5;
        else
          in = 4;
        tn = t0;
      }
      if (tf > t1)
        tf = t1;
      if (tn > tf || tf < 0)
        return FALSE;

      I->T = tn;
      I->P = R(I->T);
      I->IsN = TRUE;
      I->Sh = this;
      I->N = Norm[in];
      if (I->N & R.Dir > 0)
        I->IsIn = TRUE;
      else
        I->IsIn = FALSE;
      return TRUE;
    } /* End of 'Intersection' function */
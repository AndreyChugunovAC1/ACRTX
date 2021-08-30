/* NAME          : triangle.h
 * PURPOSE       : Triangle module file.
 * CREATION DATE : 25.08.2021
 * LAST UPDATE   : 25.08.2021
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Sphere representation class */
  class triangle : public shape
  {
  private:
    friend class object;
    vec3 N;      // Triangle's normal
    DBL D;       // Special value for triangle's plane
    vec3 U1, V1; // Extra vectors for triangle
    DBL u0, v0;  // Extra values for triangle

  public:
    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    triangle( const vec3 &P0 = vec3(0), 
              const vec3 &P1 = vec3(1, 0, 0),
              const vec3 &P2 = vec3(0, 1, 0),
              const vec3 &NewN = vec3(0), 
              material * const Mtl = nullptr,
              envi * const Envi  = nullptr) : 
      shape(Mtl, Envi), N(vec3(0)), D(0)
    {
      vec3 s1 = P1 - P0,
        s2 = P2 - P0;

      if (NewN == vec3(0))
        N = (s1 % s2).Normalize();
      else
        N = NewN;
      D = (N & P0);
      U1 = ((s1 * (s2 & s2)) - (s2 * (s1 & s2))) / 
        (((s1 & s1) * (s2 & s2)) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1;
      V1 = ((s2 * (s1 & s1)) - (s1 * (s2 & s1))) / 
        (((s2 & s2) * (s1 & s1)) - (s2 & s1) * (s2 & s1));
      v0 = P0 & V1;
    } /* End of 'triangle' function */

    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    triangle( const vec3 &P0, 
              const vec3 &P1,
              const vec3 &P2, 
              material * const Mtl,
              envi * const Envi  = nullptr) : 
      shape(Mtl, Envi), N(vec3(0)), D(0)
    {
      vec3 s1 = P1 - P0,
        s2 = P2 - P0;

      // if (NewN == vec3(0))
      N = (s1 % s2).Normalize();
      // else
      //   N = NewN;
      D = (N & P0);
      U1 = ((s1 * (s2 & s2)) - (s2 * (s1 & s2))) / 
        (((s1 & s1) * (s2 & s2)) - (s1 & s2) * (s1 & s2));
      u0 = P0 & U1;
      V1 = ((s2 * (s1 & s1)) - (s1 * (s2 & s1))) / 
        (((s2 & s2) * (s1 & s1)) - (s2 & s1) * (s2 & s1));
      v0 = P0 & V1;
    } /* End of 'triangle' function */

    /* Template intersection function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersect info variable:
     *       intr *I;
     * RETURNS:
     *   (BOOL) True, if intersection happened,
     *     False overwise;
     */
    BOOL Intersect( const ray &R, inter * const I ) const final
    {
      DBL M = R.Dir & N;

      if (abs(M) < .1e-5)
        return FALSE;
      I->T = (D - (R.Org & N)) / M;
      if (I->T < .1e-5)
        return FALSE;

      vec3 P = R(I->T);
      DBL u = (P & U1) - u0,
        v = (P & V1) - v0;
      if (u >= 0 && v >= 0 && u + v <= 1)
      {
        I->P = P;
        I->Sh = this;
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersection' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL IsIntersect( const ray &R ) const final
    {
      DBL M = R.Dir & N;

      if (abs(M) < .1e-5)
        return FALSE;
      DBL T = (D - (R.Org & N)) / M;
      if (T < .1e-5)
        return FALSE;

      vec3 P = R(T);
      DBL u = (P & U1) - u0,
        v = (P & V1) - v0;
      if (u >= 0 && v >= 0 && u + v <= 1)
        return TRUE;
      return FALSE;
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
      I->N = N;//(N & R.Dir) > 0 ? -N : N;
      I->IsIn = ((N & R.Dir) > 0);
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'triangle' class */
} /* end of 'acrtx' namespace */

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */

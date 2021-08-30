/* NAME          : thor.h
 * PURPOSE       : Thor module file.
 * CREATION DATE : 29.08.2021
 * LAST UPDATE   : 29.08.2021
 */

#ifndef __thor_h_
#define __thor_h_

#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Thor representation class */
  class thor : public shape
  {
  private:
    friend class parser;
    vec3 N, C;  // Triangle's normal
    DBL R1, R2; // Special value for triangle's plane

  public:
    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    thor( const vec3 &P0 = vec3(0), 
          const vec3 &P1 = vec3(1, 0, 0),
          const vec3 &P2 = vec3(0, 1, 0),
          const vec3 &NewN = vec3(0), 
          material * const Mtl = nullptr,
          envi * const Envi  = nullptr) : 
      shape(Mtl, Envi), N(vec3(0)), D(0)
    {
      // vec3 s1 = P1 - P0,
      //   s2 = P2 - P0;
      // 
      // if (NewN == vec3(0))
      //   N = (s1 % s2).Normalize();
      // else
      //   N = NewN;
      // D = (N & P0);
      // U1 = ((s1 * (s2 & s2)) - (s2 * (s1 & s2))) / 
      //   (((s1 & s1) * (s2 & s2)) - (s1 & s2) * (s1 & s2));
      // u0 = P0 & U1;
      // V1 = ((s2 * (s1 & s1)) - (s1 * (s2 & s1))) / 
      //   (((s2 & s2) * (s1 & s1)) - (s2 & s1) * (s2 & s1));
      // v0 = P0 & V1;
    } /* End of 'triangle' function */

    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    thor( const vec3 &P0, 
          const vec3 &P1,
          const vec3 &P2, 
          material * const Mtl,
          envi * const Envi  = nullptr) : 
      shape(Mtl, Envi), N(vec3(0)), D(0)
    {
      // vec3 s1 = P1 - P0,
      //   s2 = P2 - P0;
      // 
      // // if (NewN == vec3(0))
      // N = (s1 % s2).Normalize();
      // // else
      // //   N = NewN;
      // D = (N & P0);
      // U1 = ((s1 * (s2 & s2)) - (s2 * (s1 & s2))) / 
      //   (((s1 & s1) * (s2 & s2)) - (s1 & s2) * (s1 & s2));
      // u0 = P0 & U1;
      // V1 = ((s2 * (s1 & s1)) - (s1 * (s2 & s1))) / 
      //   (((s2 & s2) * (s1 & s1)) - (s2 & s1) * (s2 & s1));
      // v0 = P0 & V1;
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
      // Haeder
      I->IsIn = FALSE; // ((N & R.Dir) > 0);
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'triangle' class */
} /* end of 'acrtx' namespace */

#endif /* __thor_h_ */

/* END OF 'thor.h' FILE */

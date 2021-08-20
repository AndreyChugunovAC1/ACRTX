/* NAME          : plane.h
 * PURPOSE       : Plane module file.
 * CREATION DATE : 11.08.2021
 * LAST UPDATE   : 11.08.2021
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
           material * const Mtl = nullptr, envi * const Envi = nullptr) :
      D(N & C), N(N), shape(Mtl, Envi)
    {
    } /* End of 'plane' function */

    /* Base class constructor 
     * ARGUMENTS:
     *   - Point on plane:
     *       const vec3 &C;
     *   - Plane normal:
     *       const vec3 &N;
     */
    plane( material * const Mtl, envi * const Envi = nullptr,
           const vec3 &C = vec3(0), const vec3 &N = vec3(0, 1, 0) ) :
      D(N & C), N(N), shape(Mtl, Envi)
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

    /* Read plane from stream in ac1 format function.
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

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */
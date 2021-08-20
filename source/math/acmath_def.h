/* NAME          : acmath_def.h
 * PURPOSE       : Math main definition file.
 * CREATION DATE : 07.08.2021
 * LAST UPDATE   : 07.08.2021
 */

#ifndef __acmath_def_h_
#define __acmath_def_h_

#include <cmath>

#include <windows.h>

/* Base type define */
typedef DOUBLE DBL;

/* Math namespace */
namespace acmath
{
  /* Pi math constant */
  const DBL PI = 3.14159265358979323846;

  /* Base math functions */

  /* Clamp number to number > 0 function.
   * ARGUMENTS: 
   *   - Value to clamp:
   *       const Type A;
   * RETURNS:
   *   (Type) Clamped value;
   */
  template<typename Type>
    Type ClampHigh0( const Type A )
    {
      return max(0, A);
    } /* End of 'Clamp' function */

  /* Clamp number to number > 0 function.
   * ARGUMENTS: 
   *   - Value to clamp:
   *       const Type A;
   * RETURNS:
   *   (Type) Clamped value;
   */
  template<typename Type>
    Type ClampLow1( const Type A )
    {
      return min(1, A);
    } /* End of 'Clamp' function */

  /* Degree to radian convert function.
   * ARGUMENTS:
   *   - Angle in degree:
   *       const Type D;
   * RETURNS:
   *   (Type) Angle in radians;
   */
  template<typename Type>
    Type D2R( const Type D )
    {
      return D * (PI / 180.0);
    } /* End of 'D2R' function */

  /* Radian to degree convert function.
   * ARGUMENTS:
   *   - Angle in radians:
   *       const Type R;
   * RETURNS:
   *   (Type) Angle in degree;
   */
  template<typename Type>
    Type R2D( const Type R )
    {
      return R * (180.0 / PI);
    } /* End of 'D2R' function */
} /* end of 'math' namespace */

#endif /* __acmath_def_h_ */

 /* END OF 'acmath_def.h' FILE */
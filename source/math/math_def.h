/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : math_def.h
 * PURPOSE     : Raytracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __math_def_h_
#define __math_def_h_

#include <cmath>

#include <windows.h>

/* Base type define */
typedef DOUBLE DBL;
typedef FLOAT FLT;

/* Math namespace */
namespace mth
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

#endif /* __math_def_h_ */

 /* END OF 'acmath_def.h' FILE */